cmake_minimum_required(VERSION 3.5)
project(GateServer)

message(${CMAKE_BUILD_TYPE})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})    #动态库
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})    #静态库
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(${PROJECT_SOURCE_DIR}/Dependencies/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/Dependencies/lib/${CMAKE_BUILD_TYPE})

#add_subdirectory(lib/Libevent)
file(GLOB_RECURSE SOURCE_FILES include/*.h src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

IF (WIN32)
    target_link_libraries( ${PROJECT_NAME} uv flatbuffers uuid ws2_32.lib Iphlpapi.lib Psapi.lib Userenv.lib)
ELSEIF (APPLE)
    target_link_libraries( ${PROJECT_NAME} uv flatbuffers uuid)
ELSEIF (UNIX)
    MESSAGE(STATUS "Now is UNIX-like OS's. Including aPPLE os x  and CygWin")

    target_link_libraries( ${PROJECT_NAME} uv flatbuffers uuid)
ENDIF ()

