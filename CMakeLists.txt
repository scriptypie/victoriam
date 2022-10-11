cmake_minimum_required(VERSION 3.23)
project(victoriam)

set(CMAKE_CXX_STANDARD 17)

include_directories(include /opt/homebrew/Cellar/glfw/3.3.8/include)

set(SOURCE_FILES
        include/Victoriam/Core/Base.hpp
        include/Victoriam/EngineInfo.hpp
        include/Victoriam/Application/AppState.hpp
        include/Victoriam/Application/AppStateController.hpp
        include/Victoriam/Core/Memory/StandardAllocator.hpp
        include/Victoriam/Core/MacroDefinitions.hpp
        include/Victoriam/Core/Memory/SmartPointers.hpp
        include/Victoriam/Application/StartPoint.hpp
        include/Victoriam/Application/StartPoint.hpp
        include/Victoriam/Application/RuntimeApp.hpp
        include/Victoriam/Application/ArgumentLineTool.hpp
        include/Victoriam/Application/RuntimeAppCreateInfo.hpp

        src/EngineInfo.cpp
        src/AppStateController.cpp
        src/RuntimeApp.cpp
        include/Victoriam/Graphics/Window.hpp include/Victoriam/Graphics/WindowCreateInfo.hpp include/Victoriam/Math/Common/Scalar.hpp include/Victoriam/Math/Common/MinMax.hpp include/Victoriam/Math/Common/ScalarArray.hpp include/Victoriam/Math/Common/Comparator.hpp src/Comparator.cpp include/Victoriam/Math/Vector/VectorBase.hpp include/Victoriam/Math/Vector/TypeVector2.hpp include/Victoriam/Math/Vector/TypeVector3.hpp include/Victoriam/Math/Vector/TypeVector4.hpp include/Victoriam/Math/Vector/FuncVector2.hpp src/FuncVector2.cpp src/ScalarRsqrt.cpp include/Victoriam/Math/Vector2.hpp include/Victoriam/Core/Flags.hpp src/Window.cpp src/WindowGlfwImpl.cpp src/WindowGlfwImpl.hpp include/Victoriam/EventSystem/Event.hpp include/Victoriam/EventSystem/EventDispatcher.hpp include/Victoriam/EventSystem/WindowEvents.hpp include/Victoriam/Input/Keycode.hpp include/Victoriam/Input/Mousecode.hpp include/Victoriam/Input/Padcode.hpp include/Victoriam/Input/Padaxis.hpp include/Victoriam/Core/Cast.hpp include/Victoriam/Input/Input.hpp src/Input.cpp include/Victoriam/EventSystem/KeyboardEvents.hpp)

add_library(victoriam STATIC ${SOURCE_FILES})

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(victoriam PUBLIC glfw PUBLIC OpenGL::GL)

set(VISUAL_SOURCES
        include/VIsual/EditorState.hpp

        src/VIsual/EditorState.cpp
        src/VIsual/VIsualApp.cpp
)

add_executable(VIsual ${VISUAL_SOURCES})
target_link_libraries(VIsual victoriam)
