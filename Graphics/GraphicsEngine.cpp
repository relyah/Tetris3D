/*
 * GraphicsEngine.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "GraphicsEngine.h"

namespace Tetris3D {

GraphicsEngine::GraphicsEngine(TetrisEngine* tetrisEngine) {
	logger = Logger::GetLogger();

	screenWidth = 640;
	screenHeight = 480;
	this->tetrisEngine = tetrisEngine;
	Init();

}

GraphicsEngine::~GraphicsEngine() {
	logger->info("Stopping Graphics engine.");

	delete piece;
	piece = 0;
	delete camera;
	camera = 0;
	delete program;
	program = 0;
	delete manager;
	manager = 0;

	tetrisEngine = 0;

	logger->info("Stopped Graphics engine.");

}

void GraphicsEngine::Init() {
	logger->info("Initialising Graphics engine.");

	manager = new OpenGLManager(screenWidth, screenHeight);
	manager->Init(manager);

	program = new OpenGLProgram();

	camera = new Camera(program);

	piece = new ModelPiece(program);

	logger->info("Initialised Graphics engine.");

}

void GraphicsEngine::Render() {
	manager->BeginScene(1.0, 1.0, 1.0, 1.0);

	glm::mat4 projection = glm::perspective(45.0f, 1.0f * screenWidth / screenHeight, 0.1f, 100.0f);
	glUniformMatrix4fv(program->GetUniformProjection(), 1, GL_FALSE, glm::value_ptr(projection));

	camera->Render();

	piece->SetPiece(tetrisEngine->GetCurrentPiece());
	piece->Render();

	manager->EndScene();
}

void GraphicsEngine::Shutdown() {
	logger->info("Shutting down Graphics engine.");

	manager->Shutdown();

	logger->info("Shutdown Graphics engine.");
}

} /* namespace Tetris3D */
