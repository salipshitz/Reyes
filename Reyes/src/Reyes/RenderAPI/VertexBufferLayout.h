#pragma once

#include <Log.h>
#include <vector>

#include <Global.h>

#define VertexPushEntry(T, GL_T, normalized) void Push(unsigned int count, identity<T>) {m_Elements.push_back({GL_T,count,normalized});m_Stride+=count*sizeof(T);}

namespace Renderer {
	struct VertexLayoutElement {
		unsigned int type;
		unsigned int count;
		bool normalized;

		static unsigned int GetSizeOfType(unsigned int type) {
			switch (type) {
				case GL_FLOAT:
					return sizeof(float);
				case GL_UNSIGNED_INT:
					return sizeof(int);
				case GL_UNSIGNED_BYTE:
					return sizeof(char);
				default: ERROR("Unimplemented type")
					return 0;
			}
		}
	};
	
	class VertexBufferLayout {
		std::vector<VertexLayoutElement> m_Elements;
		unsigned int m_Stride;
	public:
		VertexBufferLayout() : m_Stride(0) {}

		template<typename T>
		void Push(unsigned int count) {
			Push(count, identity<T>());
		}

		[[nodiscard]] inline unsigned int GetStride() const { return m_Stride; }
		[[nodiscard]] inline const std::vector<VertexLayoutElement> &GetElements() const { return m_Elements; }

	private:
		VertexPushEntry(float, GL_FLOAT, false)
		VertexPushEntry(unsigned int, GL_UNSIGNED_INT, false)
		VertexPushEntry(unsigned char, GL_UNSIGNED_BYTE, true)
	};
}