/*
 * InputManager.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "InputManager.h"

Tetris3D::InputManager* Tetris3D::InputManager::manager = 0;

namespace Tetris3D {

InputManager::InputManager() {
	opengl = 0;
	isEscapePressed = false;
}

InputManager::~InputManager() {
opengl = 0;
}

void InputManager::Init(InputManager* manager, OpenGLManager* opengl ) {
	InputManager::manager = manager;

	this->opengl = opengl;

	glfwSetKeyCallback(opengl->GetWindow(), glfw_onKey);
	glfwSetMouseButtonCallback(opengl->GetWindow(), glfw_onMouseButton);
	glfwSetCursorPosCallback(opengl->GetWindow(), glfw_onMouseMove);
	glfwSetScrollCallback(opengl->GetWindow(), glfw_onMouseWheel);
}

void InputManager::PollEvents()
{
	glfwPollEvents();
}

bool InputManager::IsEscapePressed() {
	bool result = isEscapePressed;
	isEscapePressed = false;
	return result;
}

void InputManager::onKey(int key, int action, int mods) {

	isEscapePressed = key == GLFW_KEY_ESCAPE && action == GLFW_PRESS;
}

void InputManager::onMouseButton(int button, int action, int mods) {

}

void InputManager::onMouseMove(double x, double y) {

}

void InputManager::onMouseWheel(double xoffset, double yoffset) {

}

} /* namespace Tetris3D */
