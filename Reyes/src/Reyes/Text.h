#include <Reyes/Core/Log.h>

#include <fstream>

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Transform.h"
#include "RenderAPI/Texture.h"
#include "RenderAPI/Buffer.h"
#include "RenderAPI/VertexArray.h"

namespace Reyes
{
	struct Glyph
	{
		float offX, offY;
		glm::vec3 positions[4];
		glm::vec2 texCoords[4];
	};

	class Text
	{
	public:
		Text(Ref<Transform> transform, const std::string &text, Ref<RenderAPI::AtlasTexture> fontAtlas, uint16_t maxWidth = 0);

		[[nodiscard]] inline Ref<Transform> GetTransform() { return m_Transform; }
		[[nodiscard]] inline Ref<RenderAPI::AtlasTexture> GetFontAtlas() { return m_FontAtlas; }
		[[nodiscard]] inline Ref<RenderAPI::VertexArray> GetVertexArray() { return m_VA; }

		void Resize(uint16_t maxWidth);

	private:
		Ref<Transform> m_Transform;
		std::string m_Text;
		Ref<RenderAPI::AtlasTexture> m_FontAtlas;
		Ref<RenderAPI::VertexBuffer> m_VB;
		Ref<RenderAPI::IndexBuffer> m_IB;
		Ref<RenderAPI::VertexArray> m_VA;
	};
} // namespace Reyes::RenderAPI