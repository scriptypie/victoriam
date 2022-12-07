//
// Created by Вячеслав Кривенко on 06.12.2022.
//

#ifndef VICTORIAM_CUNIFORM_HPP
#define VICTORIAM_CUNIFORM_HPP

#include <Victoriam/Core/CCast.hpp>
#include <Victoriam/Core/CNumerics.hpp>

VISRCBEG

namespace Uniform_Impl {

	struct VIDECL BasicStorage {
		VIDECL virtual BasicStorage* Clone() = 0;
		VIDECL VIREQOUT virtual void* GetPtr() const = 0;
		VIDECL virtual ~BasicStorage() = default;
	};

	template<class T>
	struct VIDECL UniformStorage : BasicStorage {
		T OBJECT;

		VIDECL explicit UniformStorage(T value) : OBJECT(value) {}
		VIDECL BasicStorage* Clone() override { return new UniformStorage<T>(OBJECT); }
		VIDECL VIREQOUT void* GetPtr() const override { return Vi::CCast<void*>(&OBJECT); }
	};

}

/**
* CUniform - class-container with a dynamic data type.
* In other words - type can be changed at run-time.
*/
class VIDECL CUniform {
	Uniform_Impl::BasicStorage* m_Storage = nullptr;
public:
	VIDECL CUniform() : m_Storage() {}
	template<class T>
	VIDECL CUniform(const T& value) : m_Storage(new Uniform_Impl::UniformStorage<T>(value))  {}
	//VIDECL CUniform(const char* value) { // TODO: c-string support for CUniform!!!
	//	char* ptr = (char*)calloc(1, sizeof(char));
	//	strcat(ptr, value);
	//	m_Storage = new Uniform_Impl::UniformStorage<const char*>(ptr);
	//}
	VIDECL CUniform(const CUniform& other) : m_Storage(other.m_Storage->Clone()) {}
	VIDECL CUniform(CUniform&& other) : m_Storage(other.m_Storage->Clone()) {}
	VIDECL CUniform& operator=(const CUniform& other) {
		delete m_Storage;
		m_Storage = other.m_Storage->Clone();
		return *this;
	}
	VIDECL CUniform& operator=(CUniform&& other) {
		delete m_Storage;
		m_Storage = other.m_Storage->Clone();
		return *this;
	}
	template<class T>
	VIDECL CUniform& operator=(const T& value) {
		delete m_Storage;
		m_Storage = new Uniform_Impl::UniformStorage<T>(value);
		return *this;
	}
	VIDECL CUniform& operator=(const char* value) {
		delete m_Storage;
		m_Storage = new Uniform_Impl::UniformStorage<const char*>(value);
		return *this;
	}
	template<class T>
	VIDECL CUniform& operator=(T&& value) {
		delete m_Storage;
		m_Storage = new Uniform_Impl::UniformStorage<T>(value);
		return *this;
	}
	VIDECL ~CUniform() {
		delete m_Storage;
		m_Storage = nullptr;
	}
	template<class T>
	VIDECL VIREQOUT T Get() const {
		return *Vi::CCast<T*>(m_Storage->GetPtr());
	}
	VIDECL VIREQOUT Vi::Bool Empty() const {
		return !m_Storage;
	}
	VIDECL VIREQOUT Vi::Bool HasValue() const {
		return m_Storage;
	}
	VIDECL explicit operator Vi::Bool() const {
		return HasValue();
	}
};


VISRCEND

#endif //VICTORIAM_CUNIFORM_HPP
