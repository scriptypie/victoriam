//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#ifndef VICTORIAM_SHADERCOOKER_HPP
#define VICTORIAM_SHADERCOOKER_HPP

#include <Victoriam/Core/Base.hpp>
#include <utility>

VISRCBEG

struct EngineShader
{
	String Name;
	String Source;
};
struct SPIRVShader
{
	enum ShaderType
	{
		Vertex, Fragment,
		NumTypes
	} Type;
	String Source;
	String Name;

	static String toString(const ShaderType& type) ;

	SPIRVShader(const ShaderType& type, String  src, String  name)
			: Type(type), Source(std::move(src)), Name(std::move(name))
	{}
};

class VIDECL cShaderCooker
{
	const List<const char*> EXT = { ".vert.spv", ".frag.spv" };
	String INFO;
	const String COMPILER = "glslc ";
	const String SHADERDIR = "./../Resources/Shaders/";
	const String COOKEDDIR = SHADERDIR + "Cooked/";
	const String TEMPDIR = SHADERDIR + ".TMP/";
	bool IsCookedExists(const String& name);
	EngineShader ReadShader(const String& name);
	String CookShader(const List<SPIRVShader>& sshader);
	String LoadCookedShaderFromName(const String& name, const SPIRVShader::ShaderType& type);
public:
	VIDECL String LoadVertexShader(const String& name);
	VIDECL String LoadFragmentShader(const String& name);
	VIDECL [[nodiscard]] inline String GetCookedInfo() const { return INFO; }

};

VISRCEND

#endif //VICTORIAM_SHADERCOOKER_HPP
