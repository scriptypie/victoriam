//
// Created by Вячеслав Кривенко on 27.11.2022.
//

#ifndef VICTORIAM_CCONSTANT_HPP
#define VICTORIAM_CCONSTANT_HPP

#include <Victoriam/Core/CMacroDefinitions.hpp>

VISRCBEG

/*
 * The reason why I'm use custom class for constants instead of having them manually
 * is that manually set constant have a full Type size, while constant class of Type
 * have size of only 1 byte for some point. ://
 */
template<class T, T TValue>
class VIDECL SConstant {
public:
	using ValueType = T;
	using PointerType = T*;
private:
	VIDECL inline static const ValueType m_Value = TValue;
public:
	VIDECL constexpr operator ValueType() const {
		return m_Value;
	}
	VIDECL constexpr ValueType operator()() const {
		return m_Value;
	}
	VIDECL constexpr ValueType Get() const {
		return m_Value;
	}
	VIDECL constexpr ValueType Get() {
		return m_Value;
	}
	VIDECL PointerType Pointer() const {
		return &m_Value;
	}
	VIDECL PointerType Pointer() {
		return &m_Value;
	}
};

using STrueType = SConstant<bool, true>;
using SFalseType = SConstant<bool, false>;

VISRCEND

#define Constant VIDECL inline Vi::SConstant

#endif //VICTORIAM_CCONSTANT_HPP
