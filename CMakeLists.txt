cmake_minimum_required(VERSION 4.2.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER "C:/Program Files (x86)/mingw64/bin/g++.exe")
project(Snake)

include_directories(${CMAKE_SOURCE_DIR}/libs/SDL3/include)
include_directories(${CMAKE_SOURCE_DIR}/libs)
include_directories(${CMAKE_SOURCE_DIR}/include)

link_directories(${CMAKE_SOURCE_DIR}/libs/SDL3/lib)
link_libraries(
    libSDL3.dll.a
    libSDL3_test.a
)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
set(CMAKE_BUILD_TYPE "Release")

aux_source_directory(${CMAKE_SOURCE_DIR}/src SRC_LIST)

add_executable(
    snake 
    ${SRC_LIST}
)

target_link_libraries(
    snake
    PUBLIC ${CMAKE_SOURCE_DIR}/bin/SDL3.dll
    PUBLIC ${CMAKE_SOURCE_DIR}/bin/SDL3_ttf.dll
)