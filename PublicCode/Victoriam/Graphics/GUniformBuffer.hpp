//
// Created by Вячеслав Кривенко on 10.11.2022.
//

#ifndef VICTORIAM_GUNIFORMBUFFER_HPP
#define VICTORIAM_GUNIFORMBUFFER_HPP

#include <Victoriam/Graphics/GBuffer.hpp>
#include <Victoriam/Graphics/Structs/GRendererConstants.hpp>

VISRCBEG

class VIDECL CUniformBuffer : public CBuffer
{
public:
	VIDECL ~CUniformBuffer() override = default;
	/**
	 * Flush uniform buffer to GPU.
	 */
	VIDECL virtual void SubmitToGPU(const SRendererConstants& constants) = 0;

	VIDECL VIREQOUT static PUniformBuffer Create(PGraphicsContext& context, const UInt32& count);
};

VISRCEND

#endif //VICTORIAM_GUNIFORMBUFFER_HPP
