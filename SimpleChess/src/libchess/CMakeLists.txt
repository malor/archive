project(chess)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CXXFLAGS
            ${CXXFLAGS}
            "-Wall"
            "-Wextra"
            "-Wold-style-cast"
            "-fvisibility=hidden"
    )
endif(CMAKE_COMPILER_IS_GNUCXX)
add_definitions(${CXXFLAGS})

set(CHESS_INCLUDE_DIRS ${chess_SOURCE_DIR} CACHE STRING "libchess includes" FORCE)

set(sources
    ChessBoard.cpp
    ChessPiece.cpp
    pieces/Bishop.cpp
    pieces/King.cpp
    pieces/Knight.cpp
    pieces/Pawn.cpp
    pieces/Queen.cpp
    pieces/Rook.cpp
)

include_directories(${CHESS_INCLUDE_DIRS})

add_library(${PROJECT_NAME}-static STATIC
                ${sources}
)

add_library(${PROJECT_NAME} SHARED
                ${sources}
)
