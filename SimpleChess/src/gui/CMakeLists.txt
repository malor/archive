project(chess-gui)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CXXFLAGS
            ${CXXFLAGS}
            "-Wall"
            "-Wold-style-cast"
    )
endif(CMAKE_COMPILER_IS_GNUCXX)
add_definitions(${CXXFLAGS})

set(SRC
        main.cpp
        ChessBoardUi.cpp
        DrawVisitor.cpp
)

set(MOC_HEADERS
        ChessBoardUi.hpp
)

find_package(Qt4 REQUIRED)
set(QT_USE_QTSVG TRUE)
include(${QT_USE_FILE})

qt4_add_resources(resources resources.qrc)
qt4_wrap_cpp(MOC_SOURCES
                 ${MOC_HEADERS}
)

include_directories(${CHESS_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
                   ${SRC}
                   ${MOC_SOURCES}
                   ${resources}
)

target_link_libraries(${PROJECT_NAME}
                         chess
                         ${QT_LIBRARIES}
)
