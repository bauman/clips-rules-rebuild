; is_odd_arm64_msvc.asm -- Windows/ARM64 compute core of the IsOdd plugin, written
; for the Microsoft ARM64 assembler (armasm64). Same instruction-set and same ABI
; result as the GNU/Clang is_odd_aarch64.S, but a different assembler DIALECT: MS
; ARMASM directives (AREA/PROC/EXPORT/END) instead of GAS (.text/.globl/.type). The
; two files are selected per-toolchain in runtime-loader/CMakeLists.txt.
;
;     int is_odd_asm(long long n);
;
; Windows ARM64 calling convention: the 64-bit argument n arrives in x0, the int
; result returns in w0 (low half of x0). Leaf function -- no prologue/epilogue.
; Windows ARM64 does not decorate C symbol names, so the label is is_odd_asm with
; no leading underscore (matching the extern in IsOdd.c).

    AREA    |.text|, CODE, READONLY, ALIGN=2
    EXPORT  is_odd_asm

is_odd_asm PROC
    and     x0, x0, #1        ; keep only bit 0: odd -> 1, even -> 0 (works for negatives)
    ret                       ; result already 0/1 in w0
    ENDP

    END
