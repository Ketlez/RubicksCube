#pragma once
#include "GLFW.h"
class VBO
{
public:
	unsigned int vbo;
	VBO()
	{
		glGenBuffers(1, &vbo);
	}
	~VBO()
	{

	}

	void setBuffer(void *pointer, int n_byts)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, n_byts, pointer, GL_STATIC_DRAW);
	}
};