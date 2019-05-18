#include "OpenGL++/Shader.h"

#include <stdexcept>
#include <vector>
#include <fstream>
#include <cstring>

#include <cassert>

namespace GLPP {

OpenGLShaderProgram::OpenGLShaderProgram() :
	prog(0) {}

OpenGLShaderProgram::~OpenGLShaderProgram() {
	// Note: Delete of a shader object only mark the shader for removal.
	// As long as it is used inside a shader-program it can be used.
	// With the detach or deletion of the shader-program this objects will be released too.
	if (prog)
		glDeleteShader(prog);
}

bool OpenGLShaderProgram::compile(const char* src, ShaderType type) {
	return compile(src, std::strlen(src), type);
}

bool OpenGLShaderProgram::compile(const char* src, size_t strLength, ShaderType type) {
	if (strLength > 0x7FFFFFFF)
		throw std::runtime_error("to long shader source");

	prog = glCreateShader((GLenum)type);

	const char* strArray[1] = {src};
	GLint lenArray[1] = { static_cast<GLint>(strLength) };

	glShaderSource(prog, 1, strArray, lenArray);
	glCompileShader(prog);

	GLint success;
	glGetShaderiv(prog, GL_COMPILE_STATUS, &success);

	if (!success) {
		char infolog[2048];
		glGetShaderInfoLog(prog, sizeof(infolog), NULL, infolog);

		printf("Error compiling shader: %s\n", infolog);
		glDeleteShader(prog);
		return 0;
	}

	return prog;
}


bool OpenGLShaderProgram::compileFile(const char* filename, ShaderType type) {
	// open the file at the end
	std::ifstream f(filename, std::ios::ate | std::ios::binary);

	if (!f.is_open())
		return false;

	// get the total file size
	std::streampos fileSize = f.tellg();

	// seek back to the start
	f.seekg(0, f.beg);

	std::vector<char> source;
	source.resize(fileSize + std::streampos(1));	// +1 for null termination

	// read the source
    f.read(source.data(), fileSize);

    // compile the source
    return compile(source.data(), type);
}

void OpenGLShader::attachShaders(const OpenGLShaderProgram* vert,
								 const OpenGLShaderProgram* tessControl,
								 const OpenGLShaderProgram* tessEval,
								 const OpenGLShaderProgram* geom,
								 const OpenGLShaderProgram* frag) {
	assert(prog != 0);

	if (vert)
		glAttachShader(prog, vert->get());
	if (tessControl)
		glAttachShader(prog, tessControl->get());
	if (tessEval)
		glAttachShader(prog, tessEval->get());
	if (geom)
		glAttachShader(prog, geom->get());
	if (frag)
		glAttachShader(prog, frag->get());
}

bool OpenGLShader::link(const OpenGLShaderProgram* vert,
						const OpenGLShaderProgram* tessControl,
						const OpenGLShaderProgram* tessEval,
						const OpenGLShaderProgram* geom,
						const OpenGLShaderProgram* frag) {
	assert(prog == 0);
	prog = glCreateProgram();

	attachShaders(vert, tessControl, tessEval, geom, frag);

	glLinkProgram(prog);

	GLint success;
	glGetProgramiv(prog, GL_LINK_STATUS, &success);
	if (!success) {
		char infolog[2048];
		glGetProgramInfoLog(prog, sizeof(infolog), NULL, infolog);
		printf("Error linking shader program: %s\n", infolog);

		// todo cleanup

		return false;
	}

	return true;
}

bool OpenGLShader::link(const OpenGLShaderProgram* vert,
						const OpenGLShaderProgram* tessControl,
						const OpenGLShaderProgram* tessEval,
						const OpenGLShaderProgram* geom,
						std::vector<const char*>tf_param,
						TransformFeedbackOutput output) {

	assert(prog == 0);
	prog = glCreateProgram();

	attachShaders(vert, tessControl, tessEval, geom, 0);

	glTransformFeedbackVaryings(prog, tf_param.size(), (const char**)tf_param.data(), GLenum(output));

	glLinkProgram(prog);

	GLint success;
	glGetProgramiv(prog, GL_LINK_STATUS, &success);
	if (!success) {
		char infolog[2048];
		glGetProgramInfoLog(prog, sizeof(infolog), NULL, infolog);
		printf("Error linking shader program: %s\n", infolog);

		// todo cleanup

		return false;
	}

	return true;
}

bool OpenGLShader::compileAndLink(const char* src_vertex, const char* src_fragment) {
	OpenGLShaderProgram vertShader;
	OpenGLShaderProgram fragShader;

	if (!vertShader.compile(src_vertex, SHADER_VERTEX))
		return false;
	if (!fragShader.compile(src_fragment, SHADER_FRAGMENT))
		return false;

	return link(&vertShader, 0, 0, 0, &fragShader);
}

bool OpenGLShader::compileAndLink(const char* src_vertex, const char* src_geometry, const char* src_fragment) {
	OpenGLShaderProgram vertShader;
	OpenGLShaderProgram geomShader;
	OpenGLShaderProgram fragShader;

	if (!vertShader.compile(src_vertex, SHADER_VERTEX))
		return false;
	if (!geomShader.compile(src_geometry, SHADER_GEOMETRY))
		return false;
	if (!fragShader.compile(src_fragment, SHADER_FRAGMENT))
		return false;

	return link(&vertShader, 0, 0, &geomShader, &fragShader);
}

bool OpenGLShader::compileAndLinkTransformFeedback(const char* src_vertex, const std::vector<const char*>& outputVars, TransformFeedbackOutput output) {
	OpenGLShaderProgram vertShader;

	if (!vertShader.compile(src_vertex, SHADER_VERTEX))
		return false;

	return link(&vertShader, 0, 0, 0, outputVars, output);
}

bool OpenGLShader::compileAndLinkFiles(const char* vertexFile, const char* fragmentFile) {
	OpenGLShaderProgram vertShader;
	OpenGLShaderProgram fragShader;

	if (!vertShader.compileFile(vertexFile, SHADER_VERTEX))
		return false;

	if (!fragShader.compileFile(fragmentFile, SHADER_FRAGMENT))
		return false;

	return link(&vertShader, 0, 0, 0, &fragShader);
}

bool OpenGLShader::compileAndLinkFiles(const char* vertexFile, const char* geomFile, const char* fragmentFile) {
	OpenGLShaderProgram vertShader;
	OpenGLShaderProgram geomShader;
	OpenGLShaderProgram fragShader;

	if (!vertShader.compileFile(vertexFile, SHADER_VERTEX) ||
		!geomShader.compileFile(geomFile, SHADER_GEOMETRY) ||
		!fragShader.compileFile(fragmentFile, SHADER_FRAGMENT)) {
		return false;
	}

	return link(&vertShader, 0, 0, &geomShader, &fragShader);
}

bool OpenGLShader::compileAndLinkTransformFeedbackFiles(const char* vertexFile, const std::vector<const char*>& outputVars, TransformFeedbackOutput output) {
	OpenGLShaderProgram vertShader;

	if (!vertShader.compileFile(vertexFile, SHADER_VERTEX))
		return false;

	return link(&vertShader, 0, 0, 0, outputVars, output);
}

bool OpenGLShader::compileAndLinkTransformFeedbackFiles(const char* vertexFile, const char* geomFile, const std::vector<const char*>& outputVars, TransformFeedbackOutput output) {
	OpenGLShaderProgram vertShader;
	OpenGLShaderProgram geomShader;

	if (!vertShader.compileFile(vertexFile, SHADER_VERTEX))
		return false;
	if (!geomShader.compileFile(geomFile, SHADER_GEOMETRY))
		return false;

	return link(&vertShader, 0, 0, &geomShader, outputVars, output);
}

}
