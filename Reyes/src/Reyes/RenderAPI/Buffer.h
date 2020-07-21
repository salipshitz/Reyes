#pragma once

#include <Reyes/Core/Log.h>

namespace Reyes::RenderAPI {
	class BufferLayout;

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(void *vertices, size_t size) = 0;

		[[nodiscard]] virtual const BufferLayout &GetLayout() const = 0;

		static Ref<VertexBuffer> Create(void *vertices, size_t size, BufferLayout layout);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		[[nodiscard]] virtual unsigned int GetCount() const = 0;

		static Ref<IndexBuffer> Create(unsigned int *indices, unsigned int size);
	};

	class ShaderDataType {
	public:
		enum Value : unsigned char {
			None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool
		};

		ShaderDataType(Value val = Value::None) : m_Value(val) {}

		operator Value() const { return m_Value; }
		ShaderDataType &operator=(Value other) {
			m_Value = other;
			return *this;
		}
		bool operator==(Value other) const { return m_Value == other; }
		bool operator!=(Value other) const { return m_Value != other; }

		unsigned int Size() {
			switch (m_Value) {
				case ShaderDataType::Bool:
					return 1;
				case ShaderDataType::Float:
				case ShaderDataType::Int:
					return 4;
				case ShaderDataType::Float2:
				case ShaderDataType::Int2:
					return 8;
				case ShaderDataType::Float3:
				case ShaderDataType::Int3:
					return 12;
				case ShaderDataType::Float4:
				case ShaderDataType::Int4:
					return 16;
				case ShaderDataType::Mat3:
					return 36;
				case ShaderDataType::Mat4:
					return 64;
				default: REY_CORE_ASSERT(false, "Unknown ShaderDataType");
					return 0;
			}
		}

		[[nodiscard]] unsigned int ToGL() const;
	private:
		Value m_Value;
	};

	struct LayoutElement {
		std::string Name;
		ShaderDataType Type;
		bool Normalized;
		unsigned int Size;
		unsigned int Offset;
		
		LayoutElement(ShaderDataType type, std::string name, bool normalized = false)
				: Type(type), Name(std::move(name)), Normalized(normalized), Size(type.Size()), Offset(0) {}

		[[nodiscard]] unsigned int GetCount() const {
			switch (Type) {
				case ShaderDataType::Float:
				case ShaderDataType::Int:
				case ShaderDataType::Bool:
					return 1;
				case ShaderDataType::Float2:
				case ShaderDataType::Int2:
					return 2;
				case ShaderDataType::Float3:
				case ShaderDataType::Int3:
					return 3;
				case ShaderDataType::Float4:
				case ShaderDataType::Int4:
					return 4;
				case ShaderDataType::Mat3:
					return 9;
				case ShaderDataType::Mat4:
					return 16;
				default: REY_CORE_ASSERT(false, "Unknown ShaderDataType");
					return 0;
			}
		}
	};

	class BufferLayout {
	public:
		BufferLayout(const std::initializer_list<LayoutElement> &elements) : m_Elements(elements), m_Stride(0) {
			for (LayoutElement &element : m_Elements) {
				element.Offset = m_Stride;
				m_Stride += element.Size;
			}
		}

		[[nodiscard]] inline const std::vector<LayoutElement> &GetElements() const { return m_Elements; }
		[[nodiscard]] inline unsigned int GetStride() const { return m_Stride; }

		[[nodiscard]] inline std::vector<LayoutElement>::iterator begin() { return m_Elements.begin(); }
		[[nodiscard]] inline std::vector<LayoutElement>::iterator end() { return m_Elements.end(); }

	private:
		std::vector<LayoutElement> m_Elements;
		unsigned int m_Stride = 0;
	};
}