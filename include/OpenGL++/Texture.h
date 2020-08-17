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
	// standard (undefined size?) texture formats
	TIF_RED = GL_RED,
	TIF_RG = GL_RG,
	TIF_RGB = GL_RGB,
	TIF_BGR = GL_BGR,
	TIF_RGBA = GL_RGBA,
	TIF_BGRA = GL_BGRA,

	// sized texture formats
	TIF_R8 = GL_R8,
	TIF_R8_SNORM = GL_R8_SNORM,
	TIF_R16 = GL_R16,
	TIF_R16_SNORM = GL_R16_SNORM,
	TIF_RG8 = GL_RG8,
	TIF_RG8_SNORM = GL_RG8_SNORM,
	TIF_RG16 = GL_RG16,
	TIF_RG16_SNORM = GL_RG16_SNORM,
	TIF_R3_G3_B2 = GL_R3_G3_B2,
	TIF_RGB4 = GL_RGB4,
	TIF_RGB5 = GL_RGB5,
	TIF_RGB8 = GL_RGB8,
	TIF_RGB8_SNORM = GL_RGB8_SNORM,
	TIF_RGB10 = GL_RGB10,
	TIF_RGB12 = GL_RGB12,
	TIF_RGB16_SNORM = GL_RGB16_SNORM,
	TIF_RGBA2 = GL_RGBA2,
	TIF_RGBA4 = GL_RGBA4,
	TIF_RGB5_A1 = GL_RGB5_A1,
	TIF_RGBA8 = GL_RGBA8,
	TIF_RGBA8_SNORM = GL_RGBA8_SNORM,
	TIF_RGB10_A2 = GL_RGB10_A2,
	TIF_RGB10_A2UI = GL_RGB10_A2UI,
	TIF_RGBA12 = GL_RGBA12,
	TIF_RGBA16 = GL_RGBA16,
	TIF_SRGB8 = GL_SRGB8,
	TIF_SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
	TIF_R16F = GL_R16F,
	TIF_RG16F = GL_RG16F,
	TIF_RGB16F = GL_RGB16F,
	TIF_RGBA16F = GL_RGBA16F,
	TIF_R32F = GL_R32F,
	TIF_RG32F = GL_RG32F,
	TIF_RGB32F = GL_RGB32F,
	TIF_RGBA32F = GL_RGBA32F,
	TIF_R11F_G11F_B10F = GL_R11F_G11F_B10F,
	TIF_RGB9_E5 = GL_RGB9_E5,
	TIF_R8I = GL_R8I,
	TIF_R8UI = GL_R8UI,
	TIF_R16I = GL_R16I,
	TIF_R16UI = GL_R16UI,
	TIF_R32I = GL_R32I,
	TIF_R32UI = GL_R32UI,
	TIF_RG8I = GL_RG8I,
	TIF_RG8UI = GL_RG8UI,
	TIF_RG16I = GL_RG16I,
	TIF_RG16UI = GL_RG16UI,
	TIF_RG32I = GL_RG32I,
	TIF_RG32UI = GL_RG32UI,
	TIF_RGB8I = GL_RGB8I,
	TIF_RGB8UI = GL_RGB8UI,
	TIF_RGB16I = GL_RGB16I,
	TIF_RGB16UI = GL_RGB16UI,
	TIF_RGB32I = GL_RGB32I,
	TIF_RGB32UI = GL_RGB32UI,
	TIF_RGBA8I = GL_RGBA8I,
	TIF_RGBA8UI = GL_RGBA8UI,
	TIF_RGBA16I = GL_RGBA16I,
	TIF_RGBA16UI = GL_RGBA16UI,
	TIF_RGBA32I = GL_RGBA32I,
	TIF_RGBA32UI = GL_RGBA32UI,

	// compressed texture formats
	TIF_COMPRESSED_RED = GL_COMPRESSED_RED ,
	TIF_COMPRESSED_RG = GL_COMPRESSED_RG ,
	TIF_COMPRESSED_RGB = GL_COMPRESSED_RGB ,
	TIF_COMPRESSED_RGBA = GL_COMPRESSED_RGBA ,
	TIF_COMPRESSED_SRGB = GL_COMPRESSED_SRGB ,
	TIF_COMPRESSED_SRGB_ALPHA = GL_COMPRESSED_SRGB_ALPHA ,
	TIF_COMPRESSED_RED_RGTC1 = GL_COMPRESSED_RED_RGTC1 ,
	TIF_COMPRESSED_SIGNED_RED_RGTC1 = GL_COMPRESSED_SIGNED_RED_RGTC1 ,
	TIF_COMPRESSED_RG_RGTC2 = GL_COMPRESSED_RG_RGTC2 ,
	TIF_COMPRESSED_SIGNED_RG_RGTC2 = GL_COMPRESSED_SIGNED_RG_RGTC2 ,
	TIF_COMPRESSED_RGBA_BPTC_UNORM = GL_COMPRESSED_RGBA_BPTC_UNORM ,
	TIF_COMPRESSED_SRGB_ALPHA_BPTC_UNORM = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM ,
	TIF_COMPRESSED_RGB_BPTC_SIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT ,
	TIF_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT ,

	// depth / stencil formats
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
	TFT_FLOAT = GL_FLOAT,
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

		void uploadSubData1D(GLint mipLevel, GLint xoffset, GLsizei width, TextureFormat dataFormat, TextureFormatType dataType, const void* data) {
			glTexSubImage1D(target, mipLevel, xoffset, width, GLenum(dataFormat), GLenum(dataType), data);
		}

		void uploadData2D(GLint mipLevel, TextureInternalFormat internalFormat, GLsizei width, GLsizei height, TextureFormat dataFormat, TextureFormatType dataType, const void* data) {
			glTexImage2D(target, mipLevel, GLenum(internalFormat), width, height, 0, GLenum(dataFormat), GLenum(dataType), data);
		}

		void uploadSubData2D(GLint mipLevel, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, TextureFormat dataFormat, TextureFormatType dataType, const void* data) {
			glTexSubImage2D(target, mipLevel, xoffset, yoffset, width, height, GLenum(dataFormat), GLenum(dataType), data);
		}

		// @Deprecated: Use uploadData2D instead
		void uploadData(GLint mipLevel, TextureInternalFormat internalFormat, GLsizei width, GLsizei height, TextureFormat dataFormat, TextureFormatType dataType, const void* data) {
			uploadData2D(mipLevel, internalFormat, width, height, dataFormat, dataType, data);
		}

		void uploadData3D(GLint mipLevel, TextureInternalFormat internalFormat, GLsizei width, GLsizei height, GLsizei depth, TextureFormat dataFormat, TextureFormatType dataType, const void* data) {
			glTexImage3D(target, mipLevel, GLenum(internalFormat), width, height, depth, 0, GLenum(dataFormat), GLenum(dataType), data);
		}

		void getAllocatedTextureSize2D(GLint mipLevel, GLint& outWidth, GLint& outHeight) {
			glGetTexLevelParameteriv(target, mipLevel, GL_TEXTURE_WIDTH, &outWidth);
			glGetTexLevelParameteriv(target, mipLevel, GL_TEXTURE_HEIGHT, &outHeight);
		}

		void getAllocatedTextureSize2D(GLint mipLevel, GLuint& outWidth, GLuint& outHeight) {
			GLint& uWidth = reinterpret_cast<GLint&>(outWidth);
			GLint& uHeight = reinterpret_cast<GLint&>(outHeight);

			getAllocatedTextureSize2D(mipLevel, uWidth, uHeight);
		}

		/**
		* Downloads the whole texture data and converts it into the specified format.
		* Note to set the GL_PACK_ALIGNMENT properly before using this function.
		*/
		void downloadData(GLint mipLevel, TextureFormat dataFormat, TextureFormatType type, void* data) {
			glGetTexImage(target, mipLevel, GLenum(dataFormat), GLenum(type), data);
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
