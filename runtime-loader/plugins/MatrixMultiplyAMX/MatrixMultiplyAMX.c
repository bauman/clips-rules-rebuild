#include "clips.h"

#include <setjmp.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sysctl.h>

/*
 * MatrixMultiplyAMX -- the hyper-specific hardware example.
 *
 * This plugin multiplies a 2x4 by a 4x2 matrix on Apple's AMX coprocessor: an
 * UNDOCUMENTED matrix unit present on Apple Silicon M1/M2/M3. There is no
 * portable C for it, no compiler intrinsics, and no Apple-published ISA -- the
 * instruction encodings below are reverse-engineered and are emitted as raw
 * `.word` values through inline assembly. It is the clearest possible case for
 * why this loader exists: shipping support for silicon like this as a swappable
 * plugin, rather than baking it into CLIPS.
 *
 * It is also a third flavour of assembly example. plugins/IsOdd and
 * plugins/IsPrime keep their cores in separate per-toolchain .S/.asm files; here
 * the instructions must be interleaved with C (pointers handed to the coprocessor
 * one operation at a time), so inline asm is the natural form.
 *
 * ============================ THE CONTRACT ============================
 * The loader deliberately knows NOTHING about what a plugin does -- it resolves a
 * symbol and calls it. That makes it the PLUGIN's responsibility not to wreck the
 * process if it is loaded somewhere it cannot run, and to report that refusal
 * through CLIPS rather than by crashing.
 *
 * So this plugin inspects its own environment before executing a single AMX
 * instruction, and returns the symbol FAIL if the host is unsuitable. Executing
 * AMX on hardware without it is not a graceful error -- it is SIGILL, which kills
 * the whole CLIPS process and every unrelated rule in it. The guard below is the
 * plugin holding up its end of that bargain.
 * ======================================================================
 *
 * Result: a CLIPS multifield of 4 floats (the 2x2 product, row-major), or the
 * symbol FAIL if the hardware is unsupported or the arguments are malformed.
 */

/* ------------------------------------------------------------------ *
 * AMX instruction encoding
 *
 * Every AMX instruction is   0x00201000 | (op << 5) | operand
 * where `operand` is a general-purpose register number for the memory ops, or a
 * small immediate for op 17 (the enable/disable pair).
 *
 *      op  0 = ldx     load 64 bytes into the X register file
 *      op  1 = ldy     load 64 bytes into the Y register file
 *      op  5 = stz     store 64 bytes from a Z (accumulator) row
 *      op 12 = fma32   f32 multiply-accumulate
 *      op 17 = set/clr operand 0 enables the unit, 1 disables it
 *
 * The register number must be baked into the instruction word, but the compiler
 * chooses which register holds our pointer. The trick below recovers it: "%1"
 * renders as a register name such as "x8", so "0%1" assembles as 0x8 == 8. The
 * subtraction corrects x16-x31, where "0x16" would otherwise read as hex 22.
 * ------------------------------------------------------------------ */
#define AMX_OP_GPR(op, gpr) \
	__asm__ __volatile__(".word (0x00201000 + (%0 << 5) + 0%1 - ((0%1 >> 4) * 6))" \
	                     :: "i"(op), "r"((uint64_t)(gpr)) : "memory")

#define AMX_SET()    __asm__ __volatile__(".word 0x00201220" ::: "memory")
#define AMX_CLR()    __asm__ __volatile__(".word 0x00201221" ::: "memory")
#define AMX_LDX(p)   AMX_OP_GPR(0,  p)
#define AMX_LDY(p)   AMX_OP_GPR(1,  p)
#define AMX_STZ(p)   AMX_OP_GPR(5,  p)
#define AMX_FMA32(x) AMX_OP_GPR(12, x)

/* ------------------------------------------------------------------ *
 * Environment guard -- PROBE the capability, do not infer it.
 *
 * The obvious guard is to read machdep.cpu.brand_string and allowlist the
 * families known to have AMX (M1/M2/M3; it was removed in M4 in favour of the
 * architectural SME extension). That is what this plugin did first, and it was
 * WRONG -- provably so: CI's macOS arm64 runners report an Apple Silicon brand
 * string and still SIGILL on the first AMX instruction, because those runners are
 * VIRTUALISED and the hypervisor does not expose an undocumented coprocessor.
 *
 * The CPU model simply does not determine whether these instructions will
 * execute. Virtualisation, a future silicon revision, or a macOS policy change
 * can each remove them while the brand string keeps saying "Apple M2". So the
 * only trustworthy guard is to TRY the instruction and catch the fault:
 *
 *   1. cheap early-out: FEAT_SME present => M4 or later => AMX is gone.
 *   2. authoritative: execute AMX_SET/AMX_CLR under a SIGILL handler. If it
 *      faults we siglongjmp out and mark AMX unusable, whatever the reason.
 *
 * This is the plugin honouring its half of the loader contract the hard way:
 * the loader cannot know what silicon a plugin needs, so the plugin must find
 * out for itself -- and finding out means asking the hardware, not the marketing
 * string.
 *
 * CAVEAT: the probe installs a process-wide SIGILL handler for the duration of
 * two instructions. It runs exactly once, on first call, and restores the
 * previous handler immediately. Trigger it from a quiescent point (a plugin's
 * first use) rather than while other threads are handling their own signals.
 * ------------------------------------------------------------------ */

static sigjmp_buf amx_probe_jmp;

static void amx_probe_sigill(int sig)
{
	(void)sig;
	siglongjmp(amx_probe_jmp, 1);
}

/*
 * Computed once and cached. The cache is a plain int: every writer stores the
 * same value, so a race between two first-callers is benign (worst case the
 * probe runs twice and agrees). Aligned int stores are atomic on arm64.
 */
static int amx_usable(void)
{
	static int cached = -1;            /* -1 = not yet determined, 0 = no, 1 = yes */
	if (cached >= 0) { return cached; }

	struct sigaction probe_action, saved_action;
	int result = 0;

	/* Cheap early-out: SME present => M4 or later => AMX has been removed. Saves
	   installing a signal handler on hardware we already know cannot work. */
	{
		int has_sme = 0;
		size_t sme_size = sizeof(has_sme);
		if (sysctlbyname("hw.optional.arm.FEAT_SME", &has_sme, &sme_size, NULL, 0) == 0
		    && has_sme != 0) {
			cached = 0;
			return cached;
		}
	}

	memset(&probe_action, 0, sizeof(probe_action));
	probe_action.sa_handler = amx_probe_sigill;
	sigemptyset(&probe_action.sa_mask);
	probe_action.sa_flags = 0;

	if (sigaction(SIGILL, &probe_action, &saved_action) != 0) {
		cached = 0;                    /* cannot install the guard -> refuse */
		return cached;
	}

	if (sigsetjmp(amx_probe_jmp, 1) == 0) {
		AMX_SET();                     /* faults here if AMX is unavailable */
		AMX_CLR();
		result = 1;
	}
	/* else: we arrived via siglongjmp from the handler; result stays 0 */

	sigaction(SIGILL, &saved_action, NULL);

	cached = result;
	return cached;
}

/* ------------------------------------------------------------------ *
 * The computation
 *
 * C(2x2) = A(2x4) * B(4x2), built as the sum of four outer products:
 *     C = sum over k of  (column k of A) (x) (row k of B)
 *
 * One fma32 computes an entire 16x16 outer product in a single instruction,
 * accumulating into the Z register file as  Z[j*4][i] += X[i] * Y[j]  (verified
 * empirically on M2 -- the f32 result rows are strided by 4). So C[i][j] ends up
 * at Z row j*4, element i, and reading rows 0 and 4 recovers the 2x2 answer.
 *
 * AMX_SET also zeroes Z, so no explicit clear of the accumulator is needed.
 * All buffers must be 64-byte aligned: the unit moves whole 64-byte blocks.
 * ------------------------------------------------------------------ */
static void amx_matmul_2x4_4x2(const double A[8], const double B[8], double C[4])
{
	float X[16]  __attribute__((aligned(64))) = {0};
	float Y[16]  __attribute__((aligned(64))) = {0};
	float z0[16] __attribute__((aligned(64)));
	float z4[16] __attribute__((aligned(64)));
	int k;

	AMX_SET();
	for (k = 0; k < 4; k++) {
		X[0] = (float)A[0 * 4 + k];      /* column k of A */
		X[1] = (float)A[1 * 4 + k];
		Y[0] = (float)B[k * 2 + 0];      /* row k of B    */
		Y[1] = (float)B[k * 2 + 1];
		AMX_LDX(X);
		AMX_LDY(Y);
		AMX_FMA32(0);                    /* matrix mode, no offsets, accumulate */
	}
	AMX_STZ(((uint64_t)z0) | ((uint64_t)0 << 56));   /* Z row 0 */
	AMX_STZ(((uint64_t)z4) | ((uint64_t)4 << 56));   /* Z row 4 */
	AMX_CLR();

	C[0] = (double)z0[0];   /* C[0][0] */
	C[1] = (double)z4[0];   /* C[0][1] */
	C[2] = (double)z0[1];   /* C[1][0] */
	C[3] = (double)z4[1];   /* C[1][1] */
}

/*
 * Read `n` consecutive numeric arguments starting at position `first`.
 *
 * NOTE ON THE CALLING CONVENTION -- this is a property of the loader that every
 * plugin author needs to know. The generated wrapper is
 *
 *     (deffunction MatrixMultiply ($?args) (Dispatch MatrixMultiply (expand$ ?args)))
 *
 * and a $?args parameter FLATTENS multifields: calling
 *     (MatrixMultiply (create$ 1 2 3 4 5 6 7 8) (create$ 9 10 11 12 13 14 15 16))
 * binds ?args to ONE 16-element multifield, which expand$ then passes as 16
 * separate scalar arguments. A plugin therefore never receives a multifield
 * ARGUMENT through the loader -- only scalars. (It may still RETURN one, which is
 * what this plugin does.)
 *
 * That is convenient here rather than limiting: callers can pass 16 literals, or
 * two multifield variables, or any mixture, and it all arrives the same way.
 */
static int scalar_numbers(UDFContext *udfc, unsigned int first, unsigned int n, double *dst)
{
	UDFValue v;
	unsigned int i;
	for (i = 0; i < n; i++) {
		if (!UDFNthArgument(udfc, first + i, ANY_TYPE_BITS, &v)) { return 0; }
		if (v.header->type == INTEGER_TYPE)     { dst[i] = (double)v.integerValue->contents; }
		else if (v.header->type == FLOAT_TYPE)  { dst[i] = v.floatValue->contents; }
		else { return 0; }
	}
	return 1;
}

void MatrixMultiply(
	Environment* env,
	UDFContext* udfc,
	UDFValue* out)
{
	double A[8], B[8], C[4];
	MultifieldBuilder *mb;
	Multifield *mf;
	int i;

	/* THE GUARD -- refuse before touching the coprocessor. Returning FAIL keeps
	   the failure inside CLIPS, where a rule can react to it; executing AMX on
	   hardware that lacks it would SIGILL and take the whole process down. */
	if (!amx_usable()) {
		out->lexemeValue = CreateSymbol(env, "FAIL");
		return;
	}

	/* Argument 1 is the dispatch name, so the 16 matrix values occupy 2..17:
	   A (2x4, row-major) then B (4x2, row-major). Arguments are retrieved
	   permissively and type-checked here, so a bad call yields FAIL rather than a
	   hard [ARGACCES2] that halts the deffunction. */
	if (UDFArgumentCount(udfc) != 17 ||
	    !scalar_numbers(udfc, 2,  8, A) ||
	    !scalar_numbers(udfc, 10, 8, B)) {
		out->lexemeValue = CreateSymbol(env, "FAIL");
		return;
	}

	amx_matmul_2x4_4x2(A, B, C);

	mb = CreateMultifieldBuilder(env, 4);
	for (i = 0; i < 4; i++) { MBAppendFloat(mb, C[i]); }
	mf = MBCreate(mb);
	MBDispose(mb);

	out->multifieldValue = mf;
	out->begin = 0;
	out->range = mf->length;
}
