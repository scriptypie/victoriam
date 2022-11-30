//
// Created by Вячеслав Кривенко on 28.11.2022.
//

#ifndef VICTORIAM_UPATHTRACKER_HPP
#define VICTORIAM_UPATHTRACKER_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

/*
 * What is the PathTracker?
 * PathTracker is a tool for simple filepath utilizing.
 */
class VIDECL CPathTracker {
	CHashTable<StringView, String> ActualToVirtual = {};
	CHashTable<StringView, String> VirtualToActual = {};
	StringView Temp = {};
public:
	VIDECL static CPathTracker& Instance();
	VIDECL static CPathTracker& Mount(const StringView& actualPath);
	VIDECL        CPathTracker& To(const StringView& virtualPath);

	VIDECL static String Get(const StringView& virt);
	VIDECL static CList<StringView> VirtualList();
	VIDECL static CList<StringView> ActualList();
	VIDECL static Bool Exists(const StringView& virt);

};

using Path = CPathTracker;

VISRCEND

#endif //VICTORIAM_UPATHTRACKER_HPP
