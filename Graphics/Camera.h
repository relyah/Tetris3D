/*
 * Camera.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>	// TODO Auto-generated destructor stub

#include "../Logger.h"
#include "../OpenGL/OpenGLProgram.h"

namespace Tetris3D {

class Camera {
public:
	Camera(OpenGLProgram* program);
	virtual ~Camera();

	void Init();
	void Render();
private:
	log4cpp::Category* logger;

	OpenGLProgram* program;

	glm::mat4 view;
	glm::vec3 cameraPosition;
	glm::vec3 cameraLookAt;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
};

} /* namespace Tetris3D */

#endif /* CAMERA_H_ */
