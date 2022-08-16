#include "RubiksCubeModel.h"
#include <vector>
using namespace RubiksCube;
RubiksCube::Model::Model(const ColorScheme& colorSceme)
	: m_shader("FvertexShader.txt", "FfragmentShader.txt")
{
	vertices = colorSceme.createArray();
	m_vao.bind();
	m_vbo.bind();
	m_vbo.setData(vertices.data(), sizeof(float)*vertices.size());
	m_vao.attribPointer(0, 3, GL_FLOAT, 6 * sizeof(float), 0);
	m_vao.attribPointer(1, 3, GL_FLOAT, 6 * sizeof(float), 3 * sizeof(float));
}

RubiksCube::Model::~Model()
{
}

void RubiksCube::Model::pushMove(const Move& move)
{
	m_moves.push(move);
}

bool RubiksCube::Model::hasMoves() const
{
	return !m_moves.empty();
}

void RubiksCube::Model::draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 model, const float deltaTime)
{
	m_shader.use();
	m_vao.bind();

	m_shader.setMatrix("view", viewMatrix);
	m_shader.setMatrix("projection", projectionMatrix);
	m_shader.setMatrix("model", model);


	if (m_moves.empty()) {
		drawStatic();
		return;
	}
	
	if (m_moves.front().drawAtMove(vertices.data(), m_shader, m_vbo, deltaTime))
		m_moves.pop();
}

void RubiksCube::Model::shuffleAndSolve(const size_t nMoves, const float shuffleMoveSpedInSec, const float idleTimeInSec, const float solveMoveSpedInSec)
{
	std::srand(time(0));
	std::vector<RubiksCube::Move::Type> creatMove(nMoves);

	for (int i = 0; i < nMoves; i++)
	{
		int randomRotate = rand() % 12;
		while(i!=0 && creatMove[i - 1] == Move::reverse((Move::Type)randomRotate))
			randomRotate = rand() % 12;
		creatMove[i] = (RubiksCube::Move::Type)randomRotate;
		pushMove(RubiksCube::Move((RubiksCube::Move::Type)randomRotate, shuffleMoveSpedInSec));
	}
	pushMove(RubiksCube::Move(RubiksCube::Move::Type::IDLE, idleTimeInSec));

	for (int i = nMoves -1; i >= 0; i--)
	{
		pushMove(RubiksCube::Move(Move::reverse(creatMove[i]), solveMoveSpedInSec));
	}

}

void RubiksCube::Model::drawStatic()
{
	
	glDrawArrays(GL_TRIANGLES, 0, 972);
}

RubiksCube::ColorScheme::ColorScheme(Color front, Color up, Color back, Color down, Color right, Color left)
	:front(front), up(up), back(back), down(down), right(right), left(left)
{
	
}


std::array<float, 5832> RubiksCube::ColorScheme::createArray() const
{
	std::array<float, 216> verticesOneCube = {
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,

	   -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

		0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
	};

	std::array<Color, 6> colorsArray = asArray();

	for (int i = 0; i < 6; i++)
	{
		auto [R, G, B] = colorsArray[i].toFloat();
		for (int j = 0; j < 6; j++)
		{
			verticesOneCube[i * 36 + j*6 + 3] = R;
			verticesOneCube[i * 36 + j*6 + 4] = G;
			verticesOneCube[i * 36 + j*6 + 5] = B;
		}
	}

	return createArrayFromOneCube(verticesOneCube);
}

std::array<float, 5832> RubiksCube::ColorScheme::createArrayFromOneCube(const std::array<float, 216>& oneCubeVertices) const
{
	std::array<float, 5832> resultCube;
	int c = 0;
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			for (int z = 0; z < 3; z++) {
				for (int i = 0; i < 36; i++)
				{

					resultCube[c++] = oneCubeVertices[i * 6 + 0] + (x - 1);
					resultCube[c++] = oneCubeVertices[i * 6 + 1] + (y - 1);
					resultCube[c++] = oneCubeVertices[i * 6 + 2] + (z - 1);

					for (int k = 0; k < 3; k++)
					{

						resultCube[c++] = oneCubeVertices[i * 6 + 3 + k];
					}
				}
			}
		}
	}
	return resultCube;
}

std::array<Color, 6> RubiksCube::ColorScheme::asArray() const
{
	std::array<Color, 6> asArray;
	asArray[0] = back;
	asArray[1] = down;
	asArray[2] = front;
	asArray[3] = left;
	asArray[4] = right;
	asArray[5] = up;
	return asArray;
}

RubiksCube::ColorScheme RubiksCube::ColorScheme::Classic(
	Color{ 255, 0, 0 },
	Color{ 255, 255, 255 },
	Color{ 255, 130, 0 },
	Color{ 253, 233, 16 },
	Color{ 0, 57, 110 },
	Color{ 40, 140, 51 }
	);

std::tuple<float, float, float> Color::toFloat()
{
	return std::make_tuple(R/255.f, G/255.f, B/255.f);
}
