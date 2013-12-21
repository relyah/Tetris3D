/*
 * VoxelModel.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef MODELPIECE_H_
#define MODELPIECE_H_

#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library

#define GLM_MESSAGES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	// TODO Auto-generated destructor stub

#include "../Tetris/Piece.h"
#include "../OpenGL/OpenGLProgram.h"
#include "../Logger.h"

namespace Tetris3D {

struct VertexStructure {
	float coord3d[3];
	float normal[3];
	float colour[4];
};

class ModelPiece {
public:
	ModelPiece(OpenGLProgram* program);
	virtual ~ModelPiece();

	void Render();

	Piece& GetPiece() {
		return *piece;
	}

	void SetPiece(Piece* piece) {
		this->piece = piece;
	}

	void SetIsWireFrame(bool isWireFrame) {
		this->isWireFrame = isWireFrame;
	}

private:
	OpenGLProgram* program;
	Piece* piece;
	float sideLength;
	bool isWireFrame;
	glm::mat4 translate;
	GLuint vbo; //vertex buffer object
	GLuint ibo; //index buffer object
	GLint attribute_coord3d, attribute_colour, attribute_normal;
	GLint uniform_model;
	log4cpp::Category* logger;

	void Convert(std::vector<float> &cs, std::vector<unsigned short> &el);
	void MakeElements(std::vector<unsigned short> &el, int numElements, int cubeNum);
	void PushIntoVector(std::vector<float> &cs, float* coord, float *normal, float* colour);
	void GenerateBuffers();
	void GenerateArrayBuffer(std::vector<float>& vertices);
	void GenerateElementBuffer(std::vector<unsigned short>& elements);
};

} /* namespace Tetris3D */

#endif /* MODELPIECE_H_ */
