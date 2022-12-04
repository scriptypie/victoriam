//
// Created by Вячеслав Кривенко on 03.12.2022.
//

#ifndef VICTORIAM_CFUNCTION_HPP
#define VICTORIAM_CFUNCTION_HPP

#include <Victoriam/Core/CLog.hpp>
#include <Victoriam/Core/Memory/MShared.hpp>

VISRCBEG

template<class T>
class CFunction;

template<class ReturnType, class...Args>
class VIDECL CFunction<ReturnType(Args...)> {
	class VIDECL CFunctionStorageBase {
	public:
		VIDECL CFunctionStorageBase() = default;
		VIDECL CFunctionStorageBase(const CFunctionStorageBase&) = delete;
		VIDECL void operator=(const CFunctionStorageBase&) = delete;
		VIDECL virtual ~CFunctionStorageBase() = default;
		VIDECL virtual ReturnType Invoke(Args&&...args) = 0;
		VIDECL virtual Vi::CShared<CFunctionStorageBase> Clone() = 0;
	};

	using InvokerType = Vi::CShared<CFunctionStorageBase>;

	template<class FunctionType>
	class CFreeFunctionStorage : public CFunctionStorageBase {
		FunctionType m_Function;
	public:
		VIDECL explicit CFreeFunctionStorage(FunctionType fn) : CFunctionStorageBase(), m_Function(fn) {}
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
		VIDECL explicit CMemberFunctionStorage(MemberFunctionSignatureType fn) : m_Function(fn) {}
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
			return;
		}
		ViAbort("Failed to connect function to CFunction: already in use! It required to Reset() function before new Connect(...)");
	}
	template<class FunctionType, class ObjectType>
	VIDECL void Connect(FunctionType ObjectType::* fn) {
		if (!m_Invoker) {
			m_Invoker = Vi::FMakeShared<CMemberFunctionStorage<FunctionType, Args&&...>>(fn);
			return;
		}
		ViAbort("Failed to connect function to CFunction: already in use! It required to Reset() function before new Connect(...)");
	}
	VIDECL ReturnType operator()(Args&&...args) {
		return m_Invoker->Invoke(Vi::FForward<Args>(args)...);
	}
	VIDECL VIREQOUT Vi::Bool Empty() const {
		return !m_Invoker;
	}
	VIDECL VIREQOUT explicit operator Vi::Bool() const {
		return m_Invoker;
	}
	VIDECL void Reset() {
		m_Invoker.Reset();
	}
};

VISRCEND

#endif //VICTORIAM_CFUNCTION_HPP
