#pragma once

#include "OpenGL++/GL3Types.h"

#include <vector>

namespace GLPP {

enum ShaderType {
	SHADER_VERTEX = GL_VERTEX_SHADER,
	SHADER_TESSCONTROL = GL_TESS_CONTROL_SHADER,
	SHADER_TESSEVAL = GL_TESS_EVALUATION_SHADER,
	SHADER_GEOMETRY = GL_GEOMETRY_SHADER,
	SHADER_FRAGMENT = GL_FRAGMENT_SHADER,
};

enum TransformFeedbackOutput {
	TFO_INTERLEAVED_ATTRIBS = GL_INTERLEAVED_ATTRIBS,
	TFO_SEPARATE_ATTRIBS = GL_SEPARATE_ATTRIBS,
};

class OpenGLShaderProgram {
	private:
		GLuint prog;

	public:
		OpenGLShaderProgram();
		~OpenGLShaderProgram();

		bool compile(const char* src, ShaderType type);
		bool compile(const char* src, size_t srcLength, ShaderType type);
		bool compileFile(const char* filename, ShaderType type);

		GLuint get() const {
			return prog;
		}
};

class OpenGLShader {
	private:
		GLuint prog;

		void attachShaders(const OpenGLShaderProgram* vert,
						   const OpenGLShaderProgram* tessControl,
						   const OpenGLShaderProgram* tessEval,
						   const OpenGLShaderProgram* geom,
						   const OpenGLShaderProgram* frag);

		/// normal link
		bool link(const OpenGLShaderProgram* vert,
				  const OpenGLShaderProgram* tessControl,
				  const OpenGLShaderProgram* tessEval,
				  const OpenGLShaderProgram* geom,
				  const OpenGLShaderProgram* frag);

		/// link with transform feedback
		bool link(const OpenGLShaderProgram* vert,
				  const OpenGLShaderProgram* tessControl,
                  const OpenGLShaderProgram* tessEval,
                  const OpenGLShaderProgram* geom,
                  std::vector<const char*> tf_param,
                  TransformFeedbackOutput output);


	public:
		OpenGLShader() :
			prog(0) {}

		~OpenGLShader() {
			if (prog)
				deleteShader();
		}

		bool compileAndLink(const char* src_vertex, const char* src_fragment);
		bool compileAndLink(const char* src_vertex, const char* src_geom, const char* src_fragment);

		bool compileAndLinkTransformFeedback(const char* src_vertex, const std::vector<const char*>& outputVars, TransformFeedbackOutput output);

		bool compileAndLinkFiles(const char* vertexFile, const char* fragmentFile);
		bool compileAndLinkFiles(const char* vertexFile, const char* geomFile, const char* fragmentFile);

		bool compileAndLinkTransformFeedbackFiles(const char* vertexFile, const std::vector<const char*>& outputVars, TransformFeedbackOutput output);
		bool compileAndLinkTransformFeedbackFiles(const char* vertexFile, const char* geomFile, const std::vector<const char*>& outputVars, TransformFeedbackOutput output);

		void deleteShader() {
			glDeleteShader(prog);
			prog = 0;
		}

		GLuint get() const {
			return prog;
		}

		void bind() const {
			glUseProgram(prog);
		}

		void release() const {
			glUseProgram(0);
		}

		void setUniform(const char* name, GLfloat v0) {
			glUniform1f(glGetUniformLocation(prog, name), v0);
		}
		void setUniform(const char* name, GLfloat v0, GLfloat v1) {
			glUniform2f(glGetUniformLocation(prog, name), v0, v1);
		}
		void setUniform(const char* name, GLfloat v0, GLfloat v1, GLfloat v2) {
			glUniform3f(glGetUniformLocation(prog, name), v0, v1, v2);
		}
		void setUniform(const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
			glUniform4f(glGetUniformLocation(prog, name), v0, v1, v2, v3);
		}
		void setUniformMat4(const char* name, const GLfloat* data) {
			glUniformMatrix4fv(glGetUniformLocation(prog, name), 1, GL_FALSE, data);
		}
		void setUniform(const char* name, GLint v0) {
			glUniform1i(glGetUniformLocation(prog, name), v0);
		}
		void setUniform(const char* name, GLint v0, GLint v1) {
			glUniform2i(glGetUniformLocation(prog, name), v0, v1);
		}
		void setUniform(const char* name, GLint v0, GLint v1, GLint v2) {
			glUniform3i(glGetUniformLocation(prog, name), v0, v1, v2);
		}
		void setUniform(const char* name, GLint v0, GLint v1, GLint v2, GLint v3) {
			glUniform4i(glGetUniformLocation(prog, name), v0, v1, v2, v3);
		}
		void setUniform(const char* name, GLuint v0) {
			glUniform1ui(glGetUniformLocation(prog, name), v0);
		}
		void setUniform(const char* name, GLuint v0, GLuint v1) {
			glUniform2ui(glGetUniformLocation(prog, name), v0, v1);
		}
		void setUniform(const char* name, GLuint v0, GLuint v1, GLuint v2) {
			glUniform3ui(glGetUniformLocation(prog, name), v0, v1, v2);
		}
		void setUniform(const char* name, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
			glUniform4ui(glGetUniformLocation(prog, name), v0, v1, v2, v3);
		}

		void swap(OpenGLShader& other) {
			std::swap(prog, other.prog);
		}
};


}
