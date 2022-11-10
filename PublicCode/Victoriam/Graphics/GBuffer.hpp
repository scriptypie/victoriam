//
// Created by Вячеслав Кривенко on 02.11.2022.
//

#ifndef VICTORIAM_GBUFFER_HPP
#define VICTORIAM_GBUFFER_HPP

#include <Victoriam/Graphics/Basics.hpp>

VISRCBEG

/**
 * Universal buffer object, that may be:
 * VertexBuffer, IndexBuffer, or even UniformBuffer.
 * Type depends of CreateXXXBuffer(...) constructor.
 */
class VIDECL CBuffer
{
public:
	VIDECL virtual ~CBuffer() = default;
	/**
	 * Binds current buffer to GPU.
	 */
	VIDECL virtual void Bind(const SCommandBuffer& buffer) {}
	/**
	 * Submit draw command to GPU.
	 */
	VIDECL virtual void Draw(const SCommandBuffer& buffer) const {}
};

VISRCEND

#endif //VICTORIAM_GVB_HPP
