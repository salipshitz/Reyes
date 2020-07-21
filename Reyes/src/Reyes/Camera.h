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
		[[nodiscard]] virtual glm::mat4 GetUIMatrix() = 0;
	};

	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(const char *name, glm::vec2 topLeft, glm::vec2 bottomRight,
						   glm::vec3 translation = {0, 0, 0}, glm::vec3 rotation = {0, 0, 0},
						   glm::vec3 scale = {1, 1, 1}, Transform *parent = nullptr)
			: Camera(name, translation, rotation, scale, parent), m_TopLeft(topLeft), m_BottomRight(bottomRight) {}
		explicit OrthographicCamera(const char *name, glm::vec3 translation = {0, 0, 0}, glm::vec3 rotation = {0, 0, 0},
									glm::vec3 scale = {1, 1, 1}, Transform *parent = nullptr)
			: Camera(name, translation, rotation, scale, parent),
			  m_TopLeft{-Application::Get().GetWindow().GetSize().x / 2, Application::Get().GetWindow().GetSize().y / 2},
			  m_BottomRight{Application::Get().GetWindow().GetSize().x / 2, -Application::Get().GetWindow().GetSize().y / 2}
		{
		}
		~OrthographicCamera() override = default;

		[[nodiscard]] inline glm::mat4 GetUIMatrix() override
		{
			return glm::ortho(0.f, m_BottomRight.x - m_TopLeft.x, m_BottomRight.y - m_TopLeft.y, 0.f) *
				   glm::inverse(GetTransformMatrix());
		}

		[[nodiscard]] inline glm::mat4 GetViewProjectionMatrix() override
		{
			return glm::ortho(m_TopLeft.x, m_BottomRight.x, m_BottomRight.y, m_TopLeft.y, -1.f, 1.f) *
				   glm::inverse(GetTransformMatrix());
		}

	private:
		glm::vec2 m_TopLeft;
		glm::vec2 m_BottomRight;
	};
} // namespace Reyes
