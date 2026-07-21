# MatrixMultiplyAMX -- the hyper-specific hardware example.
#
# Multiplies matrices on Apple's AMX coprocessor: an UNDOCUMENTED matrix unit on
# Apple Silicon M1/M2/M3, driven by reverse-engineered instruction encodings
# emitted as raw .word values through inline assembly. No portable C, no
# intrinsics, no published ISA -- exactly the situation the runtime loader exists
# to serve.
#
# Gated on APPLE AND arm64: the encodings are meaningless anywhere else, so no
# target is created and the parent skips the test via `if (TARGET matrixmultiply)`.
#
# The build guard is NOT the whole story. AMX was removed in M4 (replaced by SME),
# and an Apple-Silicon build could still land on such a machine at RUNTIME. That
# is the plugin's own responsibility, not the loader's: MatrixMultiplyAMX.c
# inspects the CPU before issuing a single AMX instruction and returns FAIL to
# CLIPS if the host is unsuitable, because the alternative is a SIGILL that kills
# the entire CLIPS process.
#
# Unlike ../IsOdd and ../IsPrime, the core is inline assembly rather than separate
# per-toolchain .S/.asm files: the AMX instructions must be interleaved with C
# that hands the unit one pointer at a time.

if (APPLE AND CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64")
	add_library(matrixmultiply SHARED MatrixMultiplyAMX.c)
	target_link_libraries(matrixmultiply clips)
	# Build alongside the test executables (see ../../CMakeLists.txt).
	set_target_properties(matrixmultiply PROPERTIES
		OUTPUT_NAME matrixmultiply
		LIBRARY_OUTPUT_DIRECTORY "${RUNTIME_LOADER_PLUGIN_OUTPUT_DIR}"
		RUNTIME_OUTPUT_DIRECTORY "${RUNTIME_LOADER_PLUGIN_OUTPUT_DIR}")
else ()
	message(STATUS "runtime-loader: AMX is Apple-Silicon only -- skipping the matrixmultiply plugin and its test")
endif ()
