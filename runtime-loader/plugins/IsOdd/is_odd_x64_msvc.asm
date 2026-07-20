; is_odd_x64_msvc.asm -- Windows x64 compute core of the IsOdd plugin, written for
; the Microsoft x64 assembler (MASM / ml64.exe).
;
;     int is_odd_asm(long long n);
;
; Microsoft x64 ABI: the first integer argument arrives in RCX (NOT RDI as in the
; System V AMD64 ABI used by Linux/macOS -- see is_odd_x86_64.S), and the int
; result returns in EAX. Bit 0 of RCX is bit 0 of ECX, so the 32-bit form
; suffices. Leaf function -- no prologue/epilogue, no stack use, so no unwind
; data is required.
;
; Windows x64 does not decorate C symbol names (unlike 32-bit x86), so the label
; is is_odd_asm with no leading underscore, matching the extern in IsOdd.c.

.CODE

is_odd_asm PROC
    mov     eax, ecx          ; Microsoft x64 ABI: first integer arg in RCX
    and     eax, 1            ; keep only bit 0: odd -> 1, even -> 0
    ret                       ; result in EAX
is_odd_asm ENDP

END
