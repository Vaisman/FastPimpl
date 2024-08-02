cmake_minimum_required(VERSION 3.10)

project(FastPimplTest VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/utils)

add_executable(FastPimplTest src/main.cpp)

target_include_directories(FastPimplTest PRIVATE ${PROJECT_SOURCE_DIR}/utils)
