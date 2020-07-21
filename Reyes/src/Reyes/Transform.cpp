#include <pch>
#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <ostream>

namespace Reyes {
	Transform *Transform::s_WorldTransform = new Transform;

	Transform::Transform(const char *name, glm::vec3 translation, glm::vec3 rotation, glm::vec3 scale,
	                     Transform *parent) : m_Name(name), m_Translation(translation), m_Rotation(rotation),
	                                          m_Scale(scale), m_Parent(parent ?: s_WorldTransform) {
		m_Parent->m_Children.push_back(this);
		CalculateTransformMatrix();
	}

	void Transform::CalculateTransformMatrix() {
		m_TransformMatrix =
				glm::translate(m_Parent != nullptr ? m_Parent->GetTransformMatrix() : glm::mat4(1.f), m_Translation) *
				glm::toMat4(glm::quat(glm::radians(m_Rotation))) * glm::scale(glm::mat4(1.f), m_Scale);
		for (auto *child : m_Children)
			child->CalculateTransformMatrix();
	}
}
