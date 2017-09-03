#pragma once

#include "OpenGL++/GL3Types.h"

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
	public:
		GLuint vao;
		GLuint vbo[CountArrayBuffer];
		GLuint iab[CountIndexBuffer];

	public:
		OpenGLVertexArrayObject() : vao(0), vbo(), iab() {
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			// generate vertex arrays
			glGenBuffers(CountArrayBuffer, vbo);

			for (size_t i = 0; i < CountArrayBuffer; ++i) {
				glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
				glEnableVertexAttribArray(i);
			}

			// generate index arrays
			glGenBuffers(CountIndexBuffer, iab);

			/*
			for (size_t i = 0; i < CountIndexBuffer; ++i) {
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vab[i]);
			}*/

			glBindVertexArray(0);
		};
		~OpenGLVertexArrayObject() {
			// todo
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
			glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);

			glVertexAttribPointer(index, compSize, GLenum(type), normalized, stride, 0);
		}

		void setVertexIntegerFormat(size_t index, size_t compSize, VertexType type, size_t stride) {
			glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);

			glVertexAttribIPointer(index, compSize, GLenum(type), stride, 0);
		}

		void uploadVertexData(size_t index, size_t size, const void* data, VertexUsage usage) {
			glBindBuffer(GL_ARRAY_BUFFER, vbo[index]);

			glBufferData(GL_ARRAY_BUFFER, size, data, GLenum(usage));
		}

		void uploadIndexData(size_t index, size_t size, const void* data, VertexUsage usage) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iab[index]);

			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GLenum(usage));
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
