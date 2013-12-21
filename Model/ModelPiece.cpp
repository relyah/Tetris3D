#include "ModelPiece.h"

namespace Tetris3D {

ModelPiece::ModelPiece(OpenGLProgram* program) {
	logger = Logger::GetLogger();

	logger->info("Initialising model piece.");

	sideLength = 2.0;
	piece = 0;
	vbo = -1;
	ibo = -1;
	isWireFrame = false;

	this->program = program;

	this->attribute_coord3d = program->GetAttributeCoord3d();
	this->attribute_colour = program->GetAttributeColour();
	this->attribute_normal =  program->GetAttributeNormal();
	this->uniform_model =  program->GetUniformModel();

	logger->info("Initialised model piece.");

}

ModelPiece::~ModelPiece() {
	piece = 0;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void ModelPiece::Render() {

	GenerateBuffers();

	if (isWireFrame) {
		// Turn on wireframe mode
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}

	glEnableVertexAttribArray(attribute_coord3d);
	glEnableVertexAttribArray(attribute_normal);
	glEnableVertexAttribArray(attribute_colour);

	translate = glm::mat4(1.0f);
	glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(translate));

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glVertexAttribPointer(attribute_coord3d, 3, GL_FLOAT, GL_FALSE, sizeof(struct VertexStructure),  // stride
	0);  // offset

	glVertexAttribPointer(attribute_normal, 3,
	GL_FLOAT,
	GL_FALSE, sizeof(struct VertexStructure),  // stride
	(GLvoid*) offsetof(struct VertexStructure, normal));

	glVertexAttribPointer(attribute_colour, 3,
	GL_FLOAT,
	GL_FALSE, sizeof(struct VertexStructure),  // stride
	(GLvoid*) offsetof(struct VertexStructure, colour));

	/* Push each element in buffer_vertices to the vertex shader */

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	int size = 0;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (isWireFrame) {
		// Turn off wireframe mode
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}
}

void ModelPiece::Convert(std::vector<float> &cs, std::vector<unsigned short> &el) {
	cs.clear();
	el.clear();

	int size = piece->GetSize();

	int numElements = 24;
	int cubeNum = 0;

	for (int c = 0; c < size; c++) {

		for (int r = 0; r < size; r++) {
			for (int d = 0; d < size; d++) {
				Voxel* v = (*piece)(c, r, d);
				if (v == 0)
					continue;

				float f_bl[3] = { (float) (c * sideLength), (float) (-(r + 1) * sideLength), d * sideLength };
				float f_br[3] = { f_bl[0] + sideLength, f_bl[1], f_bl[2] };
				float f_tl[3] = { f_bl[0], f_bl[1] + sideLength, f_bl[2] };
				float f_tr[3] = { f_br[0], f_tl[1], f_bl[2] };
				float b_tl[3] = { f_tl[0], f_tl[1], f_bl[2] + sideLength };
				float b_tr[3] = { f_tr[0], f_tr[1], b_tl[2] };
				float b_bl[3] = { f_bl[0], f_bl[1], b_tl[2] };
				float b_br[3] = { f_tr[0], f_bl[1], b_tl[2] };

				//front
				VoxelColour colour = v->GetColour();
				PushIntoVector(cs, f_bl, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { colour.red, colour.green, colour.blue,
						colour.alpha });
				PushIntoVector(cs, f_br, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { colour.red, colour.green, colour.blue,
						colour.alpha });
				PushIntoVector(cs, f_tr, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { colour.red, colour.green, colour.blue,
						colour.alpha });
				PushIntoVector(cs, f_tl, new float[3] { 0.0, 0.0, -1.0 }, new float[4] { colour.red, colour.green, colour.blue,
						colour.alpha });

				//top
				PushIntoVector(cs, f_tl, new float[3] { 0.0, 1.0, 0.0 }, new float[4] { 0.1, 0.8, 0.0, 1.0 });
				PushIntoVector(cs, f_tr, new float[3] { 0.0, 1.0, 0.0 }, new float[4] { 0.1, 0.8, 0.0, 1.0 });
				PushIntoVector(cs, b_tr, new float[3] { 0.0, 1.0, 0.0 }, new float[4] { 0.1, 0.8, 0.0, 1.0 });
				PushIntoVector(cs, b_tl, new float[3] { 0.0, 1.0, 0.0 }, new float[4] { 0.1, 0.8, 0.0, 1.0 });

				//back
				PushIntoVector(cs, b_br, new float[3] { 0.0, 0.0, 1.0 }, new float[4] { 1.0, 0.0, 0.0, 1.0 });
				PushIntoVector(cs, b_bl, new float[3] { 0.0, 0.0, 1.0 }, new float[4] { 1.0, 0.0, 0.0, 1.0 });
				PushIntoVector(cs, b_tl, new float[3] { 0.0, 0.0, 1.0 }, new float[4] { 1.0, 0.0, 0.0, 1.0 });
				PushIntoVector(cs, b_tr, new float[3] { 0.0, 0.0, 1.0 }, new float[4] { 1.0, 0.0, 0.0, 1.0 });

				//bottom
				PushIntoVector(cs, b_bl, new float[3] { 0.0, -1.0, 0.0 }, new float[4] { 0.0, 0.5, 0.5, 1.0 });
				PushIntoVector(cs, b_br, new float[3] { 0.0, -1.0, 0.0 }, new float[4] { 0.0, 0.5, 0.5, 1.0 });
				PushIntoVector(cs, f_br, new float[3] { 0.0, -1.0, 0.0 }, new float[4] { 0.0, 0.5, 0.5, 1.0 });
				PushIntoVector(cs, f_bl, new float[3] { 0.0, -1.0, 0.0 }, new float[4] { 0.0, 0.5, 0.5, 1.0 });

				//left
				PushIntoVector(cs, b_bl, new float[3] { -1.0, 0.0, 0.0 }, new float[4] { 0.5, 0.5, 0.0, 1.0 });
				PushIntoVector(cs, f_bl, new float[3] { -1.0, 0.0, 0.0 }, new float[4] { 0.5, 0.5, 0.0, 1.0 });
				PushIntoVector(cs, f_tl, new float[3] { -1.0, 0.0, 0.0 }, new float[4] { 0.5, 0.5, 0.0, 1.0 });
				PushIntoVector(cs, b_tl, new float[3] { -1.0, 0.0, 0.0 }, new float[4] { 0.5, 0.5, 0.0, 1.0 });

				//right
				PushIntoVector(cs, f_br, new float[3] { 1.0, 0.0, 0.0 }, new float[4] { 1.0, 0.2, 0.4, 1.0 });
				PushIntoVector(cs, b_br, new float[3] { 1.0, 0.0, 0.0 }, new float[4] { 1.0, 0.2, 0.4, 1.0 });
				PushIntoVector(cs, b_tr, new float[3] { 1.0, 0.0, 0.0 }, new float[4] { 1.0, 0.2, 0.4, 1.0 });
				PushIntoVector(cs, f_tr, new float[3] { 1.0, 0.0, 0.0 }, new float[4] { 1.0, 0.2, 0.4, 1.0 });

				MakeElements(el, numElements, cubeNum);

				cubeNum++; //increment the cube counter;

			}

		}
	}

}

void ModelPiece::PushIntoVector(std::vector<float> &cs, float* coord, float *normal, float* colour) {
	cs.push_back(coord[0]);
	cs.push_back(coord[1]);
	cs.push_back(coord[2]);

	cs.push_back(normal[0]);
	cs.push_back(normal[1]);
	cs.push_back(normal[2]);

	cs.push_back(colour[0]);
	cs.push_back(colour[1]);
	cs.push_back(colour[2]);
}

void ModelPiece::MakeElements(std::vector<unsigned short> &el, int numElements, int cubeNum) {

	int offset = numElements * cubeNum;
//front
	el.push_back(0 + offset);
	el.push_back(1 + offset);
	el.push_back(2 + offset);
	el.push_back(2 + offset);
	el.push_back(3 + offset);
	el.push_back(0 + offset);
//top
	el.push_back(4 + offset);
	el.push_back(5 + offset);
	el.push_back(6 + offset);
	el.push_back(6 + offset);
	el.push_back(7 + offset);
	el.push_back(4 + offset);
//back
	el.push_back(8 + offset);
	el.push_back(9 + offset);
	el.push_back(10 + offset);
	el.push_back(10 + offset);
	el.push_back(11 + offset);
	el.push_back(8 + offset);
//bottom
	el.push_back(12 + offset);
	el.push_back(13 + offset);
	el.push_back(14 + offset);
	el.push_back(14 + offset);
	el.push_back(15 + offset);
	el.push_back(12 + offset);
//left
	el.push_back(16 + offset);
	el.push_back(17 + offset);
	el.push_back(18 + offset);
	el.push_back(18 + offset);
	el.push_back(19 + offset);
	el.push_back(16 + offset);
//rightunsigned
	el.push_back(20 + offset);
	el.push_back(21 + offset);
	el.push_back(22 + offset);
	el.push_back(22 + offset);
	el.push_back(23 + offset);
	el.push_back(20 + offset);

}

void ModelPiece::GenerateBuffers() {
	std::vector<float> cs;
	std::vector<unsigned short> el;
	Convert(cs, el);

	GenerateArrayBuffer(cs);
	GenerateElementBuffer(el);
}

void ModelPiece::GenerateArrayBuffer(std::vector<float>& vertices) {
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelPiece::GenerateElementBuffer(std::vector<unsigned short>& elements) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &ibo);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned short), &elements[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} /* namespace Tetris3D */
