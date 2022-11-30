cmake_minimum_required(VERSION 3.23)
project(victoriam)

set(CMAKE_CXX_STANDARD 17)

include_directories(PublicCode /opt/homebrew/Cellar/glfw/3.3.8/include ThirdParty /Users/old_cd_rom/VulkanSDK/1.3.224.1/macOS/include)

set(SOURCE_FILES
        PublicCode/Victoriam/Application/AAppState.hpp
        PublicCode/Victoriam/Application/AAppStateChain.hpp
        PublicCode/Victoriam/Application/AArgumentLineTool.hpp
        PublicCode/Victoriam/Application/ARuntimeInstanceCreateInfo.hpp
        PublicCode/Victoriam/Application/ARuntimeInstance.hpp
        PublicCode/Victoriam/Application/AStartPoint.hpp
        PublicCode/Victoriam/Application/AStartPoint.hpp
        PublicCode/Victoriam/Core/CBase.hpp
        PublicCode/Victoriam/Core/CCast.hpp
        PublicCode/Victoriam/Core/CFlags.hpp
        PublicCode/Victoriam/Core/CLog.hpp
        PublicCode/Victoriam/Core/CMacroDefinitions.hpp
        PublicCode/Victoriam/Core/CNumerics.hpp
        PublicCode/Victoriam/Core/CUtils.hpp
        PublicCode/Victoriam/Core/Containers/CArray.hpp
        PublicCode/Victoriam/Core/Memory/MSmartPointers.hpp
        PublicCode/Victoriam/Core/Memory/MStandardAllocator.hpp
        PublicCode/Victoriam/Core/Memory/MUtils.hpp
        PublicCode/Victoriam/EngineInfo.hpp
        PublicCode/Victoriam/EventSystem/EEvent.hpp
        PublicCode/Victoriam/EventSystem/EEventDispatcher.hpp
        PublicCode/Victoriam/EventSystem/EWindowEvents.hpp
        PublicCode/Victoriam/Graphics/Basics.hpp
        PublicCode/Victoriam/Graphics/GBuffer.hpp
        PublicCode/Victoriam/Graphics/GCamera.hpp
        PublicCode/Victoriam/Graphics/GDescriptorPool.hpp
        PublicCode/Victoriam/Graphics/GDescriptorSetLayout.hpp
        PublicCode/Victoriam/Graphics/GDescriptorWriter.hpp
        PublicCode/Victoriam/Graphics/GFramebuffer.hpp
        PublicCode/Victoriam/Graphics/GGeometryData.hpp
        PublicCode/Victoriam/Graphics/GGraphicsContext.hpp
        PublicCode/Victoriam/Graphics/GIndexBuffer.hpp
        PublicCode/Victoriam/Graphics/GPipeline.hpp
        PublicCode/Victoriam/Graphics/GRenderPass.hpp
        PublicCode/Victoriam/Graphics/GRenderSubrender.hpp
        PublicCode/Victoriam/Graphics/GRenderer.hpp
        PublicCode/Victoriam/Graphics/GSwapchain.hpp
        PublicCode/Victoriam/Graphics/GUniformBuffer.hpp
        PublicCode/Victoriam/Graphics/GVertexBuffer.hpp
        PublicCode/Victoriam/Graphics/GWindow.hpp
        PublicCode/Victoriam/Graphics/Structs/GDescriptorPoolCreateInfo.hpp
        PublicCode/Victoriam/Graphics/Structs/GDescriptorSetLayoutCreateInfo.hpp
        PublicCode/Victoriam/Graphics/Structs/GFrameInfo.hpp
        PublicCode/Victoriam/Graphics/Structs/GFramebufferCreateInfo.hpp
        PublicCode/Victoriam/Graphics/Structs/GGeometryDataCreateInfo.hpp
        PublicCode/Victoriam/Graphics/Structs/GMaterialData.hpp
        PublicCode/Victoriam/Graphics/Structs/GPipelineCreateInfo.hpp
        PublicCode/Victoriam/Graphics/Structs/GPointLightsData.hpp
        PublicCode/Victoriam/Graphics/Structs/GRenderPassCreateInfo.hpp
        PublicCode/Victoriam/Graphics/Structs/GRendererConstants.hpp
        PublicCode/Victoriam/Graphics/Structs/GRendererCreateInfo.hpp
        PublicCode/Victoriam/Graphics/Structs/GVertex.hpp
        PublicCode/Victoriam/Graphics/Structs/GWindowCreateInfo.hpp
        PublicCode/Victoriam/Graphics/Structs/GWorldRendererSettings.hpp
        PublicCode/Victoriam/IO/IOInput.hpp
        PublicCode/Victoriam/IO/IOKeycode.hpp
        PublicCode/Victoriam/IO/IOMousecode.hpp
        PublicCode/Victoriam/IO/IOPadaxis.hpp
        PublicCode/Victoriam/IO/IOPadcode.hpp
        PublicCode/Victoriam/Matemia/Base/Base.hpp
        PublicCode/Victoriam/Matemia/Base/Random.hpp
        PublicCode/Victoriam/Matemia/Base/Scalar.hpp
        PublicCode/Victoriam/Matemia/Bounding/AABB.hpp
        PublicCode/Victoriam/Matemia/Bounding/Sphere.hpp
        PublicCode/Victoriam/Matemia/Bounding/Volume.hpp
        PublicCode/Victoriam/Matemia/Common/Functions.hpp
        PublicCode/Victoriam/Matemia/Common/Hash.hpp
        PublicCode/Victoriam/Matemia/MFrustum.hpp
        PublicCode/Victoriam/Matemia/MMath.hpp
        PublicCode/Victoriam/Matemia/MMatrix4.hpp
        PublicCode/Victoriam/Matemia/MPlane.hpp
        PublicCode/Victoriam/Matemia/MPoint.hpp
        PublicCode/Victoriam/Matemia/MQuaternion.hpp
        PublicCode/Victoriam/Matemia/MVector2.hpp
        PublicCode/Victoriam/Matemia/MVector3.hpp
        PublicCode/Victoriam/Matemia/MVector4.hpp
        PublicCode/Victoriam/Utils/UCompression.hpp
        PublicCode/Victoriam/Utils/UCryptogen.hpp
        PublicCode/Victoriam/IO/IOFile.hpp
        PublicCode/Victoriam/Utils/UGeometryBuilder.hpp
        PublicCode/Victoriam/Utils/UGeometryPacker.hpp
        PublicCode/Victoriam/Utils/UHash.hpp
        PublicCode/Victoriam/Utils/UShaderCooker.hpp
        PublicCode/Victoriam/Utils/UTimestep.hpp
        PublicCode/Victoriam/World/Components/ComponentBase.hpp
        PublicCode/Victoriam/World/Components/ComponentCamera.hpp
        PublicCode/Victoriam/World/Components/ComponentName.hpp
        PublicCode/Victoriam/World/Components/ComponentPointLight.hpp
        PublicCode/Victoriam/World/Components/ComponentRenderable.hpp
        PublicCode/Victoriam/World/Components/ComponentSun.hpp
        PublicCode/Victoriam/World/Components/ComponentTransform.hpp
        PublicCode/Victoriam/World/Components/Components.hpp
        PublicCode/Victoriam/World/WGameObject.hpp
        PublicCode/Victoriam/World/WWorld.hpp
        SourceCode/Accessors/ADescriptorPool.hpp
        SourceCode/Accessors/ADescriptorSetLayout.hpp
        SourceCode/Accessors/ADescriptorWriter.hpp
        SourceCode/Accessors/AFramebuffer.hpp
        SourceCode/Accessors/AGraphicsContext.hpp
        SourceCode/Accessors/AIndexBuffer.hpp
        SourceCode/Accessors/ARenderPass.hpp
        SourceCode/Accessors/ASwapchain.hpp
        SourceCode/Accessors/AUniformBuffer.hpp
        SourceCode/Accessors/AVertexBuffer.hpp
        SourceCode/Accessors/AWindow.hpp
        SourceCode/Compression/LZ4Backend.h
        SourceCode/GLFWWindow.hpp
        SourceCode/RendererSubrenders/DefaultRenderSubrender.hpp
        SourceCode/RendererSubrenders/PointLightSubrender.hpp
        SourceCode/VulkanBackend/VulkanDescriptorPool.hpp
        SourceCode/VulkanBackend/VulkanDescriptorSetLayout.hpp
        SourceCode/VulkanBackend/VulkanDescriptorWriter.hpp
        SourceCode/VulkanBackend/VulkanFramebuffer.hpp
        SourceCode/VulkanBackend/VulkanGraphicsContext.hpp
        SourceCode/VulkanBackend/VulkanMemoryBuffer.hpp
        SourceCode/VulkanBackend/VulkanPipeline.hpp
        SourceCode/VulkanBackend/VulkanRenderPass.hpp
        SourceCode/VulkanBackend/VulkanRenderer.hpp
        SourceCode/VulkanBackend/VulkanSwapchain.hpp
        SourceCode/VulkanBackend/VulkanUniformBuffer.hpp
        SourceCode/VulkanBackend/VulkanVertex.hpp
        SourceCode/VulkanBackend/VulkanVertexBuffer.hpp

        SourceCode/AAppStateChain.cpp
        SourceCode/ARuntimeInstance.cpp
        SourceCode/Compression/LZ4Backend.cpp
        SourceCode/Compression/UCompression.cpp
        SourceCode/EngineInfo.cpp
        SourceCode/GCamera.cpp
        SourceCode/GDescriptorPool.cpp
        SourceCode/GDescriptorPoolCreateInfo.cpp
        SourceCode/GDescriptorSetLayout.cpp
        SourceCode/GDescriptorSetLayoutCreateInfo.cpp
        SourceCode/GDescriptorWriter.cpp
        SourceCode/GFramebuffer.cpp
        SourceCode/GGeometryData.cpp
        SourceCode/GGraphicsContext.cpp
        SourceCode/GIndexBuffer.cpp
        SourceCode/GLFWWindow.cpp
        SourceCode/GPipeline.cpp
        SourceCode/GRenderPass.cpp
        SourceCode/GRenderSubrender.cpp
        SourceCode/GRenderer.cpp
        SourceCode/GSwapchain.cpp
        SourceCode/GUniformBuffer.cpp
        SourceCode/GVertex.cpp
        SourceCode/GVertexBuffer.cpp
        SourceCode/GWindow.cpp
        SourceCode/IOInput.cpp
        SourceCode/Matemia/AABB.cpp
        SourceCode/Matemia/MatrixFunctions.cpp
        SourceCode/Matemia/QuaternionFunctions.cpp
        SourceCode/Matemia/Random.cpp
        SourceCode/Matemia/Scalar.cpp
        SourceCode/Matemia/Sphere.cpp
        SourceCode/RendererSubrenders/DefaultRenderSubrender.cpp
        SourceCode/RendererSubrenders/PointLightSubrender.cpp
        SourceCode/UCryptogen.cpp
        SourceCode/UFile.cpp
        SourceCode/UGeometryBuilder.cpp
        SourceCode/UGeometryPacker.cpp
        SourceCode/UShaderCooker.cpp
        SourceCode/VulkanBackend/VulkanDescriptorPool.cpp
        SourceCode/VulkanBackend/VulkanDescriptorSetLayout.cpp
        SourceCode/VulkanBackend/VulkanDescriptorWriter.cpp
        SourceCode/VulkanBackend/VulkanFramebuffer.cpp
        SourceCode/VulkanBackend/VulkanGraphicsContext.cpp
        SourceCode/VulkanBackend/VulkanIndexBuffer.cpp
        SourceCode/VulkanBackend/VulkanIndexBuffer.hpp
        SourceCode/VulkanBackend/VulkanMemoryBuffer.cpp
        SourceCode/VulkanBackend/VulkanPipeline.cpp
        SourceCode/VulkanBackend/VulkanRenderPass.cpp
        SourceCode/VulkanBackend/VulkanRenderer.cpp
        SourceCode/VulkanBackend/VulkanSwapchain.cpp
        SourceCode/VulkanBackend/VulkanUniformBuffer.cpp
        SourceCode/VulkanBackend/VulkanVertexBuffer.cpp
        SourceCode/WGameObject.cpp
        SourceCode/WWorld.cpp
        PublicCode/Victoriam/IO/IO.hpp PublicCode/Victoriam/IO/IOStream.hpp SourceCode/IOStream.cpp PublicCode/Victoriam/Core/CString.hpp PublicCode/Victoriam/Graphics/Structs/GImageCreateInfo.hpp PublicCode/Victoriam/Matemia/MExtent.hpp PublicCode/Victoriam/Graphics/GImage.hpp SourceCode/GImage.cpp SourceCode/VulkanBackend/VulkanImage.cpp SourceCode/VulkanBackend/VulkanImage.hpp SourceCode/Accessors/AImage.hpp PublicCode/Victoriam/Graphics/GImageView.hpp PublicCode/Victoriam/Graphics/Structs/GImageViewCreateInfo.hpp SourceCode/GImageView.cpp SourceCode/VulkanBackend/VulkanImageView.cpp SourceCode/VulkanBackend/VulkanImageView.hpp PublicCode/Victoriam/Core/Containers/CConstant.hpp PublicCode/Victoriam/Utils/UPathTracker.hpp SourceCode/UPathTracker.cpp ThirdParty/stb_image.h PublicCode/Victoriam/Graphics/Structs/GPictureMetrics.hpp PublicCode/Victoriam/Graphics/GPicture.hpp SourceCode/GPicture.cpp SourceCode/VulkanBackend/VulkanPicture.cpp SourceCode/VulkanBackend/VulkanPicture.hpp)

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
        PublicCode/Ved/VEditorState.hpp

        SourceCode/Ved/VIsualApp.cpp
        SourceCode/Ved/VEditorState.cpp
)

add_executable(VIsual ${VISUAL_SOURCES})
target_link_libraries(VIsual victoriam)
