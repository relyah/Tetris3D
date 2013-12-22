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
	isMoved = true;
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

void Piece::RotateZCCW() {
	isMoved = true;
	unsigned int n = size;
	unsigned int colLimit = floor((float) n / 2.0);
	unsigned int rowLimit = ceil((float) n / 2.0);

	unsigned int topRow = GetTopRow();
	unsigned int leftCol = GetLeftCol();
	unsigned int topDep = GetTopDep();

	for (unsigned int d = 0; d < size; d++) {
		for (unsigned int c = 0; c < colLimit; c++) {
			for (unsigned int r = 0; r < rowLimit; r++) {

				Voxel* temp = container[c][r][d];
				if (temp != 0)
				{
					temp = temp->Copy();
				}

				SwapVoxels(leftCol, topRow, topDep, c, r, d, container[n - 1 - r][c][d]); //	container[c][r][d] = container[n - 1 - r][c][d];

				SwapVoxels(leftCol, topRow, topDep, n - 1 - r, c, d, container[n - 1 - c][n - 1 - r][d]); //container[n - 1 - r][c][d] = container[n - 1 - c][n - 1 - r][d];

				SwapVoxels(leftCol, topRow, topDep, n - 1 - c, n - 1 - r, d, container[r][n - 1 - c][d]); // container[n - 1 - c][n - 1 - r][d] = container[r][n - 1 - c][d];

				SwapVoxels(leftCol, topRow, topDep, r, n - 1 - c, d, temp); //container[r][n - 1 - c][d] = temp;

			}
		}
	}
}

void Piece::SwapVoxels(unsigned int leftCol, unsigned int topRow, unsigned int topDep, unsigned int c1, unsigned int r1,
		unsigned int d1, Voxel* src) {

	Voxel* dest = container[c1][r1][d1];
	if (src == 0) {
		if (dest != 0) {
			delete container[c1][r1][d1];
		}
		container[c1][r1][d1] = 0;
		return;
	}

	if (dest == 0) {
		Voxel* v = new Voxel();
		v->GetLocation().col = leftCol + c1;
		v->GetLocation().row = topRow + r1;
		v->GetLocation().dep = topDep + d1;
		container[c1][r1][d1] = v;
		dest = container[c1][r1][d1];
	}

	dest->GetColour().red = src->GetColour().red;
	dest->GetColour().blue = src->GetColour().blue;
	dest->GetColour().green = src->GetColour().green;
	dest->GetColour().alpha = src->GetColour().alpha;

}

unsigned int Piece::GetLeftCol() {

	for (unsigned int col = 0; col < size; col++) {
		for (unsigned int row = 0; row < size; row++) {
			for (unsigned int dep = 0; dep < size; dep++) {
				if (container[col][row][dep])
					return container[col][row][dep]->GetLocation().col;
			}
		}
	}
	return 0;
}

unsigned int Piece::GetTopRow() {
	for (unsigned int row = 0; row < size; row++) {
		for (unsigned int col = 0; col < size; col++) {
			for (unsigned int dep = 0; dep < size; dep++) {
				if (container[col][row][dep])
					return container[col][row][dep]->GetLocation().row;
			}
		}
	}
	return 0;
}

unsigned int Piece::GetBottomRow() {
	for (unsigned int row = size - 1; row >= 0; row--) {
		for (unsigned int col = 0; col < size; col++) {
			for (unsigned int dep = 0; dep < size; dep++) {
				if (container[col][row][dep])
					return container[col][row][dep]->GetLocation().row;
			}
		}
	}
	return 0;
}

unsigned int Piece::GetTopDep() {
	for (unsigned int dep = 0; dep < size; dep++) {
		for (unsigned int row = 0; row < size; row++) {
			for (unsigned int col = 0; col < size; col++) {
				if (container[col][row][dep])
					return container[col][row][dep]->GetLocation().dep;
			}
		}
	}
	return 0;
}

} /* namespace Tetris3D */
