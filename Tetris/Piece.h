/*
 * Piece.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef PIECE_H_
#define PIECE_H_

#include "AbstractPiece.h"

namespace Tetris3D {

class Piece : public AbstractPiece {
public:
	Piece(unsigned int size);
	virtual ~Piece();

	void Move(int incCol, int incRow, int incDep);
	unsigned int GetBottomRow();

	unsigned int GetSize() const {
		return size;
	}

	bool IsMoved() {
		bool result = isMoved;
		isMoved = false;
		return result;
	}

	virtual bool IsChanged() {return IsMoved();}

private:
	unsigned int size;
	bool isMoved;

	bool Validate(unsigned int position);
};

} /* namespace Tetris3D */

#endif /* PIECE_H_ */
