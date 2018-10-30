GLPP - OpenGL C++ Wrapper Library
======

What is GLPP?
-------------
GLPP is a simple OpenGL wrapper for better type savety and a simple object orientation while using OpenGL in C++ applications.

What is GLPP not?
-----------------
GLPP does not try to complicate thinks more.
It does no state handling or even complex things like a scene graph for you. It just wraps common OpenGL objects into C++ objects and provides functions with the aim to avoid common pitfalls.

What stands GLPP for?
---------------------
Graphics Library++ (as hint for a C++ library)

What C++ standard is required?
------------------------------
GLPP is based on C++98 but works well with newer versions like C++11 and higher.

How to use this library?
-----------------------
GLPP is a header-only library. So no building itself is required, only includes in your project.
But it also comes with some extended features e.g. compiling shader sources with a simple interface.
This implementation is in a .hpp file, supposed to be included in one source file of the project.
See the GLPP.hpp file for this.

For what purpose was this library developed?
--------------------------------------------
It was (and is) developed for usage in my space game project. Most times I use OpenGL functions I have to lookup the documentation to get the right constant for functions like glTexImage2D(). And even so, often i made mistakes with the data types for the internal format and the source format. Here i saw the potential to use a type safe approach like enumerations in C++. Unfortunately C does not have something like this but C++ does. So I started to write a simple class to encapsulate a OpenGL texture and wrote some enums to avoid this pitfall in the future. With the time I was extended as required for vertex buffer objects (VBO's) and shaders.


