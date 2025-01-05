#pragma once

#include "OpenGL++/GL3Types.h"

#include <cassert>

namespace GLPP {

enum VertexUsage {
	VU_STREAM_DRAW = GL_STREAM_DRAW,
	VU_STREAM_READ = GL_STREAM_READ,
	VU_STREAM_COPY = GL_STREAM_COPY,
    VU_STATIC_DRAW = GL_STATIC_DRAW,
    VU_STATIC_READ = GL_STATIC_READ,
    VU_STATIC_COPY = GL_STATIC_COPY,
    VU_DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
    VU_DYNAMIC_READ = GL_DYNAMIC_READ,
    VU_DYNAMIC_COPY = GL_DYNAMIC_COPY
};

enum VertexType {
	VT_BYTE = GL_BYTE,
	VT_UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    VT_SHORT = GL_SHORT,
    VT_UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    VT_INT = GL_INT,
    VT_UNSIGNED_INT = GL_UNSIGNED_INT,
    VT_HALF_FLOAT = GL_HALF_FLOAT,
    VT_FLOAT = GL_FLOAT,
    VT_DOUBLE = GL_DOUBLE
};

template <size_t CountArrayBuffer, size_t CountIndexBuffer>
class OpenGLVertexArrayObject {
	private:
		GLuint vao;
		GLuint vbo[CountArrayBuffer];
		GLuint iab[CountIndexBuffer];

		OpenGLVertexArrayObject(const OpenGLVertexArrayObject&) = delete;
		OpenGLVertexArrayObject& operator=(const OpenGLVertexArrayObject&) = delete;

	public:
		OpenGLVertexArrayObject() : vao(0), vbo(), iab() {
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			// generate vertex arrays
			glGenBuffers(CountArrayBuffer, vbo);

			#pragma GCC diagnostic push
			#pragma GCC diagnostic ignored "-Wtype-limits"
			for (size_t i = 0; i < CountArrayBuffer; ++i) {
				glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
				glEnableVertexAttribArray(i);
			}
			#pragma GCC diagnostic pop

			// generate index arrays
			glGenBuffers(CountIndexBuffer, iab);

			/*
			for (size_t i = 0; i < CountIndexBuffer; ++i) {
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vab[i]);
			}*/

			glBindVertexArray(0);
		};

		OpenGLVertexArrayObject(OpenGLVertexArrayObject&& other) :
			vao(other.vao),
			vbo(),
			iab() {

			other.vao = 0u;

			#pragma GCC diagnostic push
			#pragma GCC diagnostic ignored "-Wtype-limits"
			for (size_t i = 0; i < CountArrayBuffer; ++i) {
				vbo[i] = other.vbo[i];
				other.vbo[i] = 0u;
			}

			for (size_t i = 0; i < CountIndexBuffer; ++i) {
				iab[i] = other.iab[i];
				other.iab[i] = 0u;
			}
			#pragma GCC diagnostic pop
		}

		~OpenGLVertexArrayObject() {
			if (vao) {
				glDeleteBuffers(CountIndexBuffer, iab);
				glDeleteBuffers(CountArrayBuffer, vbo);

				glDeleteVertexArrays(1, &vao);
			}
		}

		void bind() const {
			glBindVertexArray(vao);
		}

		void release() const {
			glBindVertexArray(0);
		}

		void bindBufferBase(size_t index) {
			glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, index, vao);
		}

		void setVertexFormat(size_t index, size_t compSize, VertexType type, bool normalized, size_t stride) {
			assert(index < CountArrayBuffer);

			glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);
			glVertexAttribPointer(index, compSize, GLenum(type), normalized, stride, 0);
		}

		void setVertexIntegerFormat(size_t index, size_t compSize, VertexType type, size_t stride) {
			assert(index < CountArrayBuffer);

			glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);
			glVertexAttribIPointer(index, compSize, GLenum(type), stride, 0);
		}

		void setVertexBindingDivisor(size_t index, size_t divisor) {
			assert(index < CountArrayBuffer);

			glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);
			glVertexBindingDivisor(index, divisor);
		}

		void uploadVertexData(size_t index, size_t size, const void* data, VertexUsage usage) {
			assert(index < CountArrayBuffer);

			glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);
			glBufferData(GL_ARRAY_BUFFER, size, data, GLenum(usage));
		}

		template <typename T>
		void uploadVertexData(size_t index, const T* data, size_t length, VertexUsage usage) {
			uploadVertexData(index, sizeof(data[0]) * length, data, usage);
		}

		void uploadVertexSubData(size_t index, size_t offset, size_t size, const void* data) {
			assert(index < CountArrayBuffer);

			glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		}

		void downloadVertexSubData(size_t index, size_t offset, size_t size, void* targetBuffer) {
			assert(index < CountArrayBuffer);

			glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);
			glGetBufferSubData(GL_ARRAY_BUFFER, offset, size, targetBuffer);
		}

		template <typename T>
		void uploadIndexData(size_t index, const T* data, size_t length, VertexUsage usage) {
			uploadIndexData(index, sizeof(data[0]) * length, data, usage);
		}

		void uploadIndexData(size_t index, size_t size, const void* data, VertexUsage usage) {
			assert(index < CountIndexBuffer);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iab[index]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GLenum(usage));
		}

		void uploadIndexSubData(size_t index, size_t offset, size_t size, const void* data) {
			assert(index < CountIndexBuffer);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iab[index]);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
		}

		void downloadIndexSubData(size_t index, size_t offset, size_t size, void* targetBuffer) {
			assert(index < CountIndexBuffer);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iab[index]);
			glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, targetBuffer);
		}
};

/*
class OpenGLVertexArrayBuffer {
	private:
		GLuint vab;

	public:
		OpenGLVertexArrayBuffer();
		~OpenGLVertexArrayBuffer();

		void bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, vab);
		}

		void release() const {
			glBindBuffer(GL_ARRAY_BUFFER, vab);
		}

		void uploadData(size_t size, const void* data, VertexUsage usage = VU_DEFAULT) {
			glBufferData(GL_ARRAY_BUFFER, size, data, GLenum(usage));
		}

};
*/

}
