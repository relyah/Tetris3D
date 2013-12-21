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

	logger = Logger::GetLogger();
}

InputManager::~InputManager() {
	logger->info("Input manager shutting down.");
	opengl = 0;
	logger = 0;
}

void InputManager::Init(InputManager* manager, OpenGLManager* opengl) {
	logger->info("Initialising input manager.");
	InputManager::manager = manager;

	this->opengl = opengl;

	glfwSetKeyCallback(opengl->GetWindow(), glfw_onKey);
	glfwSetMouseButtonCallback(opengl->GetWindow(), glfw_onMouseButton);
	glfwSetCursorPosCallback(opengl->GetWindow(), glfw_onMouseMove);
	glfwSetScrollCallback(opengl->GetWindow(), glfw_onMouseWheel);

	logger->info("Initialised input manager.");
}

void InputManager::PollEvents() {
	glfwPollEvents();
}

bool InputManager::IsEscapePressed() {
	bool result = isEscapePressed;
	isEscapePressed = false;
	return result;
}

void InputManager::onKey(int key, int action, int mods) {

	std::stringstream sstm;
	sstm << "Key: " << key << " Action:" << action;

	logger->debug(sstm.str());
	isEscapePressed = key == GLFW_KEY_ESCAPE && action == GLFW_PRESS;
}

void InputManager::onMouseButton(int button, int action, int mods) {

}

void InputManager::onMouseMove(double x, double y) {

}

void InputManager::onMouseWheel(double xoffset, double yoffset) {

}

} /* namespace Tetris3D */
