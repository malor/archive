project(tools)

include_directories(${AHC_INCLUDE})

set(COMPRESS_SOURCE core.cpp compress.cpp)
add_executable(compress ${COMPRESS_SOURCE})
target_link_libraries(compress ahc)

set(DECOMPRESS_SOURCE core.cpp decompress.cpp)
add_executable(decompress ${DECOMPRESS_SOURCE})
target_link_libraries(decompress ahc)
