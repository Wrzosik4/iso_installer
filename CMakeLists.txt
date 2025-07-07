cmake_minimum_required(VERSION 3.28)
project(iosInstaller)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Core REQUIRED)

add_executable(iosInstaller main.cpp)

target_link_libraries(iosInstaller PRIVATE Qt6::Widgets Qt6::Core)
