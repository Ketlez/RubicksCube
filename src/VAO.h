#pragma once
#include "GLFW.h"

class VAO
{
    unsigned int vao;
	VAO()
	{
        
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
	}
	~VAO()
	{

	}

    void vaoSwapBu
};