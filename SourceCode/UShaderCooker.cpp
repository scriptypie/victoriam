//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <filesystem>
#include <vector>
#include <iostream>

#include <Victoriam/Utils/UShaderCooker.hpp>
#include <Victoriam/Utils/UCryptogen.hpp>
#include <Victoriam/Utils/UFile.hpp>

VISRCBEG

namespace {

	const char g_Keywords[4][9] =
	{
			"group",
			"vertex",
			"fragment",
			"endgroup"
	};

	Bool CheckKeyword(String::iterator &it, CString keyword) {
		Int8 len = (Int8) (strlen)(keyword);
		for (Int8 i = 0; i < len; i++)
			if ((*(it + 1)) == keyword[i]) {
				it++;
				continue;
			} else
				return false;
		it++;
		return true;
	}

	List<SSPIRVShader> SplitShader(const SEngineShader &shader)
	{
		List<SSPIRVShader> result;
		String tmp, source = shader.Source;
		auto it = source.begin();
		while (it != source.end())
		{
			if ((*it) == 64)
				if (CheckKeyword(it, g_Keywords[0]))
				{
					if (CheckKeyword(it, g_Keywords[1]))
					{
						while ((*(++it)) != 64) tmp.push_back(*it);
						if (CheckKeyword(it, g_Keywords[3]))
						{
							result.push_back({ SSPIRVShader::Vertex, tmp, shader.Name });
							tmp = {};
							continue;
						}
					}
					if (CheckKeyword(it, g_Keywords[2]))
					{
						while ((*(++it)) != 64) tmp.push_back(*it);
						if (CheckKeyword(it, g_Keywords[3]))
						{
							result.push_back({ SSPIRVShader::Fragment, tmp, shader.Name });
							tmp = {};
							continue;
						}
					}
				}
			it++;
		}
		return result;
	}

}

bool CShaderCooker::IsCookedExists(const String &name)
{
	return std::all_of(EXT.begin(), EXT.end(),[=](CString ext) -> Bool
	{
		if (!std::filesystem::exists(COOKEDDIR + name + ext))
			return false;
		return true;
	});
}

bool CShaderCooker::IsShaderChanged(const SEngineShader& shader, const String& name)
{
	CFile file(SHADERDIR + name + ".sum", ECOpenMode::Read);
	String sum; sum.resize(32);
	if (file.Valid())
	{
		VIGNORE file.Read(sum);
		file.Close();
		bool result = shader.Checksum != sum;
		if (result)
		{
			file.Open(SHADERDIR + name + ".sum", ECOpenMode::Write);
			VIGNORE file.Write(shader.Checksum);
			file.Close();
		}
		return result;
	}
	else
	{
		file.Open(SHADERDIR + name + ".sum", ECOpenMode::Write);
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
			ViAbort("%s", exerror.c_str());
		}
	}
	INFO = "Shader checksum: " + checksum;
	return { name, source, checksum };
}

String CShaderCooker::CookShader(const List<SSPIRVShader> &sshader)
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

BinaryData CShaderCooker::LoadCookedShaderFromName(const String &name, const SSPIRVShader::EShaderType &type)
{
	BinaryData data = {};
	CFile f(COOKEDDIR + name + EXT[(uint32_t)(type)], ECOpenMode::Read);
	if (f.Valid())
	{
		VIGNORE f.Read(data);
		f.Close();
	}
	return data;
}

BinaryData CShaderCooker::LoadVertexShader(const String &name)
{
	SEngineShader shader = ReadShader(name);
	if (IsShaderChanged(shader, name) || !IsCookedExists(name))
	{
		List<SSPIRVShader> shaders = SplitShader(shader);
		INFO += CookShader(shaders);
        std::cout << INFO << std::endl;
	}
	return LoadCookedShaderFromName(name, SSPIRVShader::Vertex);
}

BinaryData CShaderCooker::LoadFragmentShader(const String &name)
{
	SEngineShader shader = ReadShader(name);
	if (IsShaderChanged(shader, name) || !IsCookedExists(name))
	{
		List<SSPIRVShader> shaders = SplitShader(shader);
		INFO += CookShader(shaders);
		std::cout << INFO << std::endl;
	}
	return LoadCookedShaderFromName(name, SSPIRVShader::Fragment);
}

String SSPIRVShader::toString(const SSPIRVShader::EShaderType &type)
{
	switch (type)
	{
		case Vertex: return "vert";
		case Fragment: return "frag";
		default: return "Unknown";
	}
}

VISRCEND
