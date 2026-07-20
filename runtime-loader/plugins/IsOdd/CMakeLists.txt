# IsOdd -- the assembly-backed example plugin.
#
# This directory is meant to be COPIED as the starting point for a real plugin, so
# everything IsOdd-specific lives here: the sources, the per-target assembly, and
# the build rules that pick between them.
#
# The compute core is one tiny routine -- int is_odd_asm(long long) -- supplied
# once per (architecture, toolchain) pair:
#
#   arch     POSIX (GAS, .S)     Windows (MSVC, .asm)
#   -------  ------------------  --------------------------------
#   aarch64  is_odd_aarch64.S    is_odd_arm64_msvc.asm  (armasm64)
#   x86-64   is_odd_x86_64.S     is_odd_x64_msvc.asm    (MASM/ml64)
#
# On aarch64 only the assembler DIALECT differs (both ABIs pass argument 1 in x0).
# On x86-64 the ABIs themselves differ -- System V passes it in RDI, Microsoft x64
# in RCX -- so those two sources are genuinely different code, not a syntax
# variant. IsOdd.c is the single CLIPS-facing adapter and is identical everywhere.
#
# On any architecture without a core here, no target is created at all; the parent
# detects that with `if (TARGET isodd)` (targets are global across directories,
# unlike variables, which do not propagate to the parent scope).
#
# TO ADD AN ARCHITECTURE: drop in one assembly file implementing is_odd_asm and add
# one branch below. Nothing else changes -- not IsOdd.c, not the test, not any rule.

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" _isodd_arch)
set(ISODD_ASM_SRC "")

if (_isodd_arch MATCHES "aarch64|arm64")
	if (WIN32)
		enable_language(ASM_MARMASM)   # Microsoft ARM64 assembler (armasm64)
		set(ISODD_ASM_SRC is_odd_arm64_msvc.asm)
		set_source_files_properties(${ISODD_ASM_SRC} PROPERTIES LANGUAGE ASM_MARMASM)
	else ()
		enable_language(ASM)           # GNU/Clang GAS; .S is preprocessed (Mach-O + ELF)
		set(ISODD_ASM_SRC is_odd_aarch64.S)
	endif ()
elseif (_isodd_arch MATCHES "x86_64|amd64")
	if (WIN32)
		enable_language(ASM_MASM)      # Microsoft x64 assembler (ml64)
		set(ISODD_ASM_SRC is_odd_x64_msvc.asm)
		set_source_files_properties(${ISODD_ASM_SRC} PROPERTIES LANGUAGE ASM_MASM)
	else ()
		enable_language(ASM)
		set(ISODD_ASM_SRC is_odd_x86_64.S)
	endif ()
endif ()

if (ISODD_ASM_SRC)
	add_library(isodd SHARED IsOdd.c ${ISODD_ASM_SRC})
	target_link_libraries(isodd clips)
	if (WIN32)
		set_target_properties(isodd PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
	endif ()
else ()
	message(STATUS "runtime-loader: no IsOdd assembly core for '${CMAKE_SYSTEM_PROCESSOR}' -- skipping the isodd plugin and its test")
endif ()
