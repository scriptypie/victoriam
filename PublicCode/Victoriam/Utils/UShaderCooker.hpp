//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_USHADERCOOKER_HPP
#define VICTORIAM_USHADERCOOKER_HPP

#include <Victoriam/Core/CBase.hpp>
#include <utility>

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
		Vertex,
		Fragment
	} Type;
	String Source;
	String Name;

	VIDECL VIREQOUT static String toString(const EShaderType& type) ;

	VIDECL inline SSPIRVShader(const EShaderType& type, String src, String name)
			: Type(type), Source(std::move(src)), Name(std::move(name))
	{}
};

class VIDECL CShaderCooker
{
	const List<CString> EXT = {".vert.spv", ".frag.spv" };
	String INFO;
	const String COMPILER = "/usr/local/bin/glslc ";
	const String SHADERDIR = "./../Resources/Shaders/";
	const String COOKEDDIR = SHADERDIR + "Cooked/";
	const String TEMPDIR = SHADERDIR + ".TMP/";
public:
	VIDECL VIREQOUT BinaryData LoadVertexShader(const String& name);
	VIDECL VIREQOUT BinaryData LoadFragmentShader(const String& name);
	VIDECL VIREQOUT inline String GetCookedInfo() const { return INFO; }

private:
	VIDECL VIREQOUT bool IsCookedExists(const String& name);
	VIDECL VIREQOUT bool IsShaderChanged(const SEngineShader& shader, const String& name);
	VIDECL VIREQOUT SEngineShader ReadShader(const String& name);
	VIDECL VIREQOUT String CookShader(const List<SSPIRVShader>& sshader);
	VIDECL VIREQOUT BinaryData LoadCookedShaderFromName(const String& name, const SSPIRVShader::EShaderType& type);
};

VISRCEND

#endif //VICTORIAM_USHADERCOOKER_HPP
