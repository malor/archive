project(chess-test)

find_package(Boost COMPONENTS unit_test_framework)

set(sources
    chess_test.cpp
)

include_directories(${CHESS_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

add_definitions("-std=c++0x")

add_executable(${PROJECT_NAME}
    ${sources}
)

target_link_libraries(${PROJECT_NAME}
                         chess
                         ${Boost_LIBRARIES}
)
