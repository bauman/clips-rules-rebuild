/*
 * is_odd_aarch64.S -- the hardware-specific compute core of the IsOdd plugin,
 * hand-written in AArch64 assembly. This is the whole point of the example: a
 * runtime-loaded CLIPS plugin whose hot path is implemented directly for a
 * specific architecture. A real plugin author would do something far more
 * involved here (NEON/SVE SIMD, memory-mapped device I/O, an accelerator's ISA);
 * this deliberately does the simplest thing that is unmistakably assembly.
 *
 *     int is_odd_asm(long long n);
 *
 * AAPCS64 calling convention: the 64-bit argument n arrives in x0, and the int
 * return value goes back in w0 (the low 32 bits of x0). It is a leaf function --
 * no stack frame, no calls -- so it needs no prologue/epilogue.
 *
 * The file is named .S (capital) so the C preprocessor runs before the assembler,
 * letting one source serve both Mach-O (Apple: symbols carry a leading underscore)
 * and ELF (Linux: no underscore, and .type is meaningful) aarch64 targets.
 */

#if defined(__APPLE__)
#  define SYM(name) _##name
#else
#  define SYM(name) name
#endif

	.text
	.globl SYM(is_odd_asm)
#if !defined(__APPLE__)
	.type  SYM(is_odd_asm), %function
#endif
SYM(is_odd_asm):
	and	x0, x0, #1        // keep only bit 0: odd -> 1, even -> 0 (works for negatives)
	ret                       // result already 0/1 in w0
