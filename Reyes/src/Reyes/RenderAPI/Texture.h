#pragma once

namespace Reyes::RenderAPI
{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		[[nodiscard]] virtual unsigned int GetWidth() const = 0;
		[[nodiscard]] virtual unsigned int GetHeight() const = 0;

		virtual void Bind(unsigned int slot = 0) const = 0;
		virtual void Unbind(unsigned int slot = 0) const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const char *path, bool minNearest, bool magNearest);
	};

	struct Glyph
	{
		float vertices[20];
		float offX, offY;
	};

	class AtlasTexture : public Texture
	{
	public:
		static Ref<AtlasTexture> Create(const char *path, int fontSize);

		[[nodiscard]] virtual std::array<float, 20> GetGlyph(char c, float *offX, float *offY) = 0;

		[[nodiscard]] virtual int GetSize() const = 0;
	};
} // namespace Reyes::RenderAPI