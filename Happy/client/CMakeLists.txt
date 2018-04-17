cmake_minimum_required(VERSION 3.5)
project(network)

MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(${PROJECT_SOURCE_DIR}/Dependencies/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCE_FILES include/*.h src/*.c src/*.cpp src/*.cxx)
#file(GLOB_RECURSE SOURCE_FILES src/network.cpp src/*.cxx)

link_directories(${PROJECT_SOURCE_DIR}/Dependencies/lib/${CMAKE_BUILD_TYPE})

if (APPLE)
    add_library(${PROJECT_NAME} MODULE ${SOURCE_FILES})
    add_library(${PROJECT_NAME}_static STATIC ${SOURCE_FILES})

    target_link_libraries(${PROJECT_NAME} uv flatbuffers)

    # OSX 下面的 Unity 插件要是 *.bundle 格式的
    set_target_properties(${PROJECT_NAME} PROPERTIES BUNDLE TRUE)

    set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

    set_target_properties(${PROJECT_NAME} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(${PROJECT_NAME}_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

    # 设置编译器
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)

    # 设置代码库的输出路径
    set(OUT_PATH ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/OSX)
elseif(IOS)
    message("IOS")
#    add_library(mylog STATIC ${SOURCE_FILES})

    # 设置编译器, 由于 iOS 和 OSX 使用的是相同的编译器，所以此处设置为 Mac 上的Clang 的路径
    # 但是对于 Android 来讲，交叉编译的环境为 NDK 的编译器环境，所以需要对 Android 设置为 NDK 下面的编译器路径。
#    set(CMAKE_C_COMPILER clang)
#    set(CMAKE_CXX_COMPILER clang++)

    # 最低支持的 iOS 版本
#    set(CMAKE_XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "8.1")

    # 支持的指令架构
#    set(CMAKE_OSX_ARCHITECTURES "armv7 arm64")

    # 使用哪个 iOS SDK 进行打包，这里需要注意是对 iPhone 真机打包还是 iPhone 模拟器打包，二者的 SDK 是不同的。
    # 我们这里使用的是 iPhone 真机的 SDK。
#    set(CMAKE_OSX_SYSROOT/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS11.0.sdk)

    # 设置代码库的输出路径
#    set(OUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/out/iOS/)

elseif(ANDROID)
    message("ANDROID")
#    add_library(mylog SHARED ${SOURCE_FILES})

    # 由于 Unity 在 Android 下面对 C++ 只支持 .so 的动态库格式，
    # 而如果你用 Mac 机编译时，默认的动态库格式为 .dylib,
    # 所以我们需要显示的使用 .so 后缀。
#    set_target_properties(mylog PROPERTIES SUFFIX ".so")

    # 设置代码库的输出路径
#    set(OUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/out/Android/${ANDROID_ABI}/)

else()
    message("else")
#    add_library(mylog STATIC ${SOURCE_FILES})
#    set(CMAKE_C_COMPILER clang)
#    set(CMAKE_CXX_COMPILER clang++)
#    set(OUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/out/else/)
endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUT_PATH})    #动态库
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUT_PATH})    #静态库

# 设置代码库的输出路径, 对 Debug 和 Release 模式都设置成同一个路径
set_target_properties(${PROJECT_NAME} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${OUT_PATH}
        ARCHIVE_OUTPUT_DIRECTORY ${OUT_PATH}
        LIBRARY_OUTPUT_DIRECTORY_RELEASE ${OUT_PATH}
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OUT_PATH}
        LIBRARY_OUTPUT_DIRECTORY_DEBUG ${OUT_PATH}
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OUT_PATH}
)

set_target_properties(${PROJECT_NAME}_static PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${OUT_PATH}
        ARCHIVE_OUTPUT_DIRECTORY ${OUT_PATH}
        LIBRARY_OUTPUT_DIRECTORY_RELEASE ${OUT_PATH}
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OUT_PATH}
        LIBRARY_OUTPUT_DIRECTORY_DEBUG ${OUT_PATH}
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OUT_PATH}
)

link_directories(${OUT_PATH})

add_executable(testnetwork main.cpp)
target_link_libraries(testnetwork uv flatbuffers ${PROJECT_NAME}_static)