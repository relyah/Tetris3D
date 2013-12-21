/*
 * Camera.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "Camera.h"

namespace Tetris3D {

Camera::Camera(OpenGLProgram* program) {
	logger = Logger::GetLogger();
	logger->info("Initialising Camera.");
	this->program = program;
	Init();
	logger->info("Initialised Camera.");
}

Camera::~Camera() {
	logger->info("Stopping Camera.");
	program = 0;
	logger->info("Stopped Camera.");}

void Camera::Init() {
	cameraPosition = glm::vec3(10.0, -14.0, 40.0);  // the position of your camera, in world space
	cameraLookAt = glm::vec3(10.0, -14.0, 0.0);  // where you want to look at, in world space
	cameraUp = glm::vec3(0.0, 1.0, 0.0); //up direction; probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
	cameraRight = glm::vec3(1.0, 0.0, 0.0); //required when rotating the camera
	view = glm::lookAt(cameraPosition, cameraLookAt, cameraUp);
}

void Camera::Render()
{
	glUniformMatrix4fv(program->GetUniformView(), 1, GL_FALSE, glm::value_ptr(view));
}

} /* namespace Tetris3D */
