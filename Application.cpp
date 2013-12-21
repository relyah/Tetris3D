/*
 * Application.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "Application.h"

namespace Tetris3D {

Application::Application() {
	cout << "Starting Tetris3D..." << endl;

	logger = Logger::GetLogger();

	logger->info("Starting Tetris3D.");

	input=0;
	opengl=0;


}

Application::~Application() {
	logger->info("Shuting down Tetris3D.");

	delete input;
	delete opengl;

	logger->info("Tetris3D End.");
	logger = 0;
}

void Application::Init() {
	logger->info("Initialising Tetris3D.");

	opengl = new OpenGLManager();
	opengl->Init(opengl);

	input = new InputManager();
	input->Init(input, opengl);

}

void Application::Run() {
	logger->info("Running Tetris3D");

	bool isRunning = true;

	while (isRunning) {

		opengl->BeginScene(1.0, 1.0, 1.0, 1.0);
		opengl->EndScene();

		input->PollEvents();
		isRunning = !input->IsEscapePressed();
		if (!isRunning) {
			opengl->Shutdown();
		}
	}

}

} /* namespace Tetris3D */
