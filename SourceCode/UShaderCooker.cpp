//
// Created by Вячеслав Кривенко on 14.10.2022.
//

#include <fstream>
#include <filesystem>
#include <vector>

#include <Victoriam/Utils/UShaderCooker.hpp>
#include <Victoriam/Utils/UCryptogen.hpp>

VISRCBEG

namespace {

	bool CheckKeyword(
			std::basic_string<char, std::char_traits<char>, StdAllocator<char>>::iterator &it, const char *keyword) {
		char len = (char) (strlen)(keyword);
		for (char i = 0; i < len; i++)
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
		const char keyword[4][9] =
				{
						"group",
						"vertex",
						"fragment",
						"endgroup"
				};
		auto it = source.begin();
		while (it != source.end())
		{
			if ((*it) == 64)
				if (CheckKeyword(it, keyword[0]))
				{
					if (CheckKeyword(it, keyword[1]))
					{
						while ((*++it) != 64) tmp.push_back(*it);
						if (CheckKeyword(it, keyword[3]))
						{
							SSPIRVShader s(
									SSPIRVShader::Vertex,
									tmp,
									shader.Name
							);
							tmp = {};
							result.push_back(s);
							continue;
						}
					}
					if (CheckKeyword(it, keyword[2]))
					{
						while ((*++it) != 64) tmp.push_back(*it);
						if (CheckKeyword(it, keyword[3]))
						{
							SSPIRVShader s(
									SSPIRVShader::Fragment,
									tmp,
									shader.Name
							);
							tmp = {};
							result.push_back(s);
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
	return std::all_of(EXT.begin(), EXT.end(),[=](const char* ext) -> Bool
	{
		if (!std::filesystem::exists(COOKEDDIR + name + ext))
			return false;
		return true;
	});
}

bool CShaderCooker::IsShaderChanged(const SEngineShader& shader, const String& name)
{
	std::fstream file(SHADERDIR + name + ".sum", std::ios::in);
	String sum; sum.resize(32);
	if (file.is_open())
	{
		file.read(CCast<char*>(sum.data()), 32);
		file.close();
		bool result = shader.Checksum != sum;
		if (result)
		{
			file.open(SHADERDIR + name + ".sum", std::ios::out);
			file.write(shader.Checksum.c_str(), 32);
			file.close();
		}
		return result;
	}
	else
	{
		file.open(SHADERDIR + name + ".sum", std::ios::out);
		file.write(shader.Checksum.c_str(), 32);
		file.close();
		return true;
	}
}

SEngineShader CShaderCooker::ReadShader(const String &name)
{
	String source = {};
	String checksum; checksum.resize(32);
	{
		std::ifstream file(SHADERDIR + name + ".shader");
		if (file.is_open())
		{
			file.seekg(0, std::ios::end);
			size_t size = file.tellg();
			file.seekg(0, std::ios::beg);
			source.resize(size);
			file.read(CCast<char*>(source.data()), CCast<UInt32>(source.size()));
			file.close();

			CCryptogen cryptogen(source, ECHashingAlgorithm::MD5);
			checksum = cryptogen.ProcessFromString();
		}
		else
		{
			String exerror = "Cant open shader '" + name + "'! Maybe it's doesn't exists!";
			String addictionalinfo = "\nINFO:\n\t";
			addictionalinfo += "CWD - ";
			addictionalinfo += std::filesystem::current_path().string();

			exerror += addictionalinfo;
			throw std::runtime_error(exerror.c_str());
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
		std::ofstream f(tempfile, std::ios::binary);
		if (f.is_open())
		{
			f.write(shader.Source.c_str(), CCast<UInt32>(shader.Source.size()));
			f.close();
		}
		// cook shader using glslc tool
		String command = COMPILER;
		command += tempfile;
		command += " -o ";
		command += cookedfile;
		system(command.c_str());
	}
	std::filesystem::remove_all(TEMPDIR);
	info += "}\n\n";
	return info;
}

BinaryData CShaderCooker::LoadCookedShaderFromName(const String &name,
                                                   const SSPIRVShader::EShaderType &type)
{
	BinaryData data = {};
	std::ifstream f(COOKEDDIR + name + EXT[(uint32_t)(type)]);
	if (f.is_open())
	{
		f.seekg(0, std::ios::end);
		data.resize(f.tellg());
		f.seekg(0, std::ios::beg);
		f.read(CCast<char*>(data.data()), CCast<UInt32>(data.size()));
		f.close();
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
        printf("%s\n", INFO.c_str());
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
		printf("%s\n", INFO.c_str());
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
