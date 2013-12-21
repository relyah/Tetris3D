/*
 * TetrisEngine.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "TetrisEngine.h"

namespace Tetris3D {

TetrisEngine::TetrisEngine() {

	logger = Logger::GetLogger();

	logger->info("Initialised Tetris engine.");

	currentPiece = new Piece(3);
	Voxel* v = new Voxel();
	v->GetColour().alpha = 1.0;
	v->GetColour().blue = 0.0;
	v->GetColour().green = 1.0;
	v->GetColour().red = 0.0;
	v->GetLocation().col = 0;
	v->GetLocation().row = 0;
	v->GetLocation().dep = 0;
	v->GetPosition().x = 0.0;
	v->GetPosition().y = 0.0;
	v->GetPosition().z = 0.0;
	currentPiece->Set(0, 0, 0, v);
}

TetrisEngine::~TetrisEngine() {
	logger->info("Stopped Tetris engine.");
}

void TetrisEngine::Run() {

}

} /* namespace Tetris3D */
