/*
 * TetrisEngine.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef TETRISENGINE_H_
#define TETRISENGINE_H_

#include <time.h>

#include "../Logger.h"
#include "Piece.h"
#include "Well.h"

namespace Tetris3D {

class TetrisEngine {
public:
	TetrisEngine();
	virtual ~TetrisEngine();

	void Run();

	Piece* GetCurrentPiece() {
		return currentPiece;
	}

	Well* GetWell() {
		return well;
	}

	bool IsCurrentPieceMoved() const {
		return isNeedToMove;
	}

	bool IsWellChanged() {
		bool result = isWellChanged;
		isWellChanged = false;
		return result;
	}

private:
	log4cpp::Category* logger;
	Piece* currentPiece;
	Well* well;
	time_t timer;
	bool isNeedToMove;
	bool isWellChanged;
	double moveDelay;
	bool isCanStartMoveDelay;
	bool isDrop;
	bool isGameOver;

	void PickPiece();

};

} /* namespace Tetris3D */

#endif /* TETRISENGINE_H_ */
