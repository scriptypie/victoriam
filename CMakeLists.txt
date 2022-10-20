cmake_minimum_required(VERSION 3.23)
project(victoriam)

set(CMAKE_CXX_STANDARD 17)

include_directories(include /opt/homebrew/Cellar/glfw/3.3.8/include /Users/old_cd_rom/VulkanSDK/1.3.224.1/macOS/include)

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
        include/Victoriam/Graphics/Window.hpp
        include/Victoriam/Graphics/WindowCreateInfo.hpp
        include/Victoriam/Math/Common/Scalar.hpp
        include/Victoriam/Math/Common/MinMax.hpp
        include/Victoriam/Math/Common/ScalarArray.hpp
        include/Victoriam/Math/Common/Comparator.hpp
        include/Victoriam/Math/Vector/VectorBase.hpp
        include/Victoriam/Math/Vector/TypeVector2.hpp
        include/Victoriam/Math/Vector/TypeVector3.hpp
        include/Victoriam/Math/Vector/TypeVector4.hpp
        include/Victoriam/Math/Vector/FuncVector2.hpp
        include/Victoriam/Math/Vector2.hpp
        include/Victoriam/Core/Flags.hpp
        include/Victoriam/EventSystem/Event.hpp
        include/Victoriam/EventSystem/EventDispatcher.hpp
        include/Victoriam/EventSystem/WindowEvents.hpp
        include/Victoriam/Input/Keycode.hpp
        include/Victoriam/Input/Mousecode.hpp
        include/Victoriam/Input/Padcode.hpp
        include/Victoriam/Input/Padaxis.hpp
        include/Victoriam/Core/Cast.hpp
        include/Victoriam/Input/Input.hpp
        include/Victoriam/Utils/ShaderCooker.hpp
        include/Victoriam/Graphics/Basics.hpp
        include/Victoriam/Graphics/Device.hpp
        include/Victoriam/Graphics/Pipeline.hpp
        include/Victoriam/Graphics/PipelineCreateInfo.hpp
        src/VulkanDevice.hpp
        src/Accessors/AWindow.hpp
        src/VulkanPipeline.hpp
        src/Accessors/ADevice.hpp
        src/GLFWWindow.hpp

        src/EngineInfo.cpp
        src/AppStateController.cpp
        src/RuntimeApp.cpp
        src/Comparator.cpp
        src/FuncVector2.cpp
        src/ScalarRsqrt.cpp
        src/Window.cpp
        src/GLFWWindow.cpp
        src/Input.cpp
        src/ShaderCooker.cpp
        src/Device.cpp
        src/VulkanDevice.cpp
        src/Pipeline.cpp
        src/VulkanPipeline.cpp
        include/Victoriam/Graphics/Swapchain.hpp src/Swapchain.cpp src/VulkanSwapchain.cpp src/VulkanSwapchain.hpp src/Accessors/ASwapchain.hpp include/Victoriam/Graphics/Renderer.hpp include/Victoriam/Graphics/RendererCreateInfo.hpp src/Renderer.cpp include/Victoriam/Graphics/DrawCommandBuffer.hpp src/DrawCommandBuffer.cpp src/VulkanDrawCommandBuffer.cpp src/VulkanDrawCommandBuffer.hpp src/Accessors/APipeline.hpp src/VulkanRenderer.cpp src/VulkanRenderer.hpp src/Accessors/ADrawCommandBuffer.hpp include/Victoriam/Graphics/WindowExtent.hpp include/Victoriam/Utils/Cryptogen.hpp src/Cryptogen.cpp include/Victoriam/Utils/File.hpp src/File.cpp)

add_library(victoriam STATIC ${SOURCE_FILES})

if(CMAKE_BUILD_TYPE==Debug)
    target_compile_definitions(victoriam PUBLIC -D_DEBUG=1)
elseif(CMAKE_BUILD_TYPE==Release)
    target_compile_definitions(victoriam PUBLIC -DNDEBUG=1)
endif()

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)

target_link_libraries(victoriam PUBLIC glfw PUBLIC OpenGL::GL PUBLIC Vulkan::Vulkan)

set(VISUAL_SOURCES
        include/VIsual/EditorState.hpp

        src/VIsual/EditorState.cpp
        src/VIsual/VIsualApp.cpp
)

add_executable(VIsual ${VISUAL_SOURCES})
target_link_libraries(VIsual victoriam)
