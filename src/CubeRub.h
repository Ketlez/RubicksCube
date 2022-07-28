#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>
#include "Shader.h"
#include <iostream>

enum class RotateFace
{
	FRONT,
	BACK,
	UP,
	DOWN,
	RIGHT,
	LEFT
};

enum class Move
{
	F,
	R,
	L,
	U,
	D,
	B,
	F_,
	R_,
	L_,
	U_,
	D_,
	B_
};

class CubRub
{	
	float time1 = 0.f;
	float time2 = 5.f;
	float masRotateX[3][3][3]{0};
	float masRotateY[3][3][3]{0};
	float masRotateZ[3][3][3]{0};
	int X, Y, Z;

	bool rotateA(float delTime, Shader shaderProgram, RotateFace face, bool isclockwise)
	{
		float* masXYZ = NULL;
		time1 += delTime;
		bool flag = time1 >= time2;
		//задние грани
		switch (face)
		{
		case RotateFace::FRONT:
			X = -1;
			Y = -1;
			Z = 2;
			masXYZ = &masRotateZ[0][0][0];
			break;
		case RotateFace::BACK:
			X = -1;
			Y = -1;
			Z = 0;
			masXYZ = &masRotateZ[0][0][0];
			break;
		case RotateFace::UP:
			X = -1;
			Y = 2;
			Z = -1;
			masXYZ = &masRotateY[0][0][0];
			break;
		case RotateFace::DOWN:
			X = -1;
			Y = 0;
			Z = -1;
			masXYZ = &masRotateY[0][0][0];
			break;
		case RotateFace::RIGHT:
			X = 2;
			Y = -1;
			Z = -1;
			masXYZ = &masRotateX[0][0][0];
			break;
		case RotateFace::LEFT:
			X = 0;
			Y = -1;
			Z = -1;
			masXYZ = &masRotateX[0][0][0];
			break;

		}
		for (int x = 0; x < 3; x++)
			for (int y = 0; y < 3; y++)
				for (int z = 0; z < 3; z++) {
					glm::mat4 model = glm::mat4(1.0f);
					if (flag && (z == Z || x == X || y == Y))
					{
						masXYZ[x * 9 + y * 3 + z] += (isclockwise ? 1.f : -1.f) * 90.f;
						time1 = 0.f;
					}

					if (z == Z || x == X || y == Y)
					{
						model = glm::rotate(model, (isclockwise ? 1.f : -1.f) * glm::radians(time1 / time2 * 90.f), glm::vec3(X + 1, Y + 1, Z + 1));
					}
					model = glm::translate(model, glm::vec3(x - 1, y - 1, z - 1));
					model = glm::rotate(model, glm::radians(masRotateX[x][y][z]), glm::vec3(1, 0, 0));
					model = glm::rotate(model, glm::radians(masRotateY[x][y][z]), glm::vec3(0, 1, 0));
					model = glm::rotate(model, glm::radians(masRotateZ[x][y][z]), glm::vec3(0, 0, 1));
					shaderProgram.setMatrix("model", model);
					glDrawArrays(GL_TRIANGLES, 0, 36);


				}
		return flag;
	}

public:
	CubRub() {};
	~CubRub() {};
	void Move(float delTime, Shader shaderProgram, Move move)
	{
		bool isclockwise = true;
		RotateFace face;
		switch (move) {
		case Move::F:
			isclockwise = false;
			face = RotateFace::FRONT;
			break;
		case Move::B:
			isclockwise = true;
			face = RotateFace::BACK;
			break;
		case Move::R:
			isclockwise = false;
			face = RotateFace::RIGHT;
			break;
		case Move::L:
			isclockwise = true;
			face = RotateFace::LEFT;
			break;
		case Move::U:
			isclockwise = false;
			face = RotateFace::UP;
			break;
		case Move::D:
			isclockwise = true;
			face = RotateFace::DOWN;
			break;
		case Move::F_:
			isclockwise = true;
			face = RotateFace::FRONT;
			break;
		case Move::B_:
			isclockwise = false;
			face = RotateFace::BACK;
			break;
		case Move::R_:
			isclockwise = true;
			face = RotateFace::RIGHT;
			break;
		case Move::L_:
			isclockwise = false;
			face = RotateFace::LEFT;
			break;
		case Move::U_:
			isclockwise = true;
			face = RotateFace::UP;
			break;
		case Move::D_:
			isclockwise = false;
			face = RotateFace::DOWN;
			break;
		}
		rotateA(delTime, shaderProgram, face, isclockwise);
	}

	
};