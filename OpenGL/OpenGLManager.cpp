/*
 * OpenGLManager.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "OpenGLManager.h"

Tetris3D::OpenGLManager* Tetris3D::OpenGLManager::manager = 0;

namespace Tetris3D {

OpenGLManager::OpenGLManager(int screenWidth, int screenHeight) {

	logger = Logger::GetLogger();
	window = 0;
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
}

OpenGLManager::~OpenGLManager() {
	logger->info("Stopping down OpenGL.");
	glfwDestroyWindow(window);
	glfwTerminate();
	logger->info("Stopped OpenGL.");
	logger = 0;
	window = 0;
}

void OpenGLManager::Shutdown()
{
	logger->info("Open GL manager shutdown requested.");
	glfwSetWindowShouldClose(window, 1);
}

void OpenGLManager::Init(OpenGLManager* manager) {
	logger->info("Initialising OpenGL.");

	OpenGLManager::manager = manager;

	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	window = glfwCreateWindow(screenWidth, screenHeight, "Tetris 3D", NULL,
	NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(glfw_error_callback);
	glfwSetWindowSizeCallback(window, glfw_onResize);
	glfwMakeContextCurrent(window);
	glewInit();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDebugMessageCallbackARB(gl_debug_callback, this);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);

	//Controlling the volume of debug output.
	GLuint unusedIds = 0;
	//glDebugMessageControlARB(enum source, enum type, enum severity, sizei count, const uint* ids, boolean enabled).
	glDebugMessageControlARB(GL_DONT_CARE,
	GL_DONT_CARE,
	GL_DONT_CARE, 0, &unusedIds, true);

	logger->info("Initialised OpenGL.");

}

void OpenGLManager::BeginScene(float r, float g, float b, float a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLManager::EndScene() {
	glfwSwapBuffers(window);
}

void OpenGLManager::OnWindowResize(GLFWwindow* window, int width, int height) {
	screenWidth = width;
	screenHeight = height;
	glViewport(0, 0, screenWidth, screenHeight);
}

void OpenGLManager::OnError(int error, const char* description) {
	std::stringstream sstm;
	sstm << "Error: " << error << " " << description;
	logger->error(sstm.str());
}

void OpenGLManager::onDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
		const GLchar* message) {
	std::stringstream sstm;
	sstm << "source: " << source << " Type " << type << " ID: " << id << " Severity: " << severity << " Length: "
			<< length << " Message: " << message;
	logger->error(sstm.str());
}

} /* namespace Tetris3D */
