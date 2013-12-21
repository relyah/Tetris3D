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
	isUpPressed = false;
	isDownPressed = false;
	isLeftPressed = false;
	isRightPressed = false;

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
	return ToggleKey(isEscapePressed);
}

bool InputManager::IsLeftPressed() {
	return ToggleKey(isLeftPressed);
}
bool InputManager::IsRightPressed() {
	return ToggleKey(isRightPressed);
}
bool InputManager::IsUpPressed() {
	return ToggleKey(isUpPressed);
}
bool InputManager::IsDownPressed() {
	return ToggleKey(isDownPressed);
}

bool InputManager::ToggleKey(bool& flag) {
	bool result = flag;
	flag = false;
	return result;
}

void InputManager::onKey(int key, int action, int mods) {

	std::stringstream sstm;
	sstm << "Key: " << key << " Action:" << action;

	logger->debug(sstm.str());

	isEscapePressed = key == GLFW_KEY_ESCAPE && action == GLFW_PRESS;

	isUpPressed = key == GLFW_KEY_UP && action == GLFW_PRESS;
	isDownPressed = key == GLFW_KEY_DOWN && action == GLFW_PRESS;
	isLeftPressed = key == GLFW_KEY_LEFT && action == GLFW_PRESS;
	isRightPressed = key == GLFW_KEY_RIGHT && action == GLFW_PRESS;
}

void InputManager::onMouseButton(int button, int action, int mods) {

}

void InputManager::onMouseMove(double x, double y) {

}

void InputManager::onMouseWheel(double xoffset, double yoffset) {

}

} /* namespace Tetris3D */
