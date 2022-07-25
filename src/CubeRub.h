#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>
#include "Shader.h"
#include <iostream>


class CubRub
{	
	float masRotateX[3][3][3]{0};
	float masRotateY[3][3][3]{0};
	float masRotateZ[3][3][3]{0};
public:
	CubRub() {};
	~CubRub() {};
	glm::mat4 rotateA(glm::mat4 model, float time, Shader shaderProgram)
	{
		for (int z = 0; z < 2; z++)
			for (int y = 0; y < 3; y++)
				for (int x = 0; x < 3; x++) {
					glm::mat4 model = glm::mat4(1.0f);
					
					model = glm::translate(model, glm::vec3(x-1, y-1, z-1));
					model = glm::rotate(model, masRotateX[x][y][z], glm::vec3(1, 0, 0));
					model = glm::rotate(model, masRotateY[x][y][z], glm::vec3(0, 1, 0));
					model = glm::rotate(model, masRotateZ[x][y][z], glm::vec3(0, 0, 1));
					shaderProgram.setMatrix("model", model);
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
		for(int y=0; y<3; y++)
			for (int x = 0; x < 3; x++) {
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::rotate(model, time, glm::vec3(0, 0, 1));
			

				
				model = glm::translate(model, glm::vec3(x-1, y-1, 1));
				model = glm::rotate(model, masRotateX[x][y][2], glm::vec3(1, 0, 0));
				model = glm::rotate(model, masRotateY[x][y][2], glm::vec3(0, 1, 0));
				model = glm::rotate(model, masRotateZ[x][y][2], glm::vec3(0, 0, 1));
				
				shaderProgram.setMatrix("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
				
				masRotateZ[x][y][2] = time;
			
			}
		

		return model;
	}
	glm::mat4 rotateB(glm::mat4 model, float time, Shader shaderProgram)
	{
		for (int y = 0; y < 2; y++)
			for (int z = 0; z < 3; z++)
				for (int x = 0; x < 3; x++) {
					glm::mat4 model = glm::mat4(1.0f);
					
					
					model = glm::translate(model, glm::vec3(x-1, y-1, z-1));
					model = glm::rotate(model, masRotateX[x][y][z], glm::vec3(1, 0, 0));
					model = glm::rotate(model, masRotateY[x][y][z], glm::vec3(0, 1, 0));
					model = glm::rotate(model, masRotateZ[x][y][z], glm::vec3(0, 0, 1));
					shaderProgram.setMatrix("model", model);
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
		for (int z = 0; z < 3; z++)
			for (int x = 0; x < 3; x++) {
				glm::mat4 model = glm::mat4(1.0f);

				model = glm::rotate(model, time, glm::vec3(0, 1, 0));


				
				
				model = glm::translate(model, glm::vec3(x-1, 1, z-1));

				model = glm::rotate(model, masRotateX[x][2][z], glm::vec3(1, 0, 0));
				model = glm::rotate(model, masRotateY[x][2][z], glm::vec3(0, 1, 0));
				model = glm::rotate(model, masRotateZ[x][2][z], glm::vec3(0, 0, 1));
				shaderProgram.setMatrix("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				
				masRotateY[x][2][z] = time;
				
			}
		
		return model;
	}

	glm::mat4 newMasRotate(glm::mat4 model)
	{
		for (int y = 0; y < 3; y++)
			for (int z = 0; z < 3; z++)
				for (int x = 0; x < 3; x++) {
					model = glm::rotate(model, masRotateX[x][y][z], glm::vec3(1, 0, 0));
					model = glm::rotate(model, masRotateY[x][y][z], glm::vec3(0, 1, 0));
					model = glm::rotate(model, masRotateZ[x][y][z], glm::vec3(0, 0, 1));
				}
		return model;
	}
};