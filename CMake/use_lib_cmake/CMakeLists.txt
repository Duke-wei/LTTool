project(Main)

cmake_minimum_required(VERSION 2.8)

add_subdirectory(Lib)

aux_source_directory(. DIR_SRCS)

add_executable(Main ${DIR_SRCS})

target_link_libraries(Main libtest)
