/*
 * is_odd_x86_64.S -- x86-64 compute core of the IsOdd plugin for the System V
 * AMD64 ABI (Linux and macOS), assembled by GNU/Clang GAS.
 *
 *     int is_odd_asm(long long n);
 *
 * System V AMD64: the first integer argument arrives in RDI and the int result
 * returns in EAX. Bit 0 of RDI is bit 0 of EDI, so the 32-bit form suffices.
 * Leaf function -- no prologue/epilogue.
 *
 * NOTE the ABI difference from the Windows x64 core (is_odd_x64_msvc.asm): there
 * the first argument arrives in RCX, not RDI. Unlike AArch64 -- where Windows and
 * POSIX agree on x0 and only the assembler dialect differs -- the two x86-64
 * targets genuinely differ in the code, not just the syntax.
 *
 * Named .S (capital) so the C preprocessor runs first, letting one source serve
 * both Mach-O (Apple: leading-underscore symbols) and ELF (Linux) x86-64.
 * Comments are C-style: cpp strips them on every target, and unlike "//" they are
 * unambiguous for the x86 assembler.
 */

#if defined(__APPLE__)
#  define SYM(name) _##name
#else
#  define SYM(name) name
#endif

	.text
	.globl SYM(is_odd_asm)
#if !defined(__APPLE__)
	.type  SYM(is_odd_asm), @function
#endif
SYM(is_odd_asm):
	movl	%edi, %eax        /* System V AMD64: first integer arg in RDI */
	andl	$1, %eax          /* keep only bit 0: odd -> 1, even -> 0 */
	ret                       /* result in EAX */
