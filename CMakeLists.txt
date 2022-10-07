cmake_minimum_required(VERSION 3.23)
project(victoriam)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(victoriam library.cpp include/Victoriam/Core/Base.h include/Victoriam/EngineInfo.h src/EngineInfo.cpp)
