//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_CBASE_HPP
#define VICTORIAM_CBASE_HPP

#include <vector>
#include <tuple>
#include <functional>
#include <unordered_map>

#include <Victoriam/Core/Containers/CArray.hpp>
#include <Victoriam/Core/Containers/CConstant.hpp>
#include <Victoriam/Core/CLog.hpp>
#include <Victoriam/Core/CFlags.hpp>
#include <Victoriam/Core/Memory/MSmartPointers.hpp>
#include <Victoriam/Matemia/MMath.hpp> // Matemia math library (property of github.com/scriptypie)

VISRCBEG

template<class T>
using CList = std::vector<T, StdAllocator<T>>;

template<class...T>
using CTuple = std::tuple<T...>;

template<class...T, class...Args>
constexpr CTuple<T...> FCreateTuple(Args&&...args)
{
	return std::make_tuple<T...>(std::forward<Args>(args)...);
}

template<class K, class V>
using CHashTable = std::unordered_map<K, V>;

template<class T>
class CFunction;

template<class ReturnType, class...Args>
class VIDECL CFunction<ReturnType(Args...)> {
	class VIDECL CFunctionStorageBase {
		VIDECL CFunctionStorageBase(const CFunctionStorageBase&);
		VIDECL void operator=(const CFunctionStorageBase&);
	public:
		VIDECL CFunctionStorageBase() {}
		VIDECL virtual ~CFunctionStorageBase() {}
		VIDECL virtual ReturnType Invoke(Args&&...args) = 0;
		VIDECL virtual Vi::CShared<CFunctionStorageBase> Clone() = 0;
	};

	using InvokerType = Vi::CShared<CFunctionStorageBase>;

	template<class FunctionType>
	class CFreeFunctionStorage : public CFunctionStorageBase {
		FunctionType m_Function;
	public:
		VIDECL CFreeFunctionStorage(FunctionType fn) : CFunctionStorageBase(), m_Function(fn) {}
		VIDECL virtual ReturnType Invoke(Args&&...args) {
			return m_Function(Vi::FForward<Args>(args)...);
		}
		VIDECL virtual Vi::CShared<CFunctionStorageBase> Clone() {
			return InvokerType(Vi::FMakeShared<CFreeFunctionStorage>(m_Function));
		}
	};

	template<class FunctionType, class ObjectType, class...Rest>
	class CMemberFunctionStorage : public CFunctionStorageBase {
	public:
		using MemberFunctionSignatureType = FunctionType ObjectType::*;
	private:
		MemberFunctionSignatureType m_Function;
	public:
		VIDECL CMemberFunctionStorage(MemberFunctionSignatureType fn) : m_Function(fn) {}
		VIDECL virtual ReturnType Invoke(ObjectType obj, Rest&&...args) {
			return (obj.*m_Function)(Vi::FForward<Rest>(args)...);
		}
		VIDECL virtual Vi::CShared<CFunctionStorageBase> Clone() {
			return InvokerType(Vi::FMakeShared<CMemberFunctionStorage>(m_Function));
		}
	};

	InvokerType m_Invoker;
public:
	using SignatureType = ReturnType(Args&&...);

	VIDECL CFunction() : m_Invoker() {}
	template<class FunctionType>
	VIDECL CFunction(FunctionType fn) : m_Invoker(Vi::FMakeShared<CFreeFunctionStorage<FunctionType>>(fn)) {}
	template<class FunctionType, class ObjectType>
	VIDECL CFunction(FunctionType ObjectType::* fn) : m_Invoker(Vi::FMakeShared<CMemberFunctionStorage<FunctionType, Args&&...>>(fn)) {}
	VIDECL CFunction(const CFunction& other) : m_Invoker(other.m_Invoker->Clone()) {}
	VIDECL CFunction&operator=(const CFunction& other) {
		m_Invoker = other.m_Invoker->Clone();
		return *this;
	}
	template<class FunctionType>
	VIDECL void Connect(FunctionType fn) {
		if (!m_Invoker) {
			m_Invoker = Vi::FMakeShared<CFreeFunctionStorage<FunctionType>>(fn);
		}
		else {
			throw std::runtime_error("Failed to connect function to CFunction: already in use! It required to Reset() function before new Connect(...)");
		}
	}
	template<class FunctionType, class ObjectType>
	VIDECL void Connect(FunctionType ObjectType::* fn) {
		if (!m_Invoker) {
			m_Invoker = Vi::FMakeShared<CMemberFunctionStorage<FunctionType, Args&&...>>(fn);
		}
		else {
			throw std::runtime_error("Failed to connect function to CFunction: already in use! It required to Reset() function before new Connect(...)");
		}
	}
	VIDECL ReturnType operator()(Args&&...args) {
		return m_Invoker->Invoke(Vi::FForward<Args>(args)...);
	}
	VIDECL VIREQOUT Vi::Bool Empty() const {
		return !m_Invoker;
	}
	VIDECL VIREQOUT operator Vi::Bool() const {
		return m_Invoker;
	}
	VIDECL void Reset() {
		m_Invoker.Reset();
	}
};

VIDECL typedef CList<char> CBinaryData;

VISRCEND

#endif //VICTORIAM_CBASE_HPP
