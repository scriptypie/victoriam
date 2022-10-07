cmake_minimum_required(VERSION 3.23)
project(victoriam)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(SOURCE_FILES
        include/Victoriam/Core/Base.hpp
        include/Victoriam/EngineInfo.hpp
        include/Victoriam/Application/AppState.hpp
        include/Victoriam/Application/AppStateController.hpp
        include/Victoriam/Core/Memory/StandardAllocator.hpp

        src/EngineInfo.cpp
        src/AppStateController.cpp
        include/Victoriam/Core/MacroDefinitions.hpp include/Victoriam/Core/Memory/SmartPointers.hpp include/Victoriam/Application/StartPoint.hpp include/Victoriam/Application/StartPoint.hpp src/RuntimeApp.cpp include/Victoriam/Application/RuntimeApp.hpp include/Victoriam/Application/ArgumentLineTool.hpp include/Victoriam/Application/RuntimeAppCreateInfo.hpp)

add_library(victoriam ${SOURCE_FILES})
