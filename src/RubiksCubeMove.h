#pragma once
#include <glm/glm.hpp>

class VBO;

namespace RubiksCube {

class Move
{
public:
	enum class Type
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

	Move(Type type, const float timeInSec = 0.5f);

	bool drawAtMove(
		float* vertices, VBO &vbo,
		const float deltaTime);
private:
	enum class RotateFace
	{
		FRONT,
		BACK,
		UP,
		DOWN,
		RIGHT,
		LEFT
	};
	static bool rotate(
		float* vertices,
		VBO &vbo,
		RotateFace face,
		bool isClockwise,
		float& currentTime,
		const float timeInSec,
		const float deltaTime);

	const Type m_type;
	const float m_timeInSec;
	float m_currentTime = 0.f;
	
};
}