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

include_directories(/usr/local/include/workflow/)
link_directories(/usr/local/lib)
#link_directories()

add_executable(QES
  http_server.h http_server.cpp main.cpp
)
target_link_libraries(QES Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(QES libworkflow.so)
