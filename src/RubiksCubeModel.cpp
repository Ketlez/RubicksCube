#include "RubiksCubeModel.h"

RubiksCube::Model::Model()
	: m_shader("FvertexShader.txt", "FfragmentShader.txt")
{

	m_vao.bind();
	m_vbo.bind();
	m_vbo.setData(vertices, sizeof(vertices));
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
	//m_shader.setMatrix("model", model);


	if (m_moves.empty()) {
		drawStatic();
		return;
	}
	
	if (m_moves.front().drawAtMove(&vertices[0], m_shader, m_vbo, deltaTime))
		m_moves.pop();
}

void RubiksCube::Model::drawStatic()
{
	
	glDrawArrays(GL_TRIANGLES, 0, 972);
}
