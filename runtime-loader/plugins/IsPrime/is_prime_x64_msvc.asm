; is_prime_x64_msvc.asm -- Windows x64 compute core of the IsPrime plugin, for
; the Microsoft x64 assembler (MASM / ml64.exe). Same algorithm as the other
; is_prime_* sources; see is_prime_aarch64.S for the full description.
;
;     int is_prime_asm(long long n);
;
; Microsoft x64 ABI: n arrives in RCX (NOT RDI as in System V -- see
; is_prime_x86_64.S), the int result returns in EAX. RAX, RCX, RDX and R8 are all
; volatile (caller-saved), so nothing needs preserving and no prologue is
; required; the function uses no stack, so it also needs no unwind data.
;
; NOTE the divisor lives in R8 here, not RCX. The System V version keeps it in
; RCX, but on Windows RCX holds the incoming argument, so reusing it would
; destroy n on the first iteration. That is a good illustration that porting
; assembly between ABIs is not just a syntax translation: register ROLES change,
; and the register allocation has to change with them.

.CODE

is_prime_asm PROC
    cmp     rcx, 2
    jl      not_prime               ; n < 2 (covers 0, 1 and negatives)
    je      yes_prime               ; n == 2, the only even prime

    test    rcx, 1                  ; bit 0: the IsOdd trick
    jz      not_prime               ; even and > 2 -> composite

    mov     r8, 3                   ; r8 = candidate divisor
loop_top:
    mov     rax, r8
    imul    rax, r8                 ; rax = d*d
    cmp     rax, rcx
    jg      yes_prime               ; d*d > n -> no factor exists, n is prime

    mov     rax, rcx                ; DIV divides RDX:RAX by the operand...
    xor     edx, edx                ; ...so RDX must be cleared first
    div     r8                      ; rax = n / d, rdx = n % d
    test    rdx, rdx
    jz      not_prime               ; remainder 0 -> d divides n

    add     r8, 2                   ; next odd divisor
    jmp     loop_top

not_prime:
    xor     eax, eax
    ret

yes_prime:
    mov     eax, 1
    ret
is_prime_asm ENDP

END
