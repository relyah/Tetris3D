/*
 * Application.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

#include "Logger.h"
#include "InputManager.h"
#include "OpenGLManager.h"

using namespace std;

namespace Tetris3D {

class Application {
public:
	Application();
	virtual ~Application();

	void Init();
	void Run();

private:

	log4cpp::Category* logger;

	InputManager* input;
	OpenGLManager* opengl;

};

} /* namespace Tetris3D */

#endif /* APPLICATION_H_ */
