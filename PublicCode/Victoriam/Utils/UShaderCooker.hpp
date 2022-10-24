//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_USHADERCOOKER_HPP
#define VICTORIAM_USHADERCOOKER_HPP

#include <Victoriam/Core/CBase.hpp>
#include <utility>

VISRCBEG

struct SEngineShader
{
	String Name;
	String Source;
	String Checksum;
};
struct SSPIRVShader
{
	enum EShaderType
	{
		Vertex, Fragment,
		NumTypes
	} Type;
	String Source;
	String Name;

	static String toString(const EShaderType& type) ;

	SSPIRVShader(const EShaderType& type, String src, String name)
			: Type(type), Source(std::move(src)), Name(std::move(name))
	{}
};

class VIDECL CShaderCooker
{
	const List<CString> EXT = { ".vert.spv", ".frag.spv" };
	String INFO;
	const String COMPILER = "/usr/local/bin/glslc ";
	const String SHADERDIR = "./../Resources/Shaders/";
	const String COOKEDDIR = SHADERDIR + "Cooked/";
	const String TEMPDIR = SHADERDIR + ".TMP/";
	bool IsCookedExists(const String& name);
	bool IsShaderChanged(const SEngineShader& shader, const String& name);
	SEngineShader ReadShader(const String& name);
	String CookShader(const List<SSPIRVShader>& sshader);
	BinaryData LoadCookedShaderFromName(const String& name, const SSPIRVShader::EShaderType& type);
public:
	VIDECL BinaryData LoadVertexShader(const String& name);
	VIDECL BinaryData LoadFragmentShader(const String& name);
	VIDECL VIREQOUT inline String GetCookedInfo() const { return INFO; }

};

VISRCEND

#endif //VICTORIAM_USHADERCOOKER_HPP
