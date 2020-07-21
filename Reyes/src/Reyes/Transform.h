#pragma once

#include <pch>
#include <Reyes/Core/Core.h>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Reyes {
	class  Transform {
	public:
		explicit Transform(const char *name, glm::vec3 translation = {0, 0, 0}, glm::vec3 rotation = {0, 0, 0},
		                   glm::vec3 scale = {1, 1, 1}, Transform *parent = nullptr);


		[[nodiscard]] inline const glm::vec3 &GetTranslation() const { return m_Translation; }
		[[nodiscard]] inline const glm::vec3 &GetRotation() const { return m_Rotation; }
		[[nodiscard]] inline const glm::vec3 &GetScale() const { return m_Scale; }

		inline void SetTranslation(const glm::vec3 &translation) {
			m_Translation = translation;
			CalculateTransformMatrix();
		}
		inline void SetRotation(const glm::vec3 &rotation) {
			m_Rotation = rotation;
			CalculateTransformMatrix();
		}
		inline void SetScale(const glm::vec3 &scale) {
			m_Scale = scale;
			CalculateTransformMatrix();
		}

		inline void Translate(const glm::vec3 &translation) {
			m_Translation += translation;
			CalculateTransformMatrix();
		}
		inline void Rotate(const glm::vec3 &rotation) {
			m_Rotation += rotation;
			CalculateTransformMatrix();
		}
		inline void Rotate(float rotation) { Rotate({0, 0, rotation}); }
		inline void Scale(const glm::vec3 &scale) {
			m_Scale += scale;
			CalculateTransformMatrix();
		}
		inline void Scale(float scale) { Scale({scale, scale, scale}); }

		[[nodiscard]] inline const glm::mat4 &GetTransformMatrix() { return m_TransformMatrix; }

		void CalculateTransformMatrix();

		[[nodiscard]] inline Transform *GetParent() { return m_Parent; }
		[[nodiscard]] inline std::vector<Transform *> GetChildren() { return m_Children; }

	private:
		Transform() : m_Name("Root"), m_Translation(0, 0, 0), m_Rotation(0, 0, 0), m_Scale(1, 1, 1),
		              m_Parent(nullptr) { CalculateTransformMatrix(); }

		const char *m_Name;

		glm::vec3 m_Translation;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;

		glm::mat4 m_TransformMatrix{};

		Transform *m_Parent;
		std::vector<Transform *> m_Children;

		static Transform *s_WorldTransform;
		
	};
}
