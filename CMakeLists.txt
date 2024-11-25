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



# source files

set(XMATH_ROOT ${CMAKE_CURRENT_LIST_DIR})


# srcs

set(SRCS_DIR ${XMATH_ROOT}/srcs)

set (SRCS_SRCS
    ${SRCS_DIR}/exp.cpp
)

set (SRCS_HEADERS
    ${SRCS_DIR}/core.hpp
    ${SRCS_DIR}/math.hpp
    ${SRCS_DIR}/exp.hpp
)

source_group("srcs" FILES ${SRCS_HEADERS} ${SRCS_SRCS})


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
    ${TEST_SRCS}
)

set (HEADERS
    ${SRCS_HEADERS}
    ${TEST_HEADERS}
)

if (MSVC OR CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
endif()

add_executable(xmath ${SOURCES} ${HEADERS})
target_include_directories(xmath PUBLIC ${SRCS_DIR} ${TEST_DIR})

if (MSVC)
    target_link_options(xmath PUBLIC "/NODEFAULTLIB:libcmt.lib")
endif()

message("Finished")
