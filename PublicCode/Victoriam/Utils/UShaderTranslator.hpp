//
// Created by Вячеслав Кривенко on 06.12.2022.
//

#ifndef VICTORIAM_USHADERTRANSLATOR_HPP
#define VICTORIAM_USHADERTRANSLATOR_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

	Constant<Signal, 0x00000001> TargetVertex;
	Constant<Signal, 0x00000010> TargetPixel;

/**
 * As expected, translate shader target from filename to output String, in SPIR-V syntax.
 */
	class VIDECL CShaderTranslator {
	public:
		VIDECL VIREQOUT String operator()(const String& source, const Signal& target);
	};

VISRCEND

#endif //VICTORIAM_USHADERTRANSLATOR_HPP
