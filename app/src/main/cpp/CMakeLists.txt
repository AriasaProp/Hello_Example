cmake_minimum_required(VERSION 3.4.1)

project(ext LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE Include_Dir LIST_DIRECTORIES true ".")
include_directories(${Include_Dir})
file(GLOB_RECURSE Src_Files "*.cpp")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -O3")
add_library(native_app_glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")
add_library(${PROJECT_NAME} SHARED ${Src_Files})

target_include_directories(${PROJECT_NAME} PRIVATE ${ANDROID_NDK}/sources/android/native_app_glue)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_link_libraries(${PROJECT_NAME} android native_app_glue EGL GLESv1_CM log)


