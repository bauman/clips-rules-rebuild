/*
 * is_prime_x86_64.S -- x86-64 (System V AMD64: Linux and macOS) compute core of
 * the IsPrime plugin, assembled by GNU/Clang GAS. Same algorithm as
 * is_prime_aarch64.S; see that file for the full description.
 *
 *     int is_prime_asm(long long n);
 *
 * System V AMD64: n arrives in RDI, the int result returns in EAX. Only
 * caller-saved registers are used (RAX, RCX, RDX), so no prologue is needed.
 *
 * Two things differ from the AArch64 version beyond syntax, and both are
 * instructive:
 *
 *   1. AArch64 has no single "remainder" instruction, so that version computes
 *      it as n - (n/d)*d with UDIV + MSUB. x86-64's DIV produces the quotient
 *      and remainder together, in RAX and RDX -- one instruction, but it hard-
 *      wires those two registers and requires RDX to be zeroed first.
 *   2. AArch64 returns its result in the same register the argument arrived in
 *      (x0). Here the argument is in RDI but the result must be in EAX, so the
 *      two are necessarily distinct.
 *
 * Comments are C-style: cpp strips them on every target, and unlike "//" they
 * are unambiguous for the x86 assembler.
 */

#if defined(__APPLE__)
#  define SYM(name) _##name
#  define LBL(name) L##name        /* Mach-O: labels starting with L are local */
#else
#  define SYM(name) name
#  define LBL(name) .L##name       /* ELF: labels starting with .L are local */
#endif

	.text
	.globl SYM(is_prime_asm)
#if !defined(__APPLE__)
	.type  SYM(is_prime_asm), @function
#endif
SYM(is_prime_asm):
	cmpq	$2, %rdi
	jl	LBL(not_prime)        /* n < 2 (covers 0, 1 and negatives) */
	je	LBL(is_prime)         /* n == 2, the only even prime */

	testq	$1, %rdi              /* bit 0: the IsOdd trick */
	jz	LBL(not_prime)        /* even and > 2 -> composite */

	movq	$3, %rcx              /* rcx = candidate divisor */
LBL(loop):
	movq	%rcx, %rax
	imulq	%rcx, %rax            /* rax = d*d */
	cmpq	%rdi, %rax
	jg	LBL(is_prime)         /* d*d > n -> no factor exists, n is prime */

	movq	%rdi, %rax            /* DIV divides RDX:RAX by the operand... */
	xorl	%edx, %edx            /* ...so RDX must be cleared first */
	divq	%rcx                  /* rax = n / d, rdx = n % d */
	testq	%rdx, %rdx
	jz	LBL(not_prime)        /* remainder 0 -> d divides n */

	addq	$2, %rcx              /* next odd divisor */
	jmp	LBL(loop)

LBL(not_prime):
	xorl	%eax, %eax
	ret

LBL(is_prime):
	movl	$1, %eax
	ret
