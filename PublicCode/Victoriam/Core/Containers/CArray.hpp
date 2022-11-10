//
// Created by Вячеслав Кривенко on 03.11.2022.
//

#ifndef VICTORIAM_CARRAY_HPP
#define VICTORIAM_CARRAY_HPP

#include <cassert>

#include <Victoriam/Core/CMacroDefinitions.hpp>

VISRCBEG

/**
 * Iterator class that handles iterator operations within array class.
 * @tparam TArray
 */
template<class TArray>
class VIDECL CArrayIterator
{
public:
	using ValueType = typename TArray::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
	using SizeType = typename TArray::SizeType;
public:
	VIDECL explicit CArrayIterator(PointerType position) : m_Position(position) {}
	VIDECL ~CArrayIterator() = default;

	VIDECL CArrayIterator& operator++()
	{
		m_Position++;
		return *this;
	}

	VIDECL CArrayIterator operator++(int)
	{
		auto iterator = *this;
		++(*this);
		return iterator;
	}

	VIDECL CArrayIterator& operator--()
	{
		m_Position--;
		return *this;
	}

	VIDECL CArrayIterator operator--(int)
	{
		auto iterator = *this;
		--(*this);
		return iterator;
	}

	VIDECL ReferenceType operator[](SizeType index)
	{
		return *(m_Position + index);
	}

	VIDECL PointerType operator->()
	{
		return m_Position;
	}

	VIDECL ReferenceType operator*()
	{
		return *m_Position;
	}

	VIDECL bool operator==(const CArrayIterator& other)
	{
		return m_Position == other.m_Position;
	}

	VIDECL bool operator!=(const CArrayIterator& other)
	{
		return !((*this) == other);
	}

private:
	VIDECL PointerType m_Position;
};

/**
 * Array container class that handles standard array structure.
 * @tparam T Type of handled object.
 * @tparam N Capacity of array.
 */
template<class T, unsigned long N>
class VIDECL CArray
{
public:
	using ValueType = T;
	using SelfType = CArray<T, N>;
	using Iterator = CArrayIterator<SelfType>;
	using PointerType = ValueType*;
	using ConstPointerType = const ValueType*;
	using ReferenceType = ValueType&;
	using ConstReferenceType = const ValueType&;
	using SizeType = unsigned long;
public:
	VIDECL CArray() = default;
	VIDECL ~CArray() = default;

	template<SizeType IN>
	VIDECL explicit CArray(ValueType (&data)[IN])
	{
		assert(IN <= N);
		for (SizeType i = 0; i < IN; i++) m_Data[i] = data[i];
	}

	template<class...Args>
	VIDECL CArray(Args&&...args)
	{
		size_t counter = 0;
		((m_Data[counter++] = std::forward<Args>(args)), ...);
		assert(counter <= N);
	}

	/**
	 * Returns static size(capacity) of array.
	 */
	VIDECL VIREQOUT constexpr SizeType Size() const
	{
		return N;
	}

	/**
	 * Access to elements in array, starting with index 0.
	 * @param pos Position index [0...N]
	 * @return Reference to object.
	 */
	VIDECL VIREQOUT ReferenceType At(SizeType pos)
	{
		assert((pos <= N) && "Position out of array bounds!");
		return m_Data[pos];
	}

	/**
	 * Access to elements in array, starting with index 0.
	 * @param pos Position index [0...N]
	 * @return Constant reference to object.
	 */
	VIDECL VIREQOUT ConstReferenceType At(SizeType pos) const
	{
		assert((pos <= N) && "Position out of array bounds!");
		return m_Data[pos];
	}

	VIDECL VIREQOUT ReferenceType operator[](SizeType pos)
	{
		return m_Data[pos];
	}

	VIDECL VIREQOUT ConstReferenceType operator[](SizeType pos) const
	{
		return m_Data[pos];
	}

	/**
	 * Access to plain pointer of array.
	 */
	VIDECL VIREQOUT PointerType Data()
	{
		return m_Data;
	}

	/**
	 * Access to plain pointer of array.
	 */
	VIDECL VIREQOUT ConstPointerType Data() const
	{
		return m_Data;
	}

	VIDECL VIREQOUT Iterator begin()
	{
		return Iterator(m_Data);
	}

	VIDECL VIREQOUT Iterator end()
	{
		return Iterator(m_Data + N);
	}

private:
	VIDECL ValueType m_Data[N] = {};
};

VISRCEND

#endif //VICTORIAM_CARRAY_HPP
