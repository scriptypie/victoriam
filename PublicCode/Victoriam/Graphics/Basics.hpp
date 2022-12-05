//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_BASICS_HPP
#define VICTORIAM_BASICS_HPP

#include <Victoriam/Graphics/Structs/GVertex.hpp>

VISRCBEG

/**
 * Opaque object that handles all commands to draw/transfer/etc...
 */
VIDECL typedef struct TSCommandBuffer* SCommandBuffer;
/**
 * Opaque object that handles created and associated descriptors.
 */
VIDECL typedef struct TSDescriptorSet* SDescriptorSet;

VIDECL typedef struct TSImageViewObject* SImageViewObject;


VIDECL typedef CUnique<class CDescriptorPool> PDescriptorPool;
VIDECL typedef CDescriptorPool DescriptorPool;
VIDECL typedef CUnique<class CDescriptorSetLayout> PDescriptorSetLayout;
VIDECL typedef CDescriptorSetLayout DescriptorSetLayout;
VIDECL typedef CShared<class CDescriptorWriter> PDescriptorWriter;
VIDECL typedef CDescriptorWriter DescriptorWriter;
VIDECL typedef CShared<class CFramebuffer> PFramebuffer;
VIDECL typedef CFramebuffer Framebuffer;
VIDECL typedef CShared<class CGraphicsContext> PGraphicsContext;
VIDECL typedef CGraphicsContext GraphicsContext;
VIDECL typedef CShared<class CImage> PImage;
VIDECL typedef CImage Image;
VIDECL typedef CShared<class CImageView> PImageView;
VIDECL typedef CImageView ImageView;
VIDECL typedef CShared<class CIndexBuffer> PIndexBuffer;
VIDECL typedef CIndexBuffer IndexBuffer;
VIDECL typedef CShared<class CPicture> PPicture;
VIDECL typedef CPicture Picture;
VIDECL typedef CUnique<class CPipeline> PPipeline;
VIDECL typedef CPipeline Pipeline;
VIDECL typedef CUnique<class CRenderer> PRenderer;
VIDECL typedef CRenderer Renderer;
VIDECL typedef CUnique<class CRenderPass> PRenderPass;
VIDECL typedef CRenderPass RenderPass;
VIDECL typedef CUnique<class CRenderSubrender> PRenderSubrender;
VIDECL typedef CRenderSubrender RenderSubrender;
VIDECL typedef CUnique<class CSwapchain> PSwapchain;
VIDECL typedef CSwapchain Swapchain;
VIDECL typedef CUnique<class CUniformBuffer> PUniformBuffer;
VIDECL typedef CUniformBuffer UniformBuffer;
VIDECL typedef CShared<class CVertexBuffer> PVertexBuffer;
VIDECL typedef CVertexBuffer VertexBuffer;
VIDECL typedef CShared<class CWindow> PWindow;
VIDECL typedef CWindow Window;

VISRCEND

#endif //VICTORIAM_BASICS_HPP
