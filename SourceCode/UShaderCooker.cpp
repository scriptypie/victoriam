//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <Victoriam/Utils/UShaderCooker.hpp>
#include <Victoriam/Utils/UCryptogen.hpp>
#include <Victoriam/Utils/UShaderTranslator.hpp>
#include "Victoriam/IO/IOFile.hpp"

VISRCBEG

namespace {

	const char g_hashmark[10] = { ".hashsum." };

	CSet<SSPIRVShader> SplitShader(const SEngineShader &shader) {
		CSet<SSPIRVShader> result;
		CShaderTranslator translator;
		SSPIRVShader vs{SSPIRVShader::Vertex, shader.Name}, fs{SSPIRVShader::Pixel, shader.Name};

		vs.Source = translator(shader.Source, TargetVertex);
		fs.Source = translator(shader.Source, TargetPixel);

		result.PushBack(vs);
		result.PushBack(fs);

		return result;
	}

}

bool CShaderCooker::IsCookedExists(const String &name)
{
	return std::all_of(EXT.begin(), EXT.end(),[=](CString ext) -> Bool {
		return std::filesystem::exists(COOKEDDIR + name + ext);
	});
}

bool CShaderCooker::IsShaderChanged(const SEngineShader& shader, const String& name)
{
	CFile file(SHADERDIR + String(g_hashmark) + name, ECOpenMode::Read);
	String sum(32, 0);
	if (file.Valid()) {
		VIGNORE file.Read(sum);
		file.Close();
		auto result = shader.Checksum != sum;
		if (result) {
			file.Open(SHADERDIR + String(g_hashmark) + name, ECOpenMode::Write);
			VIGNORE file.Write(shader.Checksum);
			file.Close();
		}
		return result;
	}
	else {
		file.Open(SHADERDIR + String(g_hashmark) + name, ECOpenMode::Write);
		VIGNORE file.Write(shader.Checksum);
		file.Close();
		return true;
	}
}

SEngineShader CShaderCooker::ReadShader(const String &name)
{
	String source = {};
	String checksum; checksum.resize(32);
	{
		CFile file(SHADERDIR + name + ".shader", ECOpenMode::Read);
		if (file.Valid())
		{
			VIGNORE file.Read(source);
			file.Close();

			CCryptogen cryptogen(source, ECHashingAlgorithm::MD5);
			checksum = cryptogen.ProcessFromString();
		}
		else
		{
			String exerror = "Cant open shader '" + name + "'! Maybe it's doesn't exists!";
			ViAbort(exerror);
		}
	}
	INFO = "Shader checksum: " + checksum;
	return { name, source, checksum };
}

String CShaderCooker::CookShader(const CSet<SSPIRVShader> &sshader)
{
	String info = "\nCooked shader: {\n", tempfile, cookedfile;

	// create tmp folder if needed
	if (!std::filesystem::is_directory(TEMPDIR))
		std::filesystem::create_directory(TEMPDIR);

	// create cooked folder if needed
	if (!std::filesystem::is_directory(COOKEDDIR))
		std::filesystem::create_directory(COOKEDDIR);

	for (const auto& shader : sshader)
	{
		// create meta info string
		String tmp = "\t{\n\t\tName: \"" + shader.Name + "\"";
		tmp += ",\n\t\tType: " + SSPIRVShader::toString(shader.Type);
		tempfile = TEMPDIR + shader.Name + "." + SSPIRVShader::toString(shader.Type);
		cookedfile = COOKEDDIR + shader.Name + "." + SSPIRVShader::toString(shader.Type) + ".spv";
		tmp += ",\n\t\tCooked: \"" + cookedfile + "\"";
		tmp += ",\n\t},\n";
		info += tmp;
		// create tmp file of out shader
		CFile f(tempfile, ECOpenMode::Write, ECFileFormat::Bin);
		if (f.Valid())
		{
			VIGNORE f.Write(shader.Source);
			f.Close();
		}
		// cook shader using glslc tool
		String command;
		((((command += COMPILER) += tempfile) +=" -o ") += cookedfile); // evil thing..
		system(command.c_str());
	}
	std::filesystem::remove_all(TEMPDIR);
	info += "}\n\n";
	return info;
}

CBinaryData CShaderCooker::LoadCookedShaderFromName(const String &name, const SSPIRVShader::EShaderType &type)
{
	CBinaryData data = {};
	CFile f(COOKEDDIR + name + EXT[(uint32_t)(type)], ECOpenMode::Read);
	if (f.Valid()) {
		VIGNORE f.Read(data);
		f.Close();
	}
	return data;
}

CBinaryData CShaderCooker::LoadVertexShader(const String &name)
{
	SEngineShader shader = ReadShader(name);
	if (IsShaderChanged(shader, name) || !IsCookedExists(name))
	{
		CSet<SSPIRVShader> shaders = SplitShader(shader);
		INFO += CookShader(shaders);
		ViLog(INFO);
	}
	return LoadCookedShaderFromName(name, SSPIRVShader::Vertex);
}

CBinaryData CShaderCooker::LoadFragmentShader(const String &name)
{
	SEngineShader shader = ReadShader(name);
	if (IsShaderChanged(shader, name) || !IsCookedExists(name))
	{
		CSet<SSPIRVShader> shaders = SplitShader(shader);
		INFO += CookShader(shaders);
		ViLog(INFO);
	}
	return LoadCookedShaderFromName(name, SSPIRVShader::Pixel);
}

String SSPIRVShader::toString(const SSPIRVShader::EShaderType &type)
{
	switch (type)
	{
		case Vertex: return "vert";
		case Pixel: return "frag";
		default: return "Unknown";
	}
}

VISRCEND
