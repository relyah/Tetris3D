/*
 * TetrisEngine.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef TETRISENGINE_H_
#define TETRISENGINE_H_

#include "../Logger.h"
#include "Piece.h"

namespace Tetris3D {

class TetrisEngine {
public:
	TetrisEngine();
	virtual ~TetrisEngine();

	void Run();

	Piece* GetCurrentPiece() {
		return currentPiece;
	}

private:
	log4cpp::Category* logger;
	Piece* currentPiece;

};

} /* namespace Tetris3D */

#endif /* TETRISENGINE_H_ */
