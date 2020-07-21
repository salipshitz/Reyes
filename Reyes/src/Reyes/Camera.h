#pragma once

#include <Reyes/Core/Application.h>
#include <Reyes/Transform.h>
#include <Reyes/Core/Window.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Reyes
{
	class Camera : public Transform
	{
	public:
		explicit Camera(const char *name, glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale,
						Transform *parent) : Transform(name, translation, rotation, scale, parent) {}
		virtual ~Camera() = default;

		[[nodiscard]] virtual glm::mat4 GetViewProjectionMatrix() = 0;

		virtual void Resize(float left, float right, float top, float bottom) = 0;
	};

	class OrthographicCamera : public Camera
	{
	public:
		explicit OrthographicCamera(const char *name, glm::vec3 translation = {0, 0, 0}, glm::vec3 rotation = {0, 0, 0},
									glm::vec3 scale = {1, 1, 1}, Transform *parent = nullptr)
			: Camera(name, translation, rotation, scale, parent)
		{
			glm::vec2 windowSize = Application::Get().GetWindow().GetSize();
			m_Left = -windowSize.x / 2;
			m_Right = windowSize.x / 2;
			m_Bottom = -windowSize.y / 2;
			m_Top = windowSize.y / 2;
		}

		OrthographicCamera(const char *name, float left, float right, float top, float bottom,
						   glm::vec3 translation = {0, 0, 0}, glm::vec3 rotation = {0, 0, 0},
						   glm::vec3 scale = {1, 1, 1}, Transform *parent = NULL)
			: Camera(name, translation, rotation, scale, parent), m_Left(left), m_Right(right),
			  m_Top(top), m_Bottom(bottom)
		{
		}
		~OrthographicCamera() override = default;

		void Resize(float left, float right, float top, float bottom) override
		{
			m_Left = left;
			m_Right = right;
			m_Top = top;
			m_Bottom = bottom;
		}

		[[nodiscard]] glm::mat4 GetViewProjectionMatrix() override
		{
			return glm::ortho(m_Left, m_Right, m_Bottom, m_Top, -10.f, 10.f) *
				   glm::inverse(GetTransformMatrix());
		}

	private:
		float m_Top, m_Bottom, m_Left, m_Right;
	};
} // namespace Reyes
