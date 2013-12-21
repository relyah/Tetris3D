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

	input = 0;
	tetrisEngine = 0;
	graphicsEngine = 0;

}

Application::~Application() {
	logger->info("Shuting down Tetris3D.");

	delete input;
	input = 0;
	delete tetrisEngine;
	tetrisEngine = 0;
	delete graphicsEngine;
	graphicsEngine = 0;

	logger->info("Tetris3D End.");
	logger = 0;
}

void Application::Init() {
	logger->info("Initialising Tetris3D.");

	tetrisEngine = new TetrisEngine();

	graphicsEngine = new GraphicsEngine(tetrisEngine);

	input = new InputManager();
	input->Init(input, graphicsEngine->GetManager());

	logger->info("Initialised Tetris3D.");

}

void Application::Run() {
	logger->info("Running Tetris3D");

	bool isRunning = true;

	while (isRunning) {

		input->PollEvents();
		isRunning = !input->IsEscapePressed();
		if (!isRunning) {
			graphicsEngine->Shutdown();
		}
	}

	logger->info("Tetris3D stopped running.");
}

} /* namespace Tetris3D */
