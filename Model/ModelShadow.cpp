/*
 * ModelShadow.cpp
 *
 *  Created on: 22 Dec 2013
 *      Author: bert
 */

#include "ModelShadow.h"

namespace Tetris3D {

ModelShadow::ModelShadow(OpenGLProgram* program) :
		AbstractModelPiece(program) {
	logger->info("Initialising model shadow.");

	piece = 0;
	well = 0;
	vbo = -1;
	ibo = -1;
	isWireFrame = false;

	logger->info("Initialised model sgadow.");
}

ModelShadow::~ModelShadow() {
	piece = 0;
	well = 0;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void ModelShadow::GenerateBuffers() {
	std::vector<float> cs;
	std::vector<unsigned short> el;
	//Convert(cs, el);

	GenerateArrayBuffer(vbo, cs);
	GenerateElementBuffer(ibo, el);
}

void ModelShadow::InitBuffers() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	AbstractModelPiece::InitBuffers();
}

void ModelShadow::DrawBuffers() {
	int size = 0;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} /* namespace Tetris3D */
