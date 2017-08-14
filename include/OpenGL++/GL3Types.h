#pragma once

#ifdef USE_GLEW
#include <GL/glew.h>
#elif USE_GL3W
#include <GL/gl3w.h>
#else
#error "No OpenGL3 function loader selected"
#endif
