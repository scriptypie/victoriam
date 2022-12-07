//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_USHADERCOOKER_HPP
#define VICTORIAM_USHADERCOOKER_HPP

#include <Victoriam/Core/CBase.hpp>

VISRCBEG

struct VIDECL SEngineShader
{
	String Name;
	String Source;
	String Checksum;
};

struct VIDECL SSPIRVShader
{
	enum VIDECL EShaderType
	{
		Undefined = -1,
		Vertex,
		Pixel
	} Type = Undefined;
	String Name = {};
	String Source = {};

	VIDECL VIREQOUT static String toString(const EShaderType& type);
};

class VIDECL CShaderCooker
{
	const CSet<CString> EXT = {".vert.spv", ".frag.spv" };
	String INFO;
	const String COMPILER = "glslc ";
	const String SHADERDIR = "./../Resources/Shaders/";
	const String COOKEDDIR = SHADERDIR + "Cooked/";
	const String TEMPDIR = SHADERDIR + ".TMP/";
public:
	VIDECL VIREQOUT CBinaryData LoadVertexShader(const String& name);
	VIDECL VIREQOUT CBinaryData LoadFragmentShader(const String& name);
	VIDECL VIREQOUT inline String GetCookedInfo() const { return INFO; }

private:
	VIDECL VIREQOUT bool IsCookedExists(const String& name);
	VIDECL VIREQOUT bool IsShaderChanged(const SEngineShader& shader, const String& name);
	VIDECL VIREQOUT SEngineShader ReadShader(const String& name);
	VIDECL VIREQOUT String CookShader(const CSet<SSPIRVShader>& sshader);
	VIDECL VIREQOUT CBinaryData LoadCookedShaderFromName(const String& name, const SSPIRVShader::EShaderType& type);
};

VISRCEND

#endif //VICTORIAM_USHADERCOOKER_HPP
