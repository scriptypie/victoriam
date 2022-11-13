cmake_minimum_required(VERSION 3.23)
project(victoriam)

set(CMAKE_CXX_STANDARD 17)

include_directories(PublicCode /opt/homebrew/Cellar/glfw/3.3.8/include ThirdParty ThirdParty/imgui/include ThirdParty/assimp/include /Users/old_cd_rom/VulkanSDK/1.3.224.1/macOS/include)

find_library(ASSIMP_LIB assimp ThirdParty/assimp/lib)

set(SOURCE_FILES
        PublicCode/Victoriam/Core/CBase.hpp
        PublicCode/Victoriam/EngineInfo.hpp
        PublicCode/Victoriam/Application/AAppState.hpp
        PublicCode/Victoriam/Application/AAppStateChain.hpp
        PublicCode/Victoriam/Core/Memory/MStandardAllocator.hpp
        PublicCode/Victoriam/Core/CMacroDefinitions.hpp
        PublicCode/Victoriam/Core/Memory/MSmartPointers.hpp
        PublicCode/Victoriam/Application/AStartPoint.hpp
        PublicCode/Victoriam/Application/AStartPoint.hpp
        PublicCode/Victoriam/Application/ARuntimeInstance.hpp
        PublicCode/Victoriam/Application/AArgumentLineTool.hpp
        PublicCode/Victoriam/Application/ARuntimeInstaceCreateInfo.hpp
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
        PublicCode/Victoriam/Graphics/GGraphicsContext.hpp
        PublicCode/Victoriam/Graphics/GPipeline.hpp
        PublicCode/Victoriam/Graphics/Structs/GPipelineCreateInfo.hpp
        SourceCode/VulkanGraphicsContext.hpp
        SourceCode/Accessors/AWindow.hpp
        SourceCode/VulkanPipeline.hpp
        SourceCode/Accessors/AGraphicsContext.hpp
        SourceCode/GLFWWindow.hpp
        PublicCode/Victoriam/Graphics/GCmdBufferSolver.hpp
        SourceCode/VulkanCmdBufferSolver.hpp
        SourceCode/VulkanRenderer.hpp
        SourceCode/Accessors/ACmdBufferSolver.hpp
        PublicCode/Victoriam/Graphics/Structs/GWindowExtent.hpp
        PublicCode/Victoriam/Utils/UCryptogen.hpp
        PublicCode/Victoriam/Utils/UFile.hpp
        PublicCode/Victoriam/Graphics/Structs/GVertex.hpp
        SourceCode/VulkanVertex.hpp
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
        PublicCode/Victoriam/Graphics/GGeometryData.hpp
        PublicCode/Victoriam/Graphics/Structs/GGeometryDataCreateInfo.hpp
        PublicCode/Victoriam/Utils/UGeometryBuilder.hpp
        PublicCode/Victoriam/Utils/UJobWorker.hpp
        ThirdParty/tinyobjloader/TinyObjLoader.hpp
        PublicCode/Victoriam/Utils/UHash.hpp
        PublicCode/Victoriam/World/Components/ComponentSun.hpp
        PublicCode/Victoriam/Graphics/Structs/GWorldRendererSettings.hpp
        SourceCode/VulkanMemoryBuffer.hpp
        PublicCode/Victoriam/Graphics/GBuffer.hpp
        SourceCode/VulkanVertexBuffer.hpp
        PublicCode/Victoriam/Graphics/Structs/GRendererConstants.hpp
        PublicCode/Victoriam/Graphics/Structs/GFrameInfo.hpp
        PublicCode/Victoriam/Core/Containers/CArray.hpp
        PublicCode/Victoriam/Graphics/Structs/GDescriptorSetLayoutCreateInfo.hpp
        PublicCode/Victoriam/Graphics/GDescriptorSetLayout.hpp
        SourceCode/VulkanDescriptorSetLayout.hpp
        SourceCode/Accessors/ADescriptorSetLayout.hpp
        PublicCode/Victoriam/Graphics/Structs/GDescriptorPoolCreateInfo.hpp
        PublicCode/Victoriam/Graphics/GDescriptorPool.hpp
        SourceCode/VulkanDescriptorPool.hpp
        PublicCode/Victoriam/Graphics/GDescriptorWriter.hpp
        SourceCode/VulkanDescriptorWriter.hpp
        SourceCode/Accessors/ADescriptorPool.hpp
        SourceCode/Accessors/AVertexBuffer.hpp
        SourceCode/Accessors/ADescriptorWriter.hpp
        PublicCode/Victoriam/World/Components/ComponentPointLight.hpp
        PublicCode/Victoriam/Graphics/GRenderSubrender.hpp
        SourceCode/RendererSubrenders/DefaultRenderSubrender.hpp
        PublicCode/Victoriam/Graphics/GVertexBuffer.hpp
        PublicCode/Victoriam/Graphics/GIndexBuffer.hpp
        PublicCode/Victoriam/Graphics/GUniformBuffer.hpp
        SourceCode/VulkanUniformBuffer.hpp
        SourceCode/Accessors/AIndexBuffer.hpp
        SourceCode/Accessors/AUniformBuffer.hpp
        SourceCode/RendererSubrenders/PointLightSubrender.hpp

        SourceCode/EngineInfo.cpp
        SourceCode/AAppStateChain.cpp
        SourceCode/ARuntimeInstance.cpp
        SourceCode/GWindow.cpp
        SourceCode/GLFWWindow.cpp
        SourceCode/IInput.cpp
        SourceCode/UShaderCooker.cpp
        SourceCode/GGraphicsContext.cpp
        SourceCode/VulkanGraphicsContext.cpp
        SourceCode/GPipeline.cpp
        SourceCode/VulkanPipeline.cpp
        SourceCode/GSwapchain.cpp
        SourceCode/VulkanSwapchain.cpp
        SourceCode/GRenderer.cpp
        SourceCode/GCmdBufferSolver.cpp
        SourceCode/VulkanCmdBufferSolver.cpp
        SourceCode/VulkanRenderer.cpp
        SourceCode/UCryptogen.cpp
        SourceCode/UFile.cpp
        SourceCode/WGameObject.cpp
        SourceCode/WWorld.cpp
        SourceCode/GCamera.cpp
        SourceCode/GGeometryData.cpp
        SourceCode/UJobWorker.cpp
        SourceCode/UGeometryBuilder.cpp
        SourceCode/GVertex.cpp
        SourceCode/VulkanMemoryBuffer.cpp
        SourceCode/GVertexBuffer.cpp
        SourceCode/VulkanVertexBuffer.cpp
        SourceCode/GDescriptorSetLayoutCreateInfo.cpp
        SourceCode/GDescriptorSetLayout.cpp
        SourceCode/VulkanDescriptorSetLayout.cpp
        SourceCode/GDescriptorPoolCreateInfo.cpp
        SourceCode/GDescriptorPool.cpp
        SourceCode/VulkanDescriptorPool.cpp
        SourceCode/GDescriptorWriter.cpp
        SourceCode/VulkanDescriptorWriter.cpp
        SourceCode/GRenderSubrender.cpp
        SourceCode/RendererSubrenders/DefaultRenderSubrender.cpp
        SourceCode/GIndexBuffer.cpp
        SourceCode/VulkanIndexBuffer.cpp
        SourceCode/VulkanIndexBuffer.hpp
        SourceCode/GUniformBuffer.cpp
        SourceCode/VulkanUniformBuffer.cpp
        SourceCode/RendererSubrenders/PointLightSubrender.cpp

        ThirdParty/tinyobjloader/TinyObjLoader.cpp
        ThirdParty/imgui/src/ImGui/imgui.cpp
        ThirdParty/imgui/src/ImGui/imgui_impl_glfw.cpp
        ThirdParty/imgui/src/ImGui/imgui_impl_vulkan.cpp
        ThirdParty/imgui/src/ImGui/imgui_tables.cpp
        ThirdParty/imgui/src/ImGui/imgui_widgets.cpp
        ThirdParty/imgui/src/ImGui/imgui_draw.cpp
        ThirdParty/imgui/src/ImGui/imgui_demo.cpp
        PublicCode/Victoriam/Graphics/Structs/GPointLightsData.hpp PublicCode/Victoriam/Graphics/Structs/GRenderPassCreateInfo.hpp PublicCode/Victoriam/Graphics/GRenderPass.hpp SourceCode/VulkanRenderPass.cpp SourceCode/VulkanRenderPass.hpp)

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
