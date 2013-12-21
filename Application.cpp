/*
 * Application.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "Application.h"

namespace Tetris3D {

Application::Application() {
	cout << "Initialising Tetris3D..." << endl;

	std::string initFileName = "log4cpp.properties";
	log4cpp::PropertyConfigurator::configure(initFileName);
	root = &(log4cpp::Category::getRoot());

	root->info("Initialising Tetris3D");

}

Application::~Application() {
	root->info("Tetris3D End.");
	root = 0;
}

void Application::Init() {
}

void Application::Run() {
	root->info("Running Tetris3D");
}

} /* namespace Tetris3D */
