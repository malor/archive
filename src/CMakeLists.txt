add_subdirectory(libchess)

option (BUILD_TESTS
        "Build chess test suite" OFF)
if(BUILD_TESTS)
    add_subdirectory(tests)
endif(BUILD_TESTS)

option (BUILD_GUI
        "Build chess gui" ON)
if(BUILD_GUI)
    add_subdirectory(gui)
endif(BUILD_GUI)
