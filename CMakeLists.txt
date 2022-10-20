cmake_minimum_required(VERSION 3.23)
project(victoriam)

set(CMAKE_CXX_STANDARD 17)

include_directories(PublicCode /opt/homebrew/Cellar/glfw/3.3.8/include /Users/old_cd_rom/VulkanSDK/1.3.224.1/macOS/include)

set(SOURCE_FILES
        PublicCode/Victoriam/Core/CBase.hpp
        PublicCode/Victoriam/EngineInfo.hpp
        PublicCode/Victoriam/Application/AAppState.hpp
        PublicCode/Victoriam/Application/AAppStateController.hpp
        PublicCode/Victoriam/Core/Memory/MStandardAllocator.hpp
        PublicCode/Victoriam/Core/CMacroDefinitions.hpp
        PublicCode/Victoriam/Core/Memory/MSmartPointers.hpp
        PublicCode/Victoriam/Application/AStartPoint.hpp
        PublicCode/Victoriam/Application/AStartPoint.hpp
        PublicCode/Victoriam/Application/ARuntimeApp.hpp
        PublicCode/Victoriam/Application/AArgumentLineTool.hpp
        PublicCode/Victoriam/Application/ARuntimeAppCreateInfo.hpp
        PublicCode/Victoriam/Graphics/GWindow.hpp
        PublicCode/Victoriam/Graphics/Structs/GWindowCreateInfo.hpp
        PublicCode/Victoriam/Math/Common/Scalar.hpp
        PublicCode/Victoriam/Math/Common/MinMax.hpp
        PublicCode/Victoriam/Math/Common/ScalarArray.hpp
        PublicCode/Victoriam/Math/Common/Comparator.hpp
        PublicCode/Victoriam/Math/Vector/VectorBase.hpp
        PublicCode/Victoriam/Math/Vector/TypeVector2.hpp
        PublicCode/Victoriam/Math/Vector/TypeVector3.hpp
        PublicCode/Victoriam/Math/Vector/TypeVector4.hpp
        PublicCode/Victoriam/Math/Vector/FuncVector2.hpp
        PublicCode/Victoriam/Math/MVector2.hpp
        PublicCode/Victoriam/Core/CFlags.hpp
        PublicCode/Victoriam/EventSystem/EEvent.hpp
        PublicCode/Victoriam/EventSystem/EEventDispatcher.hpp
        PublicCode/Victoriam/EventSystem/EWindowEvents.hpp
        PublicCode/Victoriam/Input/IKeycode.hpp
        PublicCode/Victoriam/Input/IMousecode.hpp
        PublicCode/Victoriam/Input/IPadcode.hpp
        PublicCode/Victoriam/Input/IPadaxis.hpp
        PublicCode/Victoriam/Core/CCast.hpp
        PublicCode/Victoriam/Input/IInput.hpp
        PublicCode/Victoriam/Utils/UShaderCooker.hpp
        PublicCode/Victoriam/Graphics/Basics.hpp
        PublicCode/Victoriam/Graphics/GDevice.hpp
        PublicCode/Victoriam/Graphics/GPipeline.hpp
        PublicCode/Victoriam/Graphics/Structs/GPipelineCreateInfo.hpp
        SourceCode/VulkanDevice.hpp
        SourceCode/Accessors/AWindow.hpp
        SourceCode/VulkanPipeline.hpp
        SourceCode/Accessors/ADevice.hpp
        SourceCode/GLFWWindow.hpp

        SourceCode/EngineInfo.cpp
        SourceCode/AAppStateController.cpp
        SourceCode/ARuntimeApp.cpp
        SourceCode/Comparator.cpp
        SourceCode/FuncVector2.cpp
        SourceCode/ScalarRsqrt.cpp
        SourceCode/GWindow.cpp
        SourceCode/GLFWWindow.cpp
        SourceCode/IInput.cpp
        SourceCode/UShaderCooker.cpp
        SourceCode/GDevice.cpp
        SourceCode/VulkanDevice.cpp
        SourceCode/GPipeline.cpp
        SourceCode/VulkanPipeline.cpp
        PublicCode/Victoriam/Graphics/GSwapchain.hpp SourceCode/GSwapchain.cpp SourceCode/VulkanSwapchain.cpp SourceCode/VulkanSwapchain.hpp SourceCode/Accessors/ASwapchain.hpp PublicCode/Victoriam/Graphics/GRenderer.hpp PublicCode/Victoriam/Graphics/Structs/GRendererCreateInfo.hpp SourceCode/GRenderer.cpp PublicCode/Victoriam/Graphics/GDrawCommandBuffer.hpp SourceCode/GDrawCommandBuffer.cpp SourceCode/VulkanDrawCommandBuffer.cpp SourceCode/VulkanDrawCommandBuffer.hpp SourceCode/Accessors/APipeline.hpp SourceCode/VulkanRenderer.cpp SourceCode/VulkanRenderer.hpp SourceCode/Accessors/ADrawCommandBuffer.hpp PublicCode/Victoriam/Graphics/Structs/GWindowExtent.hpp PublicCode/Victoriam/Utils/UCryptogen.hpp SourceCode/UCryptogen.cpp PublicCode/Victoriam/Utils/UFile.hpp SourceCode/UFile.cpp PublicCode/Victoriam/Graphics/GVertexBuffer.hpp PublicCode/Victoriam/Graphics/Structs/GVertex.hpp SourceCode/VulkanVertex.hpp SourceCode/GVertexBuffer.cpp SourceCode/VulkanVertexBuffer.cpp SourceCode/VulkanVertexBuffer.hpp SourceCode/Accessors/AVertexBuffer.hpp)

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
        PublicCode/VIsual/VEditorState.hpp

        SourceCode/VIsual/VEditorState.cpp
        SourceCode/VIsual/VIsualApp.cpp
)

add_executable(VIsual ${VISUAL_SOURCES})
target_link_libraries(VIsual victoriam)
