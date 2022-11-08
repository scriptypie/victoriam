//
// Created by Вячеслав Кривенко on 30.10.2022.
//

#ifndef VICTORIAM_UGEOMETRYBUILDER_HPP
#define VICTORIAM_UGEOMETRYBUILDER_HPP

#include <Victoriam/Core/CBase.hpp>
#include <Victoriam/Graphics/Structs/GGeometryDataCreateInfo.hpp>
#include <Victoriam/Graphics/GGeometryData.hpp>
#include <Victoriam/Graphics/GRenderer.hpp>
#include <Victoriam/Utils/UJobWorker.hpp>

VISRCBEG

class VIDECL CGeometryBuilder
{
	//CJobWorker worker = {};
public:
	static CGeometryBuilder& Get();

	VIDECL VIREQOUT SGeometryDataCreateInfo LoadDefaultFromFile(const String& filename);

private:
	VIDECL void InternalLoadModelFromFile(const String& filename, SGeometryDataCreateInfo& outinfo);
};

VISRCEND

#endif //VICTORIAM_UGEOMETRYBUILDER_HPP
