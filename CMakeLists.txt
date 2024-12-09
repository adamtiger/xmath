cmake_minimum_required(VERSION 3.25)

project(XMath CXX)
message("Start generating!")

option(BUILD_WITH_ASSERT "Whether to assert when needed" ON)
option(BUILD_SHARED "Whether to create a dynamically linked library" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

IF (BUILD_WITH_ASSERT)
    add_compile_definitions(AC_WITH_ASSERT)
	message("Compile with asserts")
ENDIF(BUILD_WITH_ASSERT)

IF (BUILD_SHARED)
    add_compile_definitions(EXPORT_DLL)
	message("Compile shared")
ENDIF(BUILD_SHARED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)


# architecture identification
option(BW_NO_INTRISICS "AVX512 intrinsic usage" OFF)
option(BW_AVX512 "AVX512 intrinsic usage" ON)
option(BW_NEON "ARM NEON intrinsic usage" OFF)

IF (BW_NO_INTRISICS)
    add_compile_definitions(INTRIN_NO)
    message("No intrinsics")
ELSEIF (BW_AVX512)
    add_compile_definitions(INTRIN_AVX512)
    message("AVX512 intrinsics")
ELSEIF (BW_NEON)
    add_compile_definitions(INTRIN_NEON)
    message("ARM NEON intrinsics")
ENDIF()



# source files

set(XMATH_ROOT ${CMAKE_CURRENT_LIST_DIR})


# srcs

set(SRCS_DIR ${XMATH_ROOT}/srcs)

set (SRCS_SRCS
)

set (SRCS_HEADERS
    ${SRCS_DIR}/core.hpp
    ${SRCS_DIR}/device.hpp
    ${SRCS_DIR}/math.hpp
    ${SRCS_DIR}/exp.hpp
    ${SRCS_DIR}/log.hpp
)

source_group("srcs" FILES ${SRCS_HEADERS} ${SRCS_SRCS})


# cpu x64 (default implementation)

set(X64_DIR ${XMATH_ROOT}/srcs/x64)

set (X64_SRCS
    ${X64_DIR}/exp.cpp
    ${X64_DIR}/log.cpp
)

set (X64_HEADERS
)

source_group("x64" FILES ${X64_HEADERS} ${X64_SRCS})


# cpu avx512

set(AVX512_DIR ${XMATH_ROOT}/srcs/avx512)

set (AVX512_SRCS
    ${AVX512_DIR}/exp.cpp
    ${AVX512_DIR}/log.cpp
)

set (AVX512_HEADERS
)

source_group("avx512" FILES ${AVX512_HEADERS} ${AVX512_SRCS})


# cpu arm neon

set(NEON_DIR ${XMATH_ROOT}/srcs/neon)

set (NEON_SRCS
    ${NEON_DIR}/exp.cpp
    ${NEON_DIR}/log.cpp
)

set (NEON_HEADERS
)

source_group("armneon" FILES ${NEON_HEADERS} ${NEON_SRCS})


IF (BW_NO_INTRISICS)
    set(INTRINSIC_SRCS ${X64_SRCS})
    set(INTRINSIC_HEADERS ${X64_HEADERS})
ELSEIF (BW_AVX512)
    set(INTRINSIC_SRCS ${AVX512_SRCS})
    set(INTRINSIC_HEADERS ${AVX512_HEADERS})
ELSEIF (BW_NEON)
    set(INTRINSIC_SRCS ${NEON_SRCS})
    set(INTRINSIC_HEADERS ${NEON_HEADERS})
ENDIF()


# tests

set(TEST_DIR ${XMATH_ROOT}/tests)

set (TEST_SRCS
    ${TEST_DIR}/main.cpp
)

set (TEST_HEADERS
)

source_group("tests" FILES ${TEST_HEADERS} ${TEST_SRCS})


# set all sources
set (SOURCES
    ${SRCS_SRCS}
    ${INTRINSIC_SRCS}
    ${TEST_SRCS}
)

set (HEADERS
    ${SRCS_HEADERS}
    ${INTRINSIC_HEADERS}
    ${TEST_HEADERS}
)

if (MSVC OR CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
endif()

add_executable(xmath ${SOURCES} ${HEADERS})
target_include_directories(xmath PUBLIC ${SRCS_DIR} ${TEST_DIR})

if (MSVC)
    target_compile_options(xmath PUBLIC "-mfma" "-mavx512f" "-mavx512bw" "-mavx512vl")
    target_link_options(xmath PUBLIC "/NODEFAULTLIB:libcmt.lib")
elseif (LINUX)
    target_compile_options(xmath PUBLIC "-mfpu=neon")
endif()

message("Finished")
