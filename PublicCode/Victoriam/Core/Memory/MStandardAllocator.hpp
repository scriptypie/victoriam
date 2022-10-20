//
// Created by Вячеслав Кривенко on 07.10.2022.
//

#ifndef VICTORIAM_MSTANDARDALLOCATOR_HPP
#define VICTORIAM_MSTANDARDALLOCATOR_HPP

#include <cstdlib>
#include <cassert>
#include <numeric>

#include <Victoriam/Core/CMacroDefinitions.hpp>

VISRCBEG

template<class T>
class StdAllocator
{
public:
    VIDECL typedef T value_type;
    VIDECL typedef value_type* pointer;
    VIDECL typedef const value_type* const_pointer;
    VIDECL typedef value_type& reference;
    VIDECL typedef const value_type& const_reference;
    VIDECL typedef unsigned long long size_type;
    VIDECL typedef long difference_type;
public:
    template<class U> struct rebind
    {
        VIDECL typedef StdAllocator<U> other;
    };
public:
    inline StdAllocator() = default;
    inline ~StdAllocator() = default;
    inline StdAllocator(const StdAllocator&) = default;
    template<class U>
    inline explicit StdAllocator(const StdAllocator<U>&) {}

    VIDECL inline pointer address(reference r)
    {
        return &r;
    }
    VIDECL inline const_pointer address(const_reference r)
    {
        return &r;
    }
    VIDECL inline pointer allocate(size_type cnt, const void* block = nullptr)
    {
        auto ptr = (pointer)malloc(cnt * sizeof(value_type));
        assert(ptr && "StdAllocator error! Can't allocate memory!");
        return ptr;
    }
    VIDECL inline void deallocate(pointer p, size_type cnt)
    {
        free(p);
    }
    VIDECL VIREQOUT inline size_type max_size() const
    {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }
    VIDECL inline void construct(pointer p, const_reference t)
    {
        new(p) value_type(t);
    }
    VIDECL inline void destroy(pointer p)
    {
        p->~value_type();
    }
    inline bool operator==(StdAllocator const& a) { return this == &a; }
    inline bool operator!=(StdAllocator const& a) { return !operator==(a); }
};

VISRCEND

#endif //VICTORIAM_MSTANDARDALLOCATOR_HPP
