#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include "glsl.h"

GLuint myGLSLProgram;


std::ifstream t("FragmentShader.txt"), t2("VertexShader.txt");
std::string fragmentFile((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
std::string vertexFile((std::istreambuf_iterator<char>(t2)),std::istreambuf_iterator<char>());


void checkCompiled(GLuint shader) 
{
	GLfloat compiled = 0;
	glGetObjectParameterfvARB(shader, GL_COMPILE_STATUS, &compiled);
	if(!compiled) {
		GLint blen = 500;	
		GLsizei slen = 0;
		GLchar* compiler_log = (GLchar*)malloc(blen);
		
		glGetInfoLogARB(shader, blen, &slen, compiler_log);
		std::cout << "compiler_log:\n" << compiler_log << std::endl;
		free (compiler_log);
		int i;
		std::cin >> i;
		exit(1);
	}
}

void initGLSL() 
{
	//GLSL: creazione dello shader custom
	GLuint vertexShaderObject, fragmentShaderObject;
	vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	// we need these to properly pass the strings
    const char *source;
    int length;

    // create and compiler vertex shader
    source = vertexFile.c_str();
    length = vertexFile.size();


	glShaderSourceARB(vertexShaderObject, 1, &source, &length);
	glCompileShaderARB(vertexShaderObject);
	source = fragmentFile.c_str();
    length = fragmentFile.size();
	glShaderSourceARB(fragmentShaderObject, 1, &source, &length);
	glCompileShaderARB(fragmentShaderObject);
	
	checkCompiled(vertexShaderObject);
	checkCompiled(fragmentShaderObject);

    myGLSLProgram = glCreateProgram();
	glAttachShader(myGLSLProgram, vertexShaderObject);
	glAttachShader(myGLSLProgram, fragmentShaderObject);
	glLinkProgram(myGLSLProgram);

	//controllo errori linking
	GLint linked;
	glGetProgramiv(myGLSLProgram, GL_LINK_STATUS, &linked);
	if (!linked)
	{
	   exit(1);
	}    
}
