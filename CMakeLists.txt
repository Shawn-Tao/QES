cmake_minimum_required(VERSION 3.14)

project(QES LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 如果进行交叉编译
if(CMAKE_CROSSCOMPILING)
    message(STATUS "CORSSCOMPILE FOR AARCH64")
    # aarch64 cross compile
    link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/aarch64/libyaml.a)
    link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/lib/aarch64/libworkflow.a)
else()
    message(STATUS "COMPILE FOR X86")
    set(CMAKE_PREFIX_PATH "/home/shawntao/Qt/6.2.1/gcc_64")
    find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
    # import workflow
    include_directories(/usr/local/include/workflow/)
endif()

#import include
include_directories(${PROJECT_SOURCE_DIR}/include)

FILE(GLOB_RECURSE SOURCE_FILES src/*.c* include/*.h*)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if(CMAKE_CROSSCOMPILING)
    message(STATUS "CORSSCOMPILE FOR AARCH64")
else()
    target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core)
    target_link_libraries(${PROJECT_NAME} libworkflow.so)
    target_link_libraries(${PROJECT_NAME} libyaml-cppd.a)
endif()






