

project(ahc)
cmake_minimum_required(VERSION 2.8)

option(WERROR "Treat warnings as errors" OFF)
option(WALL "Turn on the maximum level of compiler warnings" ON)
option(BUILD_TESTS "Build unit-tests" OFF)
option(BUILD_TOOLS "Build command line tools" ON)

add_definitions(-std=c++0x)
add_definitions(-fvisibility=hidden -fvisibility-inlines-hidden)
if(WERROR)
    add_definitions(-Werror)
endif(WERROR)
if(WALL)
    add_definitions(-Wall -pedantic)
endif(WALL)

set(SRC
    src/fgk.cpp
    src/node.cpp
)
add_library(${CMAKE_PROJECT_NAME} SHARED
    ${SRC}
)
set(AHC_INCLUDE ${ahc_SOURCE_DIR}/src)

if(BUILD_TOOLS)
    add_subdirectory(tools)
endif(BUILD_TOOLS)

if(BUILD_TESTS)
    add_subdirectory(tests/gtest)

    include_directories(${AHC_INCLUDE})
    include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
    )

    set(TESTS_SRC
        tests/main.cpp
    )

    if (BUILD_TOOLS)
        set(TESTS_SRC
            ${TESTS_SRC}
            tools/core.cpp
        )
        include_directories(tools)
        add_definitions(-DBUILD_TOOLS_TESTS)
    endif(BUILD_TOOLS)

    add_executable(run-tests
        ${TESTS_SRC}
    )

    target_link_libraries(run-tests
        ${CMAKE_PROJECT_NAME}
        gtest
    )
endif(BUILD_TESTS)
