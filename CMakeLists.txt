cmake_minimum_required(VERSION 3.23)
project(victoriam)

set(CMAKE_CXX_STANDARD 17)

include_directories(PublicCode /opt/homebrew/Cellar/glfw/3.3.8/include ThirdParty ThirdParty/imgui/include ThirdParty/assimp/include /Users/old_cd_rom/VulkanSDK/1.3.224.1/macOS/include)

find_library(ASSIMP_LIB assimp ThirdParty/assimp/lib)

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
        PublicCode/Victoriam/Graphics/GDrawCommandBuffer.hpp
        SourceCode/VulkanDrawCommandBuffer.hpp
        SourceCode/Accessors/APipeline.hpp
        SourceCode/VulkanRenderer.hpp
        SourceCode/Accessors/ADrawCommandBuffer.hpp
        PublicCode/Victoriam/Graphics/Structs/GWindowExtent.hpp
        PublicCode/Victoriam/Utils/UCryptogen.hpp
        PublicCode/Victoriam/Utils/UFile.hpp
        PublicCode/Victoriam/Graphics/GVertexBuffer.hpp
        PublicCode/Victoriam/Graphics/Structs/GVertex.hpp
        SourceCode/VulkanVertex.hpp
        SourceCode/VulkanVertexBuffer.hpp
        SourceCode/Accessors/AVertexBuffer.hpp
        PublicCode/Victoriam/Core/CLog.hpp
        PublicCode/Victoriam/Graphics/Structs/GMaterialData.hpp
        PublicCode/Victoriam/World/WGameObject.hpp
        PublicCode/Victoriam/World/WWorld.hpp
        PublicCode/Victoriam/World/Components/ComponentBase.hpp
        PublicCode/Victoriam/World/Components/ComponentRenderable.hpp
        PublicCode/Victoriam/World/Components/ComponentTransform.hpp
        SourceCode/Accessors/ASwapchain.hpp
        PublicCode/Victoriam/Graphics/GRenderer.hpp
        PublicCode/Victoriam/Graphics/Structs/GRendererCreateInfo.hpp
        SourceCode/VulkanSwapchain.hpp
        PublicCode/Victoriam/Graphics/GSwapchain.hpp
        PublicCode/Victoriam/World/Components/ComponentName.hpp
        PublicCode/Victoriam/World/Components/Components.hpp
        PublicCode/Victoriam/Graphics/GCamera.hpp
        PublicCode/Victoriam/World/Components/ComponentCamera.hpp
        PublicCode/Victoriam/Utils/UTimestep.hpp
        PublicCode/Victoriam/Graphics/GIndexBuffer.hpp
        SourceCode/VulkanIndexBuffer.hpp
        PublicCode/Victoriam/Graphics/GGeometryData.hpp
        PublicCode/Victoriam/Graphics/Structs/GGeometryDataCreateInfo.hpp
        PublicCode/Victoriam/Utils/UGeometryBuilder.hpp
        PublicCode/Victoriam/Utils/UJobWorker.hpp
        ThirdParty/tinyobjloader/TinyObjLoader.hpp
        PublicCode/Victoriam/Utils/UHash.hpp

        SourceCode/EngineInfo.cpp
        SourceCode/AAppStateController.cpp
        SourceCode/ARuntimeApp.cpp
        SourceCode/GWindow.cpp
        SourceCode/GLFWWindow.cpp
        SourceCode/IInput.cpp
        SourceCode/UShaderCooker.cpp
        SourceCode/GDevice.cpp
        SourceCode/VulkanDevice.cpp
        SourceCode/GPipeline.cpp
        SourceCode/VulkanPipeline.cpp
        SourceCode/GSwapchain.cpp
        SourceCode/VulkanSwapchain.cpp
        SourceCode/GRenderer.cpp
        SourceCode/GDrawCommandBuffer.cpp
        SourceCode/VulkanDrawCommandBuffer.cpp
        SourceCode/VulkanRenderer.cpp
        SourceCode/UCryptogen.cpp
        SourceCode/UFile.cpp
        SourceCode/GVertexBuffer.cpp
        SourceCode/VulkanVertexBuffer.cpp
        SourceCode/WGameObject.cpp
        SourceCode/WWorld.cpp
        SourceCode/GCamera.cpp
        SourceCode/GIndexBuffer.cpp
        SourceCode/VulkanIndexBuffer.cpp
        SourceCode/GGeometryData.cpp
        SourceCode/UJobWorker.cpp
        SourceCode/UGeometryBuilder.cpp
        ThirdParty/tinyobjloader/TinyObjLoader.cpp
        ThirdParty/imgui/src/ImGui/imgui.cpp
        ThirdParty/imgui/src/ImGui/imgui_impl_glfw.cpp
        ThirdParty/imgui/src/ImGui/imgui_impl_vulkan.cpp
        ThirdParty/imgui/src/ImGui/imgui_tables.cpp
        ThirdParty/imgui/src/ImGui/imgui_widgets.cpp
        ThirdParty/imgui/src/ImGui/imgui_draw.cpp
        ThirdParty/imgui/src/ImGui/imgui_demo.cpp
        SourceCode/GVertex.cpp)

add_library(victoriam STATIC ${SOURCE_FILES})

if(CMAKE_BUILD_TYPE==Debug)
    target_compile_definitions(victoriam PUBLIC -D_DEBUG=1)
elseif(CMAKE_BUILD_TYPE==Release)
    target_compile_definitions(victoriam PUBLIC -DNDEBUG=1)
endif()

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)

target_link_libraries(victoriam PUBLIC glfw PUBLIC OpenGL::GL PUBLIC Vulkan::Vulkan PUBLIC ${ASSIMP_LIB})

set(VISUAL_SOURCES
        PublicCode/Ved/VEditorState.hpp

        SourceCode/Ved/VEditorState.cpp
        SourceCode/Ved/VIsualApp.cpp
)

add_executable(VIsual ${VISUAL_SOURCES})
target_link_libraries(VIsual victoriam)
