//
// Created by Вячеслав Кривенко on 04.12.2022.
//

#ifndef VICTORIAM_CSET_HPP
#define VICTORIAM_CSET_HPP

#include <Victoriam/Core/CUtils.hpp>
#include <Victoriam/Core/Memory/MStandardAllocator.hpp>
#include <Victoriam/Matemia/Base/Scalar.hpp>
#include <Victoriam/Core/CLog.hpp>

#include <vector>

VISRCBEG

template<class T, class Alloc>
class VIDECL CSet;

template<class T, class Alloc>
class VIDECL CSetIterator;

template<class T, class Alloc>
struct VIDECL SListTraits {
	using ValueType = T;
	using PointerType = T*;
	using ConstPointerType = const T*;
	using ReferenceType = T&;
	using ConstReferenceType = const T&;
	using SizeType = UInt64;
	using SelfType = CSet<T, Alloc>;
	using AllocatorType = Alloc;
	using IteratorType = typename std::vector<T, Alloc>::iterator;
	using ConstIteratorType = typename std::vector<T, Alloc>::const_iterator;
	using ReverseIteratorType = typename std::vector<T, Alloc>::reverse_iterator;
	using ConstReverseIteratorType = typename std::vector<T, Alloc>::const_reverse_iterator;
};

template<class T, class Alloc>
VIDECL VIREQOUT Bool operator==(const CSet<T, Alloc>& a, const CSet<T, Alloc>& b);

template<class T, class Alloc = StdAllocator<T>>
class VIDECL CSet {
public:
	using TraitsType = SListTraits<T, Alloc>;
	using SelfType = typename TraitsType::SelfType;
	using ValueType = typename TraitsType::ValueType;
	using PointerType = typename TraitsType::PointerType;
	using ReferenceType = typename TraitsType::ReferenceType;
	using ConstPointerType = typename TraitsType::ConstPointerType;
	using ConstReferenceType = typename TraitsType::ConstReferenceType;
	using SizeType = typename TraitsType::SizeType;
	using AllocatorType = typename TraitsType::AllocatorType;
	using IteratorType = typename TraitsType::IteratorType;
	using ConstIteratorType = typename TraitsType::ConstIteratorType;
	using ReverseIteratorType = typename TraitsType::ReverseIteratorType;
	using ConstReverseIteratorType = typename TraitsType::ConstReverseIteratorType;
private:
	std::vector<T, AllocatorType> m_Vector = {};
public:
	VIDECL CSet() = default;
	VIDECL ~CSet() = default;
	VIDECL CSet(SizeType n) : m_Vector(n) {}
	VIDECL CSet(SizeType n, ConstReferenceType v) : m_Vector(n, v) {}
	VIDECL CSet(PointerType f, PointerType l) : m_Vector(f, l) {}
	VIDECL CSet(const std::initializer_list<T>& list) : m_Vector(list) {}
	VIDECL CSet(const SelfType& other) : m_Vector(other.m_Vector) {}
	VIDECL CSet& operator=(const SelfType& other) { m_Vector = other.m_Vector; return *this; }
	VIDECL CSet(SelfType&& other) noexcept : m_Vector(other.m_Vector) {}
	VIDECL CSet& operator=(SelfType&& other) noexcept { m_Vector = other.m_Vector; return *this; }
	template<class...Args>
	VIDECL ReferenceType EmplaceBack(Args&&...args) {
		return m_Vector.template emplace_back(FForward<Args>(args)...);
	}
	template<class...Args>
	VIDECL IteratorType Emplace(IteratorType pos, Args&&...args) {
		return m_Vector.emplace(pos, FForward<Args>(args)...);
	}
	VIDECL IteratorType Insert(IteratorType pos, ConstReferenceType v) {
		return Emplace(pos, v);
	}
	VIDECL IteratorType Insert(ConstIteratorType pos, ValueType&& v) {
		return Emplace(pos, FForward<ValueType>(v));
	}
	VIDECL void Insert(IteratorType pos, SizeType n, ConstReferenceType v) {
		m_Vector.insert(pos, n, v);
	}
	VIDECL void PushBack(ConstReferenceType v) {
		m_Vector.push_back(v);
	}
	VIDECL void PushBack(ValueType&& v) {
		m_Vector.push_back(v);
	}
	VIDECL void PopBack() {
		m_Vector.pop_back();
	}
	VIDECL void Fit() {
		m_Vector.shrink_to_fit();
	}
	VIDECL void Reserve(SizeType n) {
		m_Vector.reserve(n);
	}
	VIDECL void Resize(SizeType n) {
		m_Vector.resize(n);
	}
	VIDECL void Resize(SizeType n, ConstReferenceType v) {
		m_Vector.resize(n, v);
	}
	VIDECL IteratorType Erase(IteratorType pos) {
		return m_Vector.erase(pos);
	}
	VIDECL IteratorType Erase(IteratorType f, IteratorType l) {
		return m_Vector.erase(f, l);
	}
	VIDECL void Clear() noexcept {
		m_Vector.clear();
	}
	VIDECL ReferenceType Back() {
		return m_Vector.back();
	}
	VIDECL VIREQOUT ConstReferenceType Back() const {
		return m_Vector.back();
	}
	VIDECL ReferenceType Front() {
		return m_Vector.front();
	}
	VIDECL VIREQOUT ConstReferenceType Front() const {
		return m_Vector.front();
	}
	VIDECL VIREQOUT SizeType Size() const noexcept {
		return m_Vector.size();
	}
	VIDECL VIREQOUT constexpr Bool Empty() const noexcept {
		return m_Vector.empty();
	}
	VIDECL VIREQOUT SizeType Capacity() const noexcept{
		return m_Vector.capacity();
	}
	VIDECL VIREQOUT ConstPointerType Data() const noexcept {
		return m_Vector.data();
	}
	VIDECL VIREQOUT PointerType Data() noexcept {
		return m_Vector.data();
	}
	VIDECL ReferenceType operator[](UInt64 n) {
		return m_Vector[n];
	}
	VIDECL ConstReferenceType operator[](UInt64 n) const {
		return m_Vector[n];
	}
	VIDECL ReferenceType At(UInt64 n) {
		return m_Vector.at(n);
	}
	VIDECL VIREQOUT ConstReferenceType At(UInt64 n) const {
		return m_Vector.at(n);
	}
	VIDECL VIREQOUT ConstIteratorType begin() const {
		return m_Vector.begin();
	}
	VIDECL IteratorType begin() {
		return m_Vector.begin();
	}
	VIDECL VIREQOUT ConstIteratorType end() const {
		return m_Vector.end();
	}
	VIDECL IteratorType end() {
		return m_Vector.end();
	}
	VIDECL VIREQOUT ConstReverseIteratorType rbegin() const {
		return m_Vector.rbegin();
	}
	VIDECL ReverseIteratorType rbegin() {
		return m_Vector.rbegin();
	}
	VIDECL VIREQOUT ConstReverseIteratorType rend() const {
		return m_Vector.rend();
	}
	VIDECL ReverseIteratorType rend() {
		return m_Vector.rend();
	}

	template<class U>
	friend Bool operator==(const CSet<U>& a, const CSet<U>& b);
};

template<class T, class Alloc>
VIDECL Bool operator==(const CSet<T, Alloc>& a, const CSet<T, Alloc>& b) {
	if (a.m_Size != b.m_Size) return false;
	for (auto i = 0; i < a.m_Size; i++)
		if (a.m_Array[i] != b.m_Array[i])
			return false;
	return true;
}

VISRCEND

#endif //VICTORIAM_CSET_HPP
