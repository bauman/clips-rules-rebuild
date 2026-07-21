/*
 * is_prime_aarch64.S -- AArch64 (GNU/Clang GAS) compute core of the IsPrime
 * plugin: trial division by odd divisors up to sqrt(n).
 *
 *     int is_prime_asm(long long n);
 *
 * AAPCS64: n arrives in x0, the int result returns in w0 (low half of x0). Leaf
 * function -- it uses only the caller-saved scratch registers x1-x4, so it needs
 * no prologue, no stack frame, and no register saving.
 *
 * Where is_odd_aarch64.S is a single masking instruction, this one shows what
 * assembly actually looks like in practice: comparisons and conditional branches,
 * a loop, a multiply, and integer division with a remainder.
 *
 * Algorithm:
 *     n < 2            -> not prime
 *     n == 2           -> prime
 *     n even           -> not prime          (reuses the bit-0 mask from IsOdd)
 *     for d = 3, 5, 7, ...
 *         if d*d > n   -> prime              (no factor at or below sqrt(n))
 *         if n % d == 0-> not prime
 *
 * Only odd divisors are tried, because every even candidate was already rejected.
 * The d*d stop condition cannot overflow in practice: reaching it would require
 * ~2^31 iterations, which no caller will ever wait for. This is O(sqrt n) trial
 * division -- fine for an example, not a real primality test for large inputs.
 *
 * Named .S (capital) so the C preprocessor runs first, letting one source serve
 * both Mach-O (Apple: leading-underscore symbols, L-prefixed local labels) and
 * ELF (Linux: no underscore, .L-prefixed local labels).
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
	.type  SYM(is_prime_asm), %function
#endif
SYM(is_prime_asm):
	cmp	x0, #2
	b.lt	LBL(not_prime)        // n < 2 (covers 0, 1 and negatives)
	b.eq	LBL(is_prime)         // n == 2, the only even prime

	and	x1, x0, #1            // bit 0: the IsOdd trick
	cbz	x1, LBL(not_prime)    // even and > 2 -> composite

	mov	x2, #3                // x2 = candidate divisor
LBL(loop):
	mul	x3, x2, x2            // x3 = d*d
	cmp	x3, x0
	b.gt	LBL(is_prime)         // d*d > n -> no factor exists, n is prime

	udiv	x3, x0, x2            // x3 = n / d   (truncating)
	msub	x4, x3, x2, x0        // x4 = n - (x3 * d) = n % d
	cbz	x4, LBL(not_prime)    // remainder 0 -> d divides n

	add	x2, x2, #2            // next odd divisor
	b	LBL(loop)

LBL(not_prime):
	mov	x0, #0
	ret

LBL(is_prime):
	mov	x0, #1
	ret
