#pragma once

#include <Reyes/RenderAPI/Texture.h>

#include <stb_truetype.h>

namespace Reyes::RenderAPI
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string &path, bool minNearest, bool magNearest);
		~OpenGLTexture2D() override;

		[[nodiscard]] unsigned int GetWidth() const override { return m_Width; }
		[[nodiscard]] unsigned int GetHeight() const override { return m_Height; }

		void Bind(unsigned int slot = 0) const override;
		void Unbind(unsigned int slot = 0) const override;

	private:
		const std::string &m_Path;
		unsigned int m_Width, m_Height, m_ID{};
	};

	class OpenGLAtlasTexture : public AtlasTexture
	{
	public:
		explicit OpenGLAtlasTexture(const char *path, int size);
		~OpenGLAtlasTexture() override;

		[[nodiscard]] int GetSize() const override { return m_Size; }

		void Bind(unsigned int slot = 0) const override;
		void Unbind(unsigned int slot = 0) const override;

		[[nodiscard]] unsigned int GetWidth() const override { return m_AtlasSize; }
		[[nodiscard]] unsigned int GetHeight() const override { return m_AtlasSize; }

		std::array<float, 20> GetGlyph(char c, float *offX, float *offY) override;

	private:
		stbtt_packedchar cdata['~' - ' '];

		const uint32_t m_Size, m_AtlasSize;
		unsigned int m_ID{};
	};
} // namespace Reyes::RenderAPI