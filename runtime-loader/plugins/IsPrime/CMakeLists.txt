# IsPrime -- the second assembly-backed example plugin, a step up from IsOdd.
#
# Same per-(architecture, toolchain) structure as ../IsOdd, so the two together
# show the pattern scaling to a real routine rather than a single instruction:
#
#   arch     POSIX (GAS, .S)      Windows (MSVC, .asm)
#   -------  -------------------  ----------------------------------
#   aarch64  is_prime_aarch64.S   is_prime_arm64_msvc.asm  (armasm64)
#   x86-64   is_prime_x86_64.S    is_prime_x64_msvc.asm    (MASM/ml64)
#
# On aarch64 both ABIs pass argument 1 in x0, so those two sources differ only in
# assembler DIALECT. On x86-64 they differ in the ABI itself -- System V passes it
# in RDI, Microsoft x64 in RCX -- which forces different register allocation, not
# just different syntax. That contrast is a large part of why this example exists.
#
# On any architecture without a core here, no target is created; the parent
# detects that with `if (TARGET isprime)`.
#
# TO ADD AN ARCHITECTURE: drop in one assembly file implementing is_prime_asm and
# add one branch below. Nothing else changes -- not IsPrime.c, not the test.

string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" _isprime_arch)
set(ISPRIME_ASM_SRC "")

if (_isprime_arch MATCHES "aarch64|arm64")
	if (WIN32)
		enable_language(ASM_MARMASM)   # Microsoft ARM64 assembler (armasm64)
		set(ISPRIME_ASM_SRC is_prime_arm64_msvc.asm)
		set_source_files_properties(${ISPRIME_ASM_SRC} PROPERTIES LANGUAGE ASM_MARMASM)
	else ()
		enable_language(ASM)           # GNU/Clang GAS; .S is preprocessed (Mach-O + ELF)
		set(ISPRIME_ASM_SRC is_prime_aarch64.S)
	endif ()
elseif (_isprime_arch MATCHES "x86_64|amd64")
	if (WIN32)
		enable_language(ASM_MASM)      # Microsoft x64 assembler (ml64)
		set(ISPRIME_ASM_SRC is_prime_x64_msvc.asm)
		set_source_files_properties(${ISPRIME_ASM_SRC} PROPERTIES LANGUAGE ASM_MASM)
	else ()
		enable_language(ASM)
		set(ISPRIME_ASM_SRC is_prime_x86_64.S)
	endif ()
endif ()

if (ISPRIME_ASM_SRC)
	add_library(isprime SHARED IsPrime.c ${ISPRIME_ASM_SRC})
	target_link_libraries(isprime clips)
	if (WIN32)
		set_target_properties(isprime PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
	endif ()
	# Build alongside the test executables (see ../../CMakeLists.txt).
	set_target_properties(isprime PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY "${RUNTIME_LOADER_PLUGIN_OUTPUT_DIR}"
		RUNTIME_OUTPUT_DIRECTORY "${RUNTIME_LOADER_PLUGIN_OUTPUT_DIR}")
else ()
	message(STATUS "runtime-loader: no IsPrime assembly core for '${CMAKE_SYSTEM_PROCESSOR}' -- skipping the isprime plugin and its test")
endif ()
