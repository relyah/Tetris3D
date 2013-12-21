/*
 * Piece.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "Piece.h"

namespace Tetris3D {

Piece::Piece(unsigned int size) :
		AbstractPiece(size, size, size) {
	this->size = size;
	isMoved = false;
}

Piece::~Piece() {
}

void Piece::Move(int incCol, int incRow, int incDep) {
	isMoved = true;
	for (unsigned int c = 0; c < size; c++) {
		for (unsigned int r = 0; r < size; r++) {
			for (unsigned int d = 0; d < size; d++) {
				Voxel* v = container[c][r][d];
				if (v != 0) {
					v->Move(incCol, incRow, incDep);
				}
			}
		}
	}
}

unsigned int Piece::GetBottomRow() {
	for (unsigned int row = size - 1; row >= 0; row--) {
		for (unsigned int col = 0; col < size; col++) {
			for (unsigned int dep = 0; dep < size; dep++) {
				if (container[col][row][dep])
					return row;
			}
		}
	}
	return 0;
}
} /* namespace Tetris3D */
