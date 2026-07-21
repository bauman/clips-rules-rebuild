; is_prime_arm64_msvc.asm -- Windows/ARM64 compute core of the IsPrime plugin,
; for the Microsoft ARM64 assembler (armasm64). Same instruction set and same
; algorithm as is_prime_aarch64.S -- only the assembler DIALECT differs: MS
; ARMASM directives (AREA/PROC/ENDP/END, labels in column 1 without a colon)
; instead of GAS (.text/.globl/.type, labels with a colon).
;
;     int is_prime_asm(long long n);
;
; Windows ARM64 uses the same register convention as AAPCS64 here: n arrives in
; x0 and the int result returns in w0. Only the volatile scratch registers x1-x4
; are used, so this is a leaf function with no prologue, no stack use, and hence
; no unwind data required.
;
; Contrast with the two x86-64 ports: there, Windows and System V disagree about
; which register carries the argument (RCX vs RDI), which forces different
; register allocation. On AArch64 both agree on x0, so this file is a pure
; syntax translation of is_prime_aarch64.S.

    AREA    |.text|, CODE, READONLY, ALIGN=2
    EXPORT  is_prime_asm

is_prime_asm PROC
    cmp     x0, #2
    blt     not_prime               ; n < 2 (covers 0, 1 and negatives)
    beq     yes_prime               ; n == 2, the only even prime

    and     x1, x0, #1              ; bit 0: the IsOdd trick
    cbz     x1, not_prime           ; even and > 2 -> composite

    mov     x2, #3                  ; x2 = candidate divisor
loop_top
    mul     x3, x2, x2              ; x3 = d*d
    cmp     x3, x0
    bgt     yes_prime               ; d*d > n -> no factor exists, n is prime

    udiv    x3, x0, x2              ; x3 = n / d   (truncating)
    msub    x4, x3, x2, x0          ; x4 = n - (x3 * d) = n % d
    cbz     x4, not_prime           ; remainder 0 -> d divides n

    add     x2, x2, #2              ; next odd divisor
    b       loop_top

not_prime
    mov     x0, #0
    ret

yes_prime
    mov     x0, #1
    ret
    ENDP

    END
