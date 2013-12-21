/*
 * Well.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef WELL_H_
#define WELL_H_

#include "AbstractPiece.h"
#include "Piece.h"

namespace Tetris3D {

class Well: public AbstractPiece {
public:
	Well(unsigned int col, unsigned int row, unsigned int dep);
	virtual ~Well();

	bool CanMove(Piece* piece, int incCol = 0, int incRow = 0, int incDep = 0);
	void Add(Piece* piece);

	bool IsAdded() {
		bool result = isAdded;
		isAdded = false;
		return result;
	}

	virtual bool IsChanged() {return IsAdded();}

private:
	bool isAdded;

	void RemoveFullPlane();

};

} /* namespace Tetris3D */

#endif /* WELL_H_ */
