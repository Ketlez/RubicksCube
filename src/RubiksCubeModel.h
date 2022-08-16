#pragma once

#include <queue>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

#include "RubiksCubeMove.h"
#include <array>
#include <tuple>
struct Color
{
	unsigned char R;
	unsigned char G;
	unsigned char B;

	std::tuple<float, float, float> toFloat();
};
namespace RubiksCube {
class ColorScheme
{
	Color front;
	Color up;
	Color back;
	Color down;
	Color right;
	Color left;

public:
	ColorScheme(Color front,
		Color up,
		Color back,
		Color down,
		Color right,
		Color left
	);

	std::array<float, 5832> createArray() const;
	std::array<float, 5832> createArrayFromOneCube(const std::array<float, 216>& oneCubeVertices) const;
	std::array<Color, 6> asArray() const;

	static ColorScheme Classic;
};



class Model
{
public:
	Model(const ColorScheme& colorSceme);
	~Model();
	std::array<float, 5832> vertices;
	void pushMove(const Move& move);
	bool hasMoves() const;
	void draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 model, const float deltaTime);
	void shuffleAndSolve(const size_t nMoves, const float shuffleMoveSpedInSec, const float idleTimeInSec, const float solveMoveSpedInSec);
private:
	void drawStatic();
	std::queue<Move> m_moves;
	Shader m_shader;
	VAO m_vao;
	VBO m_vbo;
	
	
};
}