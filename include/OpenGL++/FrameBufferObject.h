#pragma once

#include "OpenGL++/GL3Types.h"
#include "OpenGL++/Texture.h"

namespace GLPP {

enum AttachmentType {
	AT_COLOR_ATTACHMENT0 = GL_COLOR_ATTACHMENT0,
	AT_COLOR_ATTACHMENT1 = GL_COLOR_ATTACHMENT1,
	AT_COLOR_ATTACHMENT2 = GL_COLOR_ATTACHMENT2,
	AT_COLOR_ATTACHMENT3 = GL_COLOR_ATTACHMENT3,
	AT_COLOR_ATTACHMENT4 = GL_COLOR_ATTACHMENT4,
	AT_COLOR_ATTACHMENT5 = GL_COLOR_ATTACHMENT5,
	AT_COLOR_ATTACHMENT6 = GL_COLOR_ATTACHMENT6,
	AT_COLOR_ATTACHMENT7 = GL_COLOR_ATTACHMENT7,
	AT_DEPTH_ATTACHMENT = GL_DEPTH_ATTACHMENT,
	AT_STENCIL_ATTACHMENT = GL_STENCIL_ATTACHMENT,
	AT_DEPTH_STENCIL_ATTACHMENT = GL_DEPTH_STENCIL_ATTACHMENT
};

enum RenderBufferStorageFormat {
	// Note: These may be equivalent to texture formats.
	RBSF_DEPTH_COMPONENT16 = GL_DEPTH_COMPONENT16,
	RBSF_DEPTH_COMPONENT24 = GL_DEPTH_COMPONENT24,
	RBSF_DEPTH_COMPONENT32 = GL_DEPTH_COMPONENT32,
	RBSF_DEPTH_COMPONENT32F = GL_DEPTH_COMPONENT32F,
	RBSF_DEPTH24_DENCIL8 = GL_DEPTH24_STENCIL8,
	RBSF_DEPTH32F_STENCIL8 = GL_DEPTH32F_STENCIL8,
};

enum RenderBufferBindType {
	RBBT_DRAW = GL_DRAW_FRAMEBUFFER,
	RBBT_READ = GL_READ_FRAMEBUFFER,
	RBBT_READ_AND_DRAW = GL_FRAMEBUFFER
};

class OpenGLRenderBufferObject {
	private:
		GLuint rbo;

		OpenGLRenderBufferObject(const OpenGLRenderBufferObject&) = delete;
		OpenGLRenderBufferObject& operator=(const OpenGLRenderBufferObject&) = delete;

	public:
		OpenGLRenderBufferObject() : rbo(0) {
			glGenRenderbuffers(1, &rbo);
		}
		OpenGLRenderBufferObject(OpenGLRenderBufferObject&& other) :
			rbo(other.rbo) {
			other.rbo = 0u;
		}
		~OpenGLRenderBufferObject() {
			if (rbo)
				glDeleteRenderbuffers(1, &rbo);
		}

		void bind() const {
			glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		}

		void release() const {
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}

		void setRenderbufferStorage(RenderBufferStorageFormat storageFormat, GLsizei width, GLsizei height) {
			glRenderbufferStorage(GL_RENDERBUFFER, storageFormat, width, height);
		}

		GLuint getRenderbuffer() const {
			return rbo;
		}
};

class OpenGLFrameBufferObject {
	private:
		GLuint fbo;

		OpenGLFrameBufferObject(const OpenGLFrameBufferObject&) = delete;
		OpenGLFrameBufferObject& operator=(const OpenGLFrameBufferObject&) = delete;

	public:
		OpenGLFrameBufferObject() :fbo(0) {
			glGenFramebuffers(1, &fbo);
		}
		OpenGLFrameBufferObject(OpenGLFrameBufferObject&& other) :
			fbo(other.fbo) {
			other.fbo = 0u;
		}
		~OpenGLFrameBufferObject() {
			if (fbo)
				glDeleteFramebuffers(1, &fbo);
		}

		void bind(RenderBufferBindType bindMode) const {
			glBindFramebuffer(bindMode, fbo);
		}

		void release(RenderBufferBindType bindMode) const {
			glBindFramebuffer(bindMode, 0);
		}

		void attachTextureTarget1D(AttachmentType attachmentType, OpenGLTexture& texture, GLint mipLevel) {
			glFramebufferTexture1D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_1D, texture.getTexture(), mipLevel);
		}

		void attachTextureTarget2D(AttachmentType attachmentType, OpenGLTexture& texture, GLint mipLevel) {
			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_2D, texture.getTexture(), mipLevel);
		}

		void attachTextureTarget3D(AttachmentType attachmentType, OpenGLTexture& texture, GLint mipLevel, GLint layer) {
			glFramebufferTexture3D(GL_FRAMEBUFFER, attachmentType, GL_TEXTURE_3D, texture.getTexture(), mipLevel, layer);
		}

		void attachRenderTarget(OpenGLRenderBufferObject& rbo, AttachmentType attachmentType) {
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentType, GL_RENDERBUFFER, rbo.getRenderbuffer());
		}

		bool checkCompleted() const {
			return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		}

		GLuint getFramebuffer() const {
			return fbo;
		}
};

}
