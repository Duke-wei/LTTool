project(HelloWorld)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_COMPILER g++)
ADD_COMPILE_OPTIONS(-std=c++11)
add_definitions(-O3 -g -W -Wall)
FIND_PACKAGE(OpenCV REQUIRED)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS})
