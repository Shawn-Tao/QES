cmake_minimum_required(VERSION 3.14)

project(QES LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "/home/shawntao/Qt/6.2.1/gcc_64")

find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
# find_package(YAML)


link_directories(${PROJECT_SOURCE_DIR}/lib)

# import workflow
include_directories(/usr/local/include/workflow/)
link_directories(/usr/local/lib)

#import yaml
# include_directories(${PROJECT_SOURCE_DIR}/yaml/include)
# link_directories(${PROJECT_SOURCE_DIR}/yaml/lib)

#import include
include_directories(${PROJECT_SOURCE_DIR}/include)

FILE(GLOB_RECURSE SOURCE_FILES src/*.c* include/*.h*)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${PROJECT_NAME} libworkflow.so)
target_link_libraries(${PROJECT_NAME} libyaml-cpp.a)
