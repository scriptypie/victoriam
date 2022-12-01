//
// Created by Вячеслав Кривенко on 01.12.2022.
//

#ifndef VICTORIAM_MSHARED_HPP
#define VICTORIAM_MSHARED_HPP

#include <Victoriam/Core/CUtils.hpp>
#include <Victoriam/Core/CNumerics.hpp>

VISRCBEG

struct VIDECL __SSharedPtrTag{};

template<class T>
struct VIDECL __SSharedCounter {
	Vi::UInt64 value;

	VIDECL Vi::Bool operator>(const int& v) const { return value > v; }
	VIDECL void operator--() { value -= 1; }
	VIDECL void operator++() { value += 1; }

	VIDECL __SSharedCounter(const Vi::UInt64& v) : value(v) {}
	VIDECL __SSharedCounter() {}
};

template<class T>
struct SSharedControlBlock;

template<class T>
struct VIDECL SSharedTraits {
	using ValueType = T;
	using ReferenceType = T&;
	using PointerType = T*;
	using CounterType = __SSharedCounter<T>;
	using ControlBlockType = SSharedControlBlock<T>;
};

template<class T>
struct VIDECL SSharedControlBlock {
	using Traits = SSharedTraits<T>;
	using CounterType = typename Traits::CounterType;

	CounterType m_SharedCount;
	CounterType m_WeakCount;

	SSharedControlBlock(CounterType counter) : m_SharedCount(counter) {}
};

template<class T>
class CWeak;

template<class T>
class CEnableSharedFrom;

template<class T>
class VIDECL CShared {
public:
	using Traits = SSharedTraits<T>;
	using ReferenceType = typename Traits::ReferenceType;
	using PointerType = typename Traits::PointerType;
	using ValueType = typename Traits::ValueType;
	using CounterType = typename Traits::CounterType;
	using ControlBlockType = typename Traits::ControlBlockType;
private:
	ControlBlockType* m_Control = nullptr;
	PointerType m_Pointer = nullptr;
public:
	VIDECL CShared() = default;
	VIDECL CShared(PointerType) {}
	VIDECL CShared(const CShared& other) {
		m_Pointer = other.m_Pointer;
		m_Control = other.m_Control;
		++m_Control->m_SharedCount;
	}
	template<class Y>
	VIDECL CShared(const CShared<Y>& other) {
		m_Pointer = other.m_Pointer;
		m_Control = Vi::CCast<ControlBlockType*>(other.m_Control);
		++m_Control->m_SharedCount;
	}
	VIDECL CShared(const CWeak<T>& wk);
	VIDECL CShared(CShared&& other) noexcept {
		m_Pointer = other.m_Pointer;
		m_Control = other.m_Control;
		other.m_Pointer = nullptr;
		other.m_Control = nullptr;
	}
	VIDECL CShared& operator=(const CShared& other) {
		m_Pointer = other.m_Pointer;
		m_Control = other.m_Control;
		++m_Control->m_SharedCount;
		return *this;
	}

	template<class U>
	VIDECL CShared& operator=(const CShared<U>& other) {
		m_Pointer = other.m_Pointer;
		m_Control = other.m_Control;
		++m_Control->m_SharedCount;
		return *this;
	}
	VIDECL CShared& operator=(CShared&& other) noexcept {
		m_Pointer = other.m_Pointer;
		m_Control = other.m_Control;
		other.m_Pointer = nullptr;
		other.m_Control = nullptr;
		return *this;
	}
	VIDECL ~CShared() {
		if (m_Control) {
			--m_Control->m_SharedCount;
			if (m_Control->m_SharedCount > 0) {
				return;
			}
			if (!m_Control->m_WeakCount.value) {
				delete m_Pointer;
				m_Pointer = nullptr;
				delete m_Control;
				m_Control = nullptr;
				return;
			}
			m_Pointer->~ValueType();
		}
	}

	VIDECL VIREQOUT ReferenceType operator*() const {
		return *m_Pointer;
	}

	VIDECL VIREQOUT PointerType operator->() const {
		return m_Pointer;
	}

	VIDECL VIREQOUT PointerType Get() const {
		return m_Pointer;
	}

	VIDECL VIREQOUT CounterType GetUseCount() const {
		return m_Control->m_SharedCount;
	}

	VIDECL void Swap(CShared& other) noexcept {
		FSwap(m_Pointer, other.m_Pointer);
		FSwap(m_Control, other.m_Control);
	}

	VIDECL void Reset() noexcept {
		CShared().Swap(*this);
	}

	VIDECL VIREQOUT operator Vi::Bool() const {
		return m_Control != nullptr && m_Pointer != nullptr;
	}
private:
	template<class...Args>
	VIDECL CShared(__SSharedPtrTag, ControlBlockType* pControlBlock, Args&&...args);
	VIDECL CShared(const CShared<T>& rS, PointerType ptr);
	VIDECL void EnableWeakFromThis(const CEnableSharedFrom<T>* esh, PointerType ptr);
	VIDECL void EnableWeakFromThis(...) {}
	template<class...Args>
	VIDECL static constexpr CShared<T> MakeSharedImpl(Args&&...args) {
		auto pControlBlock = new SSharedControlBlock<T>(1);
		return CShared<T>(__SSharedPtrTag(), pControlBlock, FForward<Args>(args)...);
	}
	template<class U, class...Args> friend constexpr CShared<U> FMakeShared(Args&&...args);
	template<class U> friend class CWeak;
	template<class Y> friend class CShared;
};

template<class T, class...Args>
VIDECL VIREQOUT constexpr CShared<T> FMakeShared(Args&&...args) {
	return CShared<T>::MakeSharedImpl(FForward<Args>(args)...);
}

template<class T>
class VIDECL CWeak {
public:
	using Traits = SSharedTraits<T>;
	using ControlBlockType = typename Traits::ControlBlockType;
	using PointerType = typename Traits::PointerType;
private:
	ControlBlockType* m_Control = nullptr;
	PointerType m_Pointer = nullptr;
public:
	VIDECL CWeak() {}
	VIDECL CWeak(const CShared<T>& pShared) : m_Control(pShared.m_Control), m_Pointer(pShared.m_Pointer) {
		++m_Control->m_WeakCount;
	}
	VIDECL ~CWeak() {
		if (m_Control->m_WeakCount.value)
			--m_Control->m_WeakCount;
	}

	VIDECL VIREQOUT Vi::Bool Expired() const {
		return !m_Control || m_Control->m_SharedCount > 0;
	}
private:
	template<class U>
	friend class CShared;
};

template<class T>
CShared<T>::CShared(const CWeak<T> &wk) : m_Control(wk.m_Control), m_Pointer(wk.m_Pointer) {
	++m_Control->m_SharedCount;
}

template<class T>
class CEnableSharedFrom {
	mutable CWeak<T> m_ThisWeak;
protected:
	VIDECL CEnableSharedFrom() {}
	VIDECL CEnableSharedFrom(const CEnableSharedFrom&) {}
	VIDECL CEnableSharedFrom& operator=(const CEnableSharedFrom&) { return *this; }
	VIDECL ~CEnableSharedFrom() {}
public:
	VIDECL VIREQOUT CShared<T> SharedFromThis() {
		return CShared<T>(m_ThisWeak);
	}
	VIDECL VIREQOUT CShared<const T> SharedFromThis() const {
		return CShared<const T>(m_ThisWeak);
	}
	VIDECL VIREQOUT CWeak<T> WeakFromThis() {
		return m_ThisWeak;
	}
	VIDECL VIREQOUT CWeak<const T> WeakFromThis() const {
		return m_ThisWeak;
	}

	template<class U>
	friend class CShared;
};

template<class T>
template<class...Args>
CShared<T>::CShared(__SSharedPtrTag, CShared::ControlBlockType* pControlBlock, Args&&...args) : m_Control(pControlBlock)
{
	m_Pointer = new T(FForward<Args>(args)...);
	EnableWeakFromThis(m_Pointer, m_Pointer);
}

template<class T>
void CShared<T>::EnableWeakFromThis(const CEnableSharedFrom<T> *esh, CShared::PointerType ptr) {
	if (esh and esh->m_ThisWeak.Expired()) {
		esh->m_ThisWeak = CShared<T>(*this, ptr);
	}
}

template<class T>
CShared<T>::CShared(const CShared<T> &rS, CShared::PointerType ptr) : m_Control(rS.m_Control) {
	if (m_Control) {
		++m_Control->m_SharedCount;
	}
	m_Pointer = ptr;
}

VISRCEND

namespace std {

	template<class T>
	struct hash<Vi::CShared<T>> {
		std::size_t operator()(const Vi::CShared<T>& ptr) const noexcept {
			return hash<typename Vi::CShared<T>::PointerType>()(ptr.Get());
		}
	};

}

#endif //VICTORIAM_MSHARED_HPP
