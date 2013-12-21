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

using namespace std;

namespace Tetris3D {

class Application {
public:
	Application();
	virtual ~Application();

	void Run();

private:
	void Init();

	log4cpp::Category* root;
};

} /* namespace Tetris3D */

#endif /* APPLICATION_H_ */
