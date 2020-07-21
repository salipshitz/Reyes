#pragma once

#include <glad/glad.h>
#include <Reyes/RenderAPI/Shader.h>
#include <glm/gtc/type_ptr.hpp>

#define _REY_OGL_SHADER_UNIFORM_METHOD(T, suffix, ...) void SetUniform(const char *name, T val, identity<T>) {glUniform##suffix(GetUniformLocation(name), __VA_ARGS__);}

namespace Reyes::RenderAPI {
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string &vertexSrc, const std::string &fragmentSrc);
		explicit OpenGLShader(const std::string &filePath);
		~OpenGLShader() override;
		
		void Bind() const override;
		void Unbind() const override;

		template<typename T>
		inline void SetUniform(const char *name, T val) { SetUniform(name, val, identity<T>()); }

	private:
		std::unordered_map<unsigned int, std::string> Preprocess(const std::string &source);
		void Compile(const std::unordered_map<unsigned int, std::string> &shaderSources);
		
		template<typename T>
		struct identity {};
		
		_REY_OGL_SHADER_UNIFORM_METHOD(float, 1f, val)
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::vec2, 2f, val.x, val.y);
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::vec3, 3f, val.x, val.y, val.z)
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::vec4, 4f, val.x, val.y, val.z, val.w)

		_REY_OGL_SHADER_UNIFORM_METHOD(int, 1i, val)
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::ivec2, 2i, val.x, val.y);
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::ivec3, 3i, val.x, val.y, val.z)
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::ivec4, 4i, val.x, val.y, val.z, val.w)

		_REY_OGL_SHADER_UNIFORM_METHOD(unsigned int, 1ui, val)
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::uvec2, 2ui, val.x, val.y);
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::uvec3, 3ui, val.x, val.y, val.z)
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::uvec4, 4ui, val.x, val.y, val.z, val.w)

		_REY_OGL_SHADER_UNIFORM_METHOD(glm::mat2, Matrix2fv, 1, false, glm::value_ptr(val))
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::mat3, Matrix3fv, 1, false, glm::value_ptr(val))
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::mat4, Matrix4fv, 1, false, glm::value_ptr(val))
		
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::mat3x2, Matrix3x2fv, 1, false, glm::value_ptr(val))
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::mat2x3, Matrix2x3fv, 1, false, glm::value_ptr(val))

		_REY_OGL_SHADER_UNIFORM_METHOD(glm::mat2x4, Matrix2x4fv, 1, false, glm::value_ptr(val))
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::mat4x2, Matrix4x2fv, 1, false, glm::value_ptr(val))

		_REY_OGL_SHADER_UNIFORM_METHOD(glm::mat3x4, Matrix3x4fv, 1, false, glm::value_ptr(val))
		_REY_OGL_SHADER_UNIFORM_METHOD(glm::mat4x3, Matrix4x3fv, 1, false, glm::value_ptr(val))

		int GetUniformLocation(const char *name);

		std::unordered_map<const char *, int> m_UniformLocationCache;
		unsigned int m_ID{};
	};
}
