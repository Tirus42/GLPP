#pragma once

#include "OpenGL++/GL3Types.h"

namespace GLPP {

enum TextureTarget {
	TT_TEXTURE_1D = GL_TEXTURE_1D,
	TT_TEXTURE_2D = GL_TEXTURE_2D,
	TT_TEXTURE_3D = GL_TEXTURE_3D,
	TT_TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
	TT_TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
	TT_TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
	TT_TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
	TT_TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
	TT_TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
	TT_TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
	TT_TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
};

enum TextureInternalFormat {
	TIF_RED = GL_RED,
	TIF_RG = GL_RG,
	TIF_RGB = GL_RGB,
	TIF_BGR = GL_BGR,
	TIF_RGBA = GL_RGBA,
	TIF_BGRA = GL_BGRA,
	TIF_DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
	TIF_DEPTH_STENCIL = GL_DEPTH_STENCIL
};

enum TextureFormat {
	TF_RED = GL_RED,
	TF_RG = GL_RG,
	TF_RGB = GL_RGB,
	TF_BGR = GL_BGR,
	TF_RGBA = GL_RGBA,
	TF_BGRA = GL_BGRA,
	TF_RED_INTEGER = GL_RED_INTEGER,
	TF_RG_INTEGER = GL_RG_INTEGER,
	TF_RGB_INTEGER = GL_RGB_INTEGER,
	TF_BGR_INTEGER = GL_BGR_INTEGER,
	TF_RGBA_INTEGER = GL_RGBA_INTEGER,
	TF_BGRA_INTEGER = GL_BGRA_INTEGER,
	TF_STENCIL_INDEX = GL_STENCIL_INDEX,
	TF_DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
	TF_DEPTH_STENCIL = GL_DEPTH_STENCIL
};

enum TextureFormatType {
	TFT_UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	TFT_BYTE = GL_BYTE,
	TFT_UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	TFT_SHORT = GL_SHORT,
	TFT_UNSIGNED_INT = GL_UNSIGNED_INT,
	TFT_INT = GL_INT,
	TFT_FLOAT = GL_FLOAT
};

class OpenGLTexture {
	private:
		GLuint tex;
		TextureTarget target;

		OpenGLTexture& operator=(const OpenGLTexture&);
		OpenGLTexture(const OpenGLTexture&);

	public:
		OpenGLTexture(TextureTarget target) : tex(0), target(target) {
			glGenTextures(1, &tex);
		}

		~OpenGLTexture() {
			glDeleteTextures(1, &tex);
		}

		void bind() {
			glBindTexture(GLenum(target), tex);
		}

		void bind(unsigned int texNr) {
			glActiveTexture(GL_TEXTURE0 + texNr);
			bind();
		}

		void release() {
			glBindTexture(GLenum(target), 0);
		}

		void release(unsigned int texNr) {
			glActiveTexture(GL_TEXTURE0 + texNr);
			release();
		}

		void uploadData1D(GLint mipLevel, TextureInternalFormat internalFormat, GLsizei width, TextureFormat dataFormat, TextureFormatType dataType, const void* data) {
			glTexImage1D(target, mipLevel, GLenum(internalFormat), width, 0, GLenum(dataFormat), GLenum(dataType), data);
		}

		void uploadData2D(GLint mipLevel, TextureInternalFormat internalFormat, GLsizei width, GLsizei height, TextureFormat dataFormat, TextureFormatType dataType, const void* data) {
			glTexImage2D(target, mipLevel, GLenum(internalFormat), width, height, 0, GLenum(dataFormat), GLenum(dataType), data);
		}

		// @Depricated: Use uploadData2D instead
		void uploadData(GLint mipLevel, TextureInternalFormat internalFormat, GLsizei width, GLsizei height, TextureFormat dataFormat, TextureFormatType dataType, const void* data) {
			uploadData2D(mipLevel, internalFormat, width, height, dataFormat, dataType, data);
		}

		void uploadData3D(GLint mipLevel, TextureInternalFormat internalFormat, GLsizei width, GLsizei height, GLsizei depth, TextureFormat dataFormat, TextureFormatType dataType, const void* data) {
			glTexImage3D(target, mipLevel, GLenum(internalFormat), width, height, depth, 0, GLenum(dataFormat), GLenum(dataType), data);
		}

		void generateMipMaps() {
			glGenerateMipmap(target);
		}

		GLuint getTexture() const {
			return tex;
		}

		TextureTarget getTextureType() const {
			return target;
		}
};

}
