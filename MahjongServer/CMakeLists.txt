cmake_minimum_required(VERSION 3.5)
project(MahjongServer)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${PROJECT_SOURCE_DIR}/include)

#add_subdirectory(lib/Libevent)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp include/*.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# target_link_libraries( ${PROJECT_NAME} )