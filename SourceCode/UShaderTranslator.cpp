//
// Created by Вячеслав Кривенко on 06.12.2022.
//

#include <Victoriam/Utils/UShaderTranslator.hpp>

VISRCBEG

static Bool IsBuiltinType(const String& token) {
	if (token == "Vector2") return true;
	else if (token == "Vector3") return true;
	else if (token == "Vector4") return true;
	else if (token == "Matrix3") return true;
	else if (token == "Matrix4") return true;
	else if (token == "Float32") return true;
	else if (token == "Int32") return true;
	else if (token == "VERTEX_POSITION") return true;
	else if (token == "VERTEXPOSITION") return true;
	else if (token == "V_POSITION") return true;
	else if (token == "VPOSITION") return true;
	else if (token == "VERTEX_ID") return true;
	else if (token == "VERTEXID") return true;
	else if (token == "VID") return true;
	else if (token == "V_ID") return true;
	else if (token == "FNormalize") return true;
	else if (token == "FDot") return true;
	else if (token == "FMin") return true;
	else if (token == "FMax") return true;
	else if (token == "FCross") return true;
	else if (token == "FSqrt") return true;
	else return false;
}

static String FTranslate(const String& token) {
	if (token == "Vector2") return "vec2";
	else if (token == "Vector3") return "vec3";
	else if (token == "Vector4") return "vec4";
	else if (token == "Matrix3") return "mat3";
	else if (token == "Matrix4") return "mat4";
	else if (token == "Float32") return "float";
	else if (token == "Int32") return "int";
	else if (token == "VERTEX_POSITION") return "gl_Position";
	else if (token == "VERTEXPOSITION") return "gl_Position";
	else if (token == "V_POSITION") return "gl_Position";
	else if (token == "VPOSITION") return "gl_Position";
	else if (token == "VERTEX_ID") return "gl_VertexIndex";
	else if (token == "VERTEXID") return "gl_VertexIndex";
	else if (token == "VID") return "gl_VertexIndex";
	else if (token == "V_ID") return "gl_VertexIndex";
	else if (token == "FNormalize") return "normalize";
	else if (token == "FDot") return "dot";
	else if (token == "FMin") return "min";
	else if (token == "FMax") return "max";
	else if (token == "FCross") return "cross";
	else if (token == "FSqrt") return "sqrt";
	else if (token == "1") return "450";
	else return token;
}

struct VIDECL SToken {
	enum EType : FlagDef {
		EndOfFile,
		White, // ' '
		Number, // 0-9
		Identifier,
		Operator, // + - * / | = == += -= *= /= |= ++ --
		OpenParen, // (
		CloseParen, // )
		OpenSquare, // [
		CloseSquare, // ]
		OpenCurly, // {
		CloseCurly, // }
		Semicolon, // ;
		Dot, // '.'
		Comma, // ','
	};
	SFlags Type;
	String Value;
};

VIDECL typedef CSet<SToken> TokenList;

static TokenList FTokenizeString(const String& string) {
	TokenList list = {};
	for (auto i = 0; i < string.size(); i++) {
		while (string[i] == ' ' || string[i] == '\t') i++;
		if (string[i] == '/' && string[i + 1] == '/')
			while (string[i] != '\n') i++;
		if (isdigit(string[i])) {
			const auto start = i;
			while (isdigit(string[i]) || string[i] == '.') i++;
			list.PushBack({SToken::Number, string.substr(start, i - start)});
		}
		if (isalpha(string[i]) || string[i] == '_') {
			const auto start = i;
			while (isalpha(string[i]) || string[i] == '_' || isdigit(string[i])) i++;
			list.PushBack({SToken::Identifier, string.substr(start, i - start)});
		}
		if (string[i] == '+' ||
		    string[i] == '-' ||
		    string[i] == '*' ||
		    string[i] == '/' ||
		    string[i] == '>' ||
		    string[i] == '<' ||
		    string[i] == '|' ||
		    string[i] == '=' ||
		    ((string[i] == '+') && (string[i + 1] == '=')) ||
		    ((string[i] == '-') && (string[i + 1] == '=')) ||
		    ((string[i] == '*') && (string[i + 1] == '=')) ||
		    ((string[i] == '/') && (string[i + 1] == '=')) ||
		    ((string[i] == '|') && (string[i + 1] == '=')) ||
		    ((string[i] == '=') && (string[i + 1] == '=')) ||
		    ((string[i] == '>') && (string[i + 1] == '=')) ||
		    ((string[i] == '<') && (string[i + 1] == '=')) ||
		    ((string[i] == '+') && (string[i + 1] == '+')) ||
		    ((string[i] == '-') && (string[i + 1] == '-'))
				) {
			const auto start = i;
			auto end = i + 1;
			if ((string[i + 1] == '=') || (string[i + 1] == '+') || (string[i + 1] == '-')) {
				end++;
				i++;
			}
			list.PushBack({SToken::Operator, string.substr(start, end - start)});
		}
		if (string[i] == '(') {
			list.PushBack({SToken::OpenParen, "("});
		}
		if (string[i] == ')') {
			list.PushBack({SToken::CloseParen, ")"});
		}
		if (string[i] == '[') {
			list.PushBack({SToken::OpenSquare, "["});
		}
		if (string[i] == ']') {
			list.PushBack({SToken::CloseSquare, "]"});
		}
		if (string[i] == '{') {
			list.PushBack({SToken::OpenCurly, "{"});
		}
		if (string[i] == '}') {
			list.PushBack({SToken::CloseCurly, "}"});
		}
		if (string[i] == ';') {
			list.PushBack({SToken::Semicolon, ";"});
		}
		if (string[i] == ',') {
			list.PushBack({SToken::Comma, ","});
		}
		if (string[i] == '.') {
			list.PushBack({SToken::Dot, "."});
		}
	}
	list.PushBack({SToken::EndOfFile, ""});
	return list;
}

/**
EndOfFile
White
Number
Identifier
Operator
OpenParen
CloseParen
OpenSquare
CloseSquare
OpenCurly
CloseCurly
Semicolon
Dot
Comma
*/

static StringView FToString(const SToken::EType& type) {
	switch (type) {
		case SToken::EndOfFile:
			return "EndOfFile";
		case SToken::White:
			return "White";
		case SToken::Number:
			return "Number";
		case SToken::Identifier:
			return "Identifier";
		case SToken::Operator:
			return "Operator";
		case SToken::OpenParen:
			return "OpenParen";
		case SToken::CloseParen:
			return "CloseParen";
		case SToken::OpenSquare:
			return "OpenSquare";
		case SToken::CloseSquare:
			return "CloseSquare";
		case SToken::OpenCurly:
			return "OpenCurly";
		case SToken::CloseCurly:
			return "CloseCurly";
		case SToken::Semicolon:
			return "Semicolon";
		case SToken::Dot:
			return "Dot";
		case SToken::Comma:
			return "Comma";
	}
}

static SToken FExpect(const SToken& token, const SToken::EType& type) {
	if (token.Type == type) return token;
	VIDECL auto typeName = FToString(type);
	ViAbort("Failed to parse shader: unexpected token '" << token.Value << "', was expected of type " << typeName);
}

//
static String GetAttributeList(const TokenList& source, const Signal& t) {
	String result = {};
	enum { undefined, input_vertex, input_pixel, output_vertex, output_pixel, global_constant, global_struct, global_uniform_struct, global_push, vertex_static, pixel_static };
	int state = undefined;
	int location = 0;
	int set = 0;

	for (auto i = 0; i < source.Size(); i++) {
		if (source[i].Value == "VERSION" || source[i].Value == "version") {
			i++;
			auto version = FTranslate(FExpect(source[i], SToken::Number).Value);
			result += "#version ";
			result += version;
			result += "\n";
		}
		else if (source[i].Value == "INPUT" || source[i].Value == "input") {
			i++;
			auto target = FExpect(source[i], SToken::Identifier).Value;
			if (t == TargetVertex)
				if (target == "VERTEX" || target == "vertex")
					state = input_vertex;
			if (t == TargetPixel)
				if (target == "PIXEL" || target == "pixel")
					state = input_pixel;
			i++;
		}
		else if (source[i].Value == "OUTPUT" || source[i].Value == "output") {
			i++;
			auto target = FExpect(source[i], SToken::Identifier).Value;
			if (t == TargetVertex)
				if (target == "VERTEX" || target == "vertex")
					state = output_vertex;
			if (t == TargetPixel)
				if (target == "PIXEL" || target == "pixel")
					state = output_pixel;
			i++;
		}
		else if (source[i].Value == "GLOBAL" || source[i].Value == "global") {
			if (source[i + 1].Value == "STRUCT" || source[i + 1].Value == "struct") {
				state = global_struct;
			}
			else if (source[i + 1].Value == "CONSTANT" || source[i + 1].Value == "constant") {
				state = global_constant;
			}
			else if (source[i + 1].Value == "UNIFORM" || source[i + 1].Value == "uniform") {
				if (source[i + 2].Value == "STRUCT" || source[i + 2].Value == "struct") {
					state = global_uniform_struct;
				}
			}
			else if (source[i + 1].Value == "PUSH" || source[i + 1].Value == "push") {
				if (source[i + 2].Value == "STRUCT" || source[i + 2].Value == "struct") {
					state = global_push;
				}
			}
		}
		else if (source[i].Value == "VERTEX" && source[i - 1].Value != "PROGRAM") {
			if (t == TargetVertex)
				state = vertex_static;
		}
		else if (source[i].Value == "PIXEL" && source[i - 1].Value != "PROGRAM") {
			if (t == TargetPixel)
				state = pixel_static;
		}
		else if (state == vertex_static || state == pixel_static) {
			String type = FTranslate(FExpect(source[i++], SToken::Identifier).Value);
			auto start = i; // +1 ?
			while (source[i].Type != SToken::OpenCurly || source[i].Type != SToken::White) i++;
			String name = {};
			for (auto j = start; j < i; j++) name += source[j].Value;
			String value = {};
			i++;
			start = i;
			while (source[i].Type != SToken::CloseCurly) i++;
			for (auto j = start; j < i; j++) value += FTranslate(source[j].Value);
			result += " const ";
			result += type + " ";
			result += name + " = ";
			result += value + "; ";
			state = undefined;
		}
		else if (state == input_vertex || state == output_vertex) {
			location = 0;
			for (auto j = i; j < source.Size() && source[i].Type != SToken::CloseCurly; j++) {
				auto type = FTranslate(FExpect(source[i], SToken::Identifier).Value);
				i++;
				auto name = FExpect(source[i], SToken::Identifier).Value;
				i++;
				FExpect(source[i], SToken::Semicolon);
				i++;
				result += "layout(location=" + std::to_string(location++) + ((state == input_vertex) ? ") in " : (state == output_vertex) ? ") out " : ") ");
				result += type + " ";
				result += name + "; ";
			}
			state = undefined;
		}
		else if (state == input_pixel || state == output_pixel) {
			location = 0;
			for (auto j = i; j < source.Size() && source[i].Type != SToken::CloseCurly; i++) {
				auto type = FTranslate(FExpect(source[i], SToken::Identifier).Value);
				i++;
				auto name = FExpect(source[i], SToken::Identifier).Value;
				i++;
				FExpect(source[i], SToken::Semicolon);
				result += "layout(location=" + std::to_string(location++) + ((state == input_pixel) ? ") in " : (state == output_pixel) ? ") out " : ") ");
				result += type + " ";
				result += name + "; ";
			}
			state = undefined;
		}
		else if (state == global_constant) {
			FExpect(source[i++], SToken::Identifier); // CONSTANT
			auto name = FExpect(source[i++], SToken::Identifier).Value;
			FExpect(source[i++], SToken::Operator); // =
			auto value = source[i++].Value;
			result += "\n#define ";
			result += name + " ";
			result += value + "\n ";
			state = undefined;
		}
		else if (state == global_struct || state == global_uniform_struct || state == global_push) {
			FExpect(source[i], SToken::Identifier); // STRUCT or UNIFORM or PUSH
			i++;
			if (state == global_uniform_struct || state == global_push) {
				FExpect(source[i], SToken::Identifier); // STRUCT
				i++;
			}
			auto struct_name = FExpect(source[i++], SToken::Identifier).Value;
			i++;

			if (state == global_struct)
				result += "struct ";
			else if (state == global_uniform_struct) {
				result += "layout (set = ";
				result += std::to_string(set++);
				result += ", binding = 0) uniform UNIFORM_";
			}
			else if (state == global_push) {
				result += "layout (push_constant) uniform PUSH_";
			}
			result += struct_name + " { ";

			for (auto j = i; j < source.Size() && source[i].Type != SToken::CloseCurly; j++) {
				String type = FTranslate(FExpect(source[i], SToken::Identifier).Value);
				i++;
				auto name = FExpect(source[i], SToken::Identifier).Value;
				i++;
				if (source[i].Type == SToken::OpenSquare) {
					name += source[i++].Value;
					name += source[i++].Value;
					name += source[i++].Value;
				}
				i++;
				result += type + " ";
				result += name + "; ";
			}
			result += "} ";
			if (state == global_uniform_struct || state == global_push)
				result += struct_name + ";  ";
			else {
				result += " ;  ";
			}
			state = undefined;
		}
	}

	return result;
}

static String ParseProgramFunction(const TokenList& source, const Signal& target) {
	String result = "\nvoid main() { \n";
	enum { undefined, read };
	int state = undefined;
	for (auto i = 0; i < source.Size(); i++) {
		if (source[i].Value == "PROGRAM" || source[i].Value == "program") {
			if (target == TargetVertex) {
				if (source[i + 1].Value == "VERTEX" || source[i + 1].Value == "vertex") {
					state = read;
				}
			}
			else if (target == TargetPixel) {
				if (source[i + 1].Value == "PIXEL" || source[i + 1].Value == "pixel") {
					state = read;
				}
			}
		}
		else if (state == read) {
			FExpect(source[i++], SToken::Identifier); // VERTEX
			FExpect(source[i++], SToken::OpenCurly); // {
			String tmp;
			while (source[i].Value != "ENDPROGRAM") {

				if (IsBuiltinType(source[i].Value))
					tmp = FTranslate(source[i].Value);
				else
					tmp = source[i].Value;

				if (source[i + 1].Type == SToken::Dot || source[i].Type == SToken::Dot ||
				    source[i + 1].Type == SToken::OpenSquare || source[i].Type == SToken::OpenSquare ||
				    source[i + 1].Type == SToken::CloseSquare || source[i].Type == SToken::CloseSquare ||
				    source[i + 1].Type == SToken::Operator
						)
					result += tmp;
				else
					result += tmp + " ";
				i++;
			}
			return result;
		}
	}
	return {};
}

static String TranslateVertexShader(const String& source) {
	TokenList list = FTokenizeString(source);
	String head = GetAttributeList(list, TargetVertex);
	String body = ParseProgramFunction(list, TargetVertex);
	return head + body;
}

static String TranslatePixelShader(const String& source) {
	TokenList list = FTokenizeString(source);
	String head = GetAttributeList(list, TargetPixel);
	String body = ParseProgramFunction(list, TargetPixel);
	return head + body;
}

String CShaderTranslator::operator()(const String& source, const Signal &target) {
	switch (target) {
		case TargetVertex: return TranslateVertexShader(source);
		case TargetPixel: return TranslatePixelShader(source);
		default: return "";
	}
}



VISRCEND
