#include "RubiksCubeMove.h"

#include <glm/gtc/matrix_transform.hpp>

#include "VBO.h"
#include "Shader.h"
#include <iostream>

RubiksCube::Move::Move(Type type, const float timeInSec)
	: m_type(type),
	m_timeInSec(timeInSec)
{
}



bool RubiksCube::Move::drawAtMove(float* vertices, Shader &shader, VBO &vbo, const float deltaTime)
{
	//отрисовывание статичниго кубика
	if (m_type == Type::IDLE)
		return staticDraw(deltaTime);
	bool isClockwise = true;
	RotateFace face = RotateFace::FRONT;
	switch (m_type) {
	case Type::F:
		isClockwise = false;
		face = RotateFace::FRONT;
		break;
	case Type::B:
		isClockwise = true;
		face = RotateFace::BACK;
		break;
	case Type::R:
		isClockwise = false;
		face = RotateFace::RIGHT;
		break;
	case Type::L:
		isClockwise = true;
		face = RotateFace::LEFT;
		break;
	case Type::U:
		isClockwise = false;
		face = RotateFace::UP;
		break;
	case Type::D:
		isClockwise = true;
		face = RotateFace::DOWN;
		break;
	case Type::F_:
		isClockwise = true;
		face = RotateFace::FRONT;
		break;
	case Type::B_:
		isClockwise = false;
		face = RotateFace::BACK;
		break;
	case Type::R_:
		isClockwise = true;
		face = RotateFace::RIGHT;
		break;
	case Type::L_:
		isClockwise = false;
		face = RotateFace::LEFT;
		break;
	case Type::U_:
		isClockwise = true;
		face = RotateFace::UP;
		break;
	case Type::D_:
		isClockwise = false;
		face = RotateFace::DOWN;
		break;
	}

	return rotate(
		vertices,
		shader,
		vbo,
		face,
		isClockwise,
		m_currentTime,
		m_timeInSec,
		deltaTime);
}

RubiksCube::Move::Type RubiksCube::Move::reverse(Type type)
{
	if ((int)type < 6)
		(int&)type += 6;
	else
		(int&)type -= 6;
	return type;
}

bool RubiksCube::Move::rotate(
	float* vertices,
	Shader &shader,
	VBO &vbo,
	RotateFace face,
	bool isClockwise,
	float& currentTime,
	float timeInSec,
	float deltaTime)
{
	currentTime += deltaTime;
	bool isAnimationOver = currentTime >= timeInSec;
	if (isAnimationOver)
	{
		deltaTime = deltaTime - (currentTime - timeInSec);
		currentTime = timeInSec;
	}

	int X = 0;
	int Y = 0;
	int Z = 0;
	bool rotate = false;
	bool flag = true;
	switch (face)
	{
	case RotateFace::FRONT:
		Z = 3;
		rotate = true;
		break;
	case RotateFace::BACK:
		Z = 3;
		rotate = false;
		break;
	case RotateFace::UP:
		Y = 2;
		rotate = true;
		break;
	case RotateFace::DOWN:
		Y = 2;
		rotate = false;
		break;
	case RotateFace::RIGHT:
		X = 1;
		rotate = true;
		break;
	case RotateFace::LEFT:
		X = 1;
		rotate = false;
		break;
	}

	

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 reverseModel = glm::mat4(1.0f);
	model = glm::rotate(glm::mat4(1.0f), (isClockwise ? 1.f : -1.f) * glm::radians(deltaTime / timeInSec * 90.f), glm::vec3(X, Y, Z));
	reverseModel = glm::rotate(glm::mat4(1.0f), (isClockwise ? -1.f : 1.f) * glm::radians(currentTime / timeInSec * 90.f), glm::vec3(X, Y, Z));
	shader.setMatrix("reverseModel", reverseModel);
	
	for (int i = 0; i < 27; i++) {
		for (int j = 0; j < 36; j++) {
			
			if (rotate - (vertices[i*216 + j*6 + X + Y + Z - 1] > 0.f)) {
				flag = false;
				break;
			}
			
		}
		if(flag)
			for (int j = 0; j < 36; j++) {
				glm::vec4 Vert = model * glm::vec4(vertices[i * 216 + j * 6 + 0], vertices[i * 216 + j * 6 + 1], vertices[i * 216 + j * 6 + 2], 1);
				
				vertices[i * 216 + j * 6 + 0] = Vert.x;
				vertices[i * 216 + j * 6 + 1] = Vert.y;
				vertices[i * 216 + j * 6 + 2] = Vert.z;

				//избовляемся от лишнего доворота т.к. currentTime >= timeInSec
				if (isAnimationOver)
				{
					vertices[i * 216 + j * 6 + 0] = round(vertices[i * 216 + j * 6 + 0] * 10) / 10;
					vertices[i * 216 + j * 6 + 1] = round(vertices[i * 216 + j * 6 + 1] * 10) / 10;
					vertices[i * 216 + j * 6 + 2] = round(vertices[i * 216 + j * 6 + 2] * 10) / 10;
				}
				
			}
		flag = true;
	}

	
	vbo.setData(vertices, sizeof(vertices[0])*5832);
	glDrawArrays(GL_TRIANGLES, 0, 972);

	return isAnimationOver;
}

bool RubiksCube::Move::staticDraw(float deltaTime)
{
	m_currentTime += deltaTime;
	bool isAnimationOver = m_currentTime >= m_timeInSec;
	glDrawArrays(GL_TRIANGLES, 0, 972);

	return isAnimationOver;
}
