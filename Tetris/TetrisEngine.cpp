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

	isGameOver = false;
	isCanStartMoveDelay = true;
	moveDelay = 0.0;

	struct tm y2k;
	y2k.tm_hour = 0;
	y2k.tm_min = 0;
	y2k.tm_sec = 0;
	y2k.tm_year = 100;
	y2k.tm_mon = 0;
	y2k.tm_mday = 1;
	timer = mktime(&y2k);

	well = new Well(10, 14, 5);

	currentPiece = 0;
	PickPiece();

}

TetrisEngine::~TetrisEngine() {
	logger->info("Stopping Tetris engine.");
	delete currentPiece;
	currentPiece=0;
	delete well;
	well=0;
	logger->info("Stopped Tetris engine.");
}

void TetrisEngine::Run() {

	if (isGameOver)
		return;

	time_t now;

	time(&now);

	double seconds = 0.0;
	seconds = difftime(now, timer);

	isNeedToMove = seconds >= 2.0;

	if (!isCanStartMoveDelay) {
		moveDelay += seconds;
	}

	if (isNeedToMove) {
		std::ostringstream strs;
		strs << "Need to move. Elapsed time:" << seconds << "(sec)";

		logger->debug(strs.str());

		if (isCanStartMoveDelay && well->CanMove(currentPiece, 0, 1, 0)) {
			logger->debug("Piece moved.");

			currentPiece->Move(0, 1, 0);

		} else if (isCanStartMoveDelay && !isDrop) {
			logger->debug("Entering move delay.");

			isCanStartMoveDelay = false;
			moveDelay = 0;
		} else if (isDrop || moveDelay > 2.0) {
			logger->debug("Fixing piece.");

			moveDelay = 0;
			isCanStartMoveDelay = true;
			isDrop = false;
			isWellChanged = true;

			well->Add(currentPiece);

			PickPiece();

			if (well->CanMove(currentPiece)) {
				isGameOver = false;
			} else {
				isGameOver = true;
			}
		}

		timer = now;

	}
}

void TetrisEngine::PickPiece() {
	if (currentPiece != 0) {
		logger->debug("Deleting previous piece.");
		delete currentPiece;
		currentPiece = 0;
	}

	logger->debug("Making new piece.");

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

} /* namespace Tetris3D */
