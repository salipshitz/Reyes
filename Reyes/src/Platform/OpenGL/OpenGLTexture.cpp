#include <pch>
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include <Reyes/Core/Log.h>
#include <filesystem>

#include <fstream>
#include <stb_image_write.h>
#include <string>

namespace Reyes::RenderAPI
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string &path, bool minNearest, bool magNearest) : m_Path(path)
	{
		stbi_set_flip_vertically_on_load(1);

		int width, height, channels;
		REY_CORE_TRACE("CWD: {}", std::filesystem::current_path());
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		REY_CORE_ASSERT(data, "Failed to load image");
		m_Width = width;
		m_Height = height;

		REY_CORE_TRACE("Channels: {}", channels);

		int internalFormat, dataFormat;
		switch (channels)
		{
		case 4:
			dataFormat = GL_RGBA;
			internalFormat = GL_RGBA8;
			break;
		case 3:
			dataFormat = GL_RGB;
			internalFormat = GL_RGB8;
			break;
		case 2:
			dataFormat = GL_RG;
			internalFormat = GL_RG8;
			break;
		case 1:
			dataFormat = GL_R;
			internalFormat = GL_R8;
			break;
		default:
			REY_CORE_ASSERT(false, "Incorrect number of channels");
			return;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
		glTextureStorage2D(m_ID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, magNearest ? GL_NEAREST : GL_LINEAR);
		glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, minNearest ? GL_NEAREST : GL_LINEAR);

		glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_ID);
	}

	void OpenGLTexture2D::Bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, m_ID);
	}

	void OpenGLTexture2D::Unbind(unsigned int slot) const
	{
		glBindTextureUnit(0, m_ID);
	}

	OpenGLAtlasTexture::OpenGLAtlasTexture(const char *path, int size) : m_Size(size), m_AtlasSize(size * 1024 / 100)
	{
		std::ifstream in(path, std::ios::in | std::ios::binary);
		unsigned char *ttf;
		if (!in)
		{
			REY_CORE_ERROR("Failed to open shader asset '{}'", path);
			return;
		}
		in.seekg(0, std::ios::end);
		size_t srcSize = in.tellg();
		ttf = new unsigned char[srcSize];
		in.seekg(0, std::ios::beg);
		in.read((char *)ttf, srcSize);
		in.close();

		unsigned char *atlas = new unsigned char[m_AtlasSize * m_AtlasSize];

		stbtt_pack_context context;
		REY_CORE_ASSERT(stbtt_PackBegin(&context, atlas, m_AtlasSize, m_AtlasSize, 0, 1, NULL), "Failed to initialize font");

		stbtt_PackSetOversampling(&context, 2, 2);
		REY_CORE_ASSERT(stbtt_PackFontRange(&context, ttf, 0, m_Size, ' ', '~' - ' ', cdata), "Failed to pack font");

		stbtt_PackEnd(&context);

		// stbtt_BakeFontBitmap(ttf, 0, m_Size, atlas, ATL_WIDTH, ATL_HEIGHT, ' ', '~' - ' ', cdata);

		delete[] ttf;

		// std::string s;
		// s.reserve(ATL_WIDTH * ATL_HEIGHT);
		// std::cout << std::hex;
		// for (int i = 0; i < s.capacity(); i++)
		// 	std::cout << int(atlas[i]);
		// std::cout << std::endl;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
		glTextureStorage2D(m_ID, 1, GL_R8, m_AtlasSize, m_AtlasSize);

		glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_ID, 0, 0, 0, m_AtlasSize, m_AtlasSize, GL_RED, GL_UNSIGNED_BYTE, atlas);

		delete[] atlas;
	}

	OpenGLAtlasTexture::~OpenGLAtlasTexture()
	{
		glDeleteTextures(1, &m_ID);
	}

	void OpenGLAtlasTexture::Bind(unsigned int slot) const
	{
		glBindTextureUnit(slot, m_ID);
	}

	void OpenGLAtlasTexture::Unbind(unsigned int slot) const
	{
		glBindTextureUnit(0, m_ID);
	}

	std::array<float, 20> OpenGLAtlasTexture::GetGlyph(char c, float *offX, float *offY)
	{
		stbtt_aligned_quad quad;
		stbtt_GetPackedQuad(cdata, m_AtlasSize, m_AtlasSize, c - ' ', offX, offY, &quad, 1);

		return {
			quad.x0, -quad.y0, 0, quad.s0, quad.t0,
			quad.x0, -quad.y1, 0, quad.s0, quad.t1,
			quad.x1, -quad.y1, 0, quad.s1, quad.t1,
			quad.x1, -quad.y0, 0, quad.s1, quad.t0};
	}
} // namespace Reyes::RenderAPI