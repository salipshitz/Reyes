#include <pch>
#include "OpenGLShader.h"

#include <fstream>

#include <Reyes/Core/Log.h>

namespace Reyes::RenderAPI {
	OpenGLShader::OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc) {
		std::unordered_map<unsigned int, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	OpenGLShader::OpenGLShader(const std::string &filePath) {
		std::ifstream in(filePath, std::ios::in, std::ios::binary);
		std::string source;
		if (in) {
			in.seekg(0, std::ios::end);
			source.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&source[0], source.size());
			in.close();
		} else {
			REY_CORE_ERROR("Failed to open shader asset '{}'", filePath);
		}
		Compile(Preprocess(source));
	}

	std::unordered_map<unsigned int, std::string> OpenGLShader::Preprocess(const std::string &source) {
		std::unordered_map<unsigned int, std::string> shaderSources;
		const static char *typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			REY_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			int glType = 0;
			if (type == "vertex")
				glType = GL_VERTEX_SHADER;
			else if (type == "fragment" || type == "pixel")
				glType = GL_FRAGMENT_SHADER;
			REY_CORE_ASSERT(glType, "Invalid shader type specified");
			size_t nlp = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nlp);
			shaderSources[glType] = source.substr(nlp, pos - (nlp == std::string::npos ? source.size() - 1 : nlp));
		}
		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<unsigned int, std::string> &shaderSources) {
		unsigned int program = glCreateProgram();
		std::vector<unsigned int> shaders;
		shaders.reserve(shaderSources.size());
		for (auto &kv : shaderSources) {
			unsigned int type = kv.first;
			const char *source = kv.second.c_str();
			
			unsigned int shader = glCreateShader(type);
			
			glShaderSource(shader, 1, &source, nullptr);
			glCompileShader(shader);
			
			int isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (!isCompiled) {
				int maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				char *infoLog = (char *) alloca(maxLength * sizeof(char));
				glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);

				glDeleteShader(shader);

				REY_CORE_FATAL("{}", infoLog);
				REY_CORE_ASSERT(false, "Shader (type: {}) failed to compile", type);
				return;
			}
			glAttachShader(program, shader);
			shaders.push_back(shader);
		}
		glLinkProgram(program);

		int isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (!isLinked) {
			int maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			char *infoLog = (char *) alloca(maxLength * sizeof(char));
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);
			for (auto shader : shaders)
				glDeleteShader(shader);

			REY_CORE_FATAL("{}", infoLog);
			REY_CORE_ASSERT(false, "Shaders failed to link");
		}
		
		for (auto shader : shaders)
			glDetachShader(program, shader);
		
		m_ID = program;
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_ID);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_ID);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	int OpenGLShader::GetUniformLocation(const char *name) {
		if ((m_UniformLocationCache.find(name)) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		int location = glGetUniformLocation(m_ID, name);
		m_UniformLocationCache[name] = location;
		if (location == -1) REY_CORE_WARN("Uniform '{}' doesn't exist", name);
		return location;
	}
}
