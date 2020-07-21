#include <pch>
#include "Text.h"

#include <glm/glm.hpp>

#include "RenderAPI/Buffer.h"
#include "RenderAPI/VertexArray.h"
#include "RenderAPI/Texture.h"

#include "stb_truetype.h"

namespace Reyes
{
	Text::Text(Ref<Transform> transform, const std::string &text, Ref<RenderAPI::AtlasTexture> fontAtlas, uint16_t maxWidth) : m_Text(text), m_Transform(transform), m_FontAtlas(fontAtlas)
	{
		int indicesSize = 6 * text.size() * sizeof(uint32_t);
		auto indices = (uint32_t *)alloca(indicesSize);

		// TODO: Optimize
		for (uint16_t i = 0; i < text.size(); i++)
		{
			indices[6 * i + 0] = 4 * i;
			indices[6 * i + 1] = 4 * i + 1;
			indices[6 * i + 2] = 4 * i + 2;
			indices[6 * i + 3] = 4 * i;
			indices[6 * i + 4] = 4 * i + 2;
			indices[6 * i + 5] = 4 * i + 3;
		}

		RenderAPI::BufferLayout layout{
			{RenderAPI::ShaderDataType::Float3, "i_Position"},
			{RenderAPI::ShaderDataType::Float2, "i_TexCoord"}};
		m_VB = RenderAPI::VertexBuffer::Create({}, 0, layout);
		m_IB = RenderAPI::IndexBuffer::Create(&indices[0], indicesSize);
		m_VA = RenderAPI::VertexArray::Create();
		m_VA->AddVertexBuffer(m_VB);
		m_VA->SetIndexBuffer(m_IB);
		if (maxWidth > 0)
			Resize(maxWidth);
	}

	void Text::Resize(uint16_t maxWidth)
	{
		// TODO: Optimize
		std::vector<float> vertices;

		bool firstWord = true;
		uint16_t wordIndex = 0;
		uint16_t wordVerticesBegin = 0;

		float offX = 0, offY = m_FontAtlas->GetSize();
		for (uint16_t i = 0; i < m_Text.size(); i++)
		{
			auto verts = m_FontAtlas->GetGlyph(m_Text[i], &offX, &offY);
			vertices.insert(vertices.end(), verts.begin(), verts.end());

			switch (m_Text[i])
			{
			case ' ':
			case '.':
			case '!':
			case '?':
			case ',':
			case ':':
			case ';':
			case '(':
			case ')':
			case '[':
			case ']':
				// REY_CORE_TRACE("{}, {}", wordIndex,m_Text.substr(wordIndex, i - wordIndex));
				wordVerticesBegin = vertices.size();
				wordIndex = i + 1;
				firstWord = false;
				break;
			default:
				if (offX <= maxWidth || firstWord)
					break;
				vertices.erase(vertices.begin() + wordVerticesBegin, vertices.end());
				firstWord = true;
				i = wordIndex;
				offX = 0;
				offY += m_FontAtlas->GetSize();
				break;
			}
		}

		m_VB->SetData(&vertices[0], vertices.size());
	}
} // namespace Reyes
