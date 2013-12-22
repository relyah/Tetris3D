/*
 * ModelGrid.cpp
 *
 *  Created on: 22 Dec 2013
 *      Author: bert
 */

#include "ModelGrid.h"

namespace Tetris3D {

ModelGrid::ModelGrid(OpenGLProgram* program) :
		AbstractModelPiece(program) {
	well = 0;
	vbo = -1;
}

ModelGrid::~ModelGrid() {
	program = 0;
	well = 0;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo);
}

void ModelGrid::GenerateBuffers() {

	std::vector<float> grid;
	MakeGrid(grid);
	GenerateArrayBuffer(vbo, grid);
}

void ModelGrid::InitBuffers() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	AbstractModelPiece::InitBuffers();
}

void ModelGrid::DrawBuffers() {
	int size = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawArrays(GL_LINES, 0, size / sizeof(VertexStructure));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelGrid::MakeGrid(std::vector<float> &cs) {
	cs.clear();

	unsigned int maxCol = well->GetCol();
	unsigned int maxRow = well->GetRow();
	unsigned int maxDep = well->GetDep();

	float z = -sideLength * maxDep;

	for (unsigned int row = 0; row <= maxRow; row++) {

		float xStart = 0.0;
		float y = -(float) (row * sideLength);

		float xEnd = (float) (maxCol * sideLength);

		float start[3] = { xStart, y, z };
		float end[3] = { xEnd, y, z };

		PushIntoVector(cs, start, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0, 0.0, 1.0 });
		PushIntoVector(cs, end, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 1.0, 0.0, 1.0 });

	}

	for (unsigned int col = 0; col <= maxCol; col++) {

		float yStart = 0.0;
		float x = (float) (col * sideLength);

		float yEnd = -(float) (maxRow * sideLength);

		float start[3] = { x, yStart, z };
		float end[3] = { x, yEnd, z };

		PushIntoVector(cs, start, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 0.0, 1.0, 1.0 });
		PushIntoVector(cs, end, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { 1.0, 0.0, 1.0, 1.0 });

	}

}

} /* namespace Tetris3D */
