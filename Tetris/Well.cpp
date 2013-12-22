/*
 * Well.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "Well.h"

namespace Tetris3D {

Well::Well(unsigned int col, unsigned int row, unsigned int dep) :
		AbstractPiece(col, row, dep) {
	isAdded = false;
}

Well::~Well() {
}

bool Well::CanMove(Piece* piece, int incCol, int incRow, int incDep) {
	unsigned int pieceBottomRow = piece->GetBottomRow();
	if (pieceBottomRow >= this->row - 1)
		return false;

	int otherSize = piece->GetSize();
	for (int r = pieceBottomRow; r >= 0; r--) {
		for (int c = 0; c < otherSize; c++) {
			for (int d = 0; d < otherSize; d++) {
				Voxel* v = (*piece)(c, r, d);

				if (!v)
					continue;

				VoxelLocation newLocation = v->GetLocation().Move(incCol, incRow, incDep);
				if (newLocation.col >= this->col)
					return false;
				if (newLocation.row >= this->row)
					return false;
				if (newLocation.dep >= this->dep)
					return false;
				if (this->container[newLocation.col][newLocation.row][newLocation.dep])
					return false;

			}
		}
	}
	return true;
}

void Well::Add(Piece* other) {
	int otherSize = other->GetSize();
	for (int c = 0; c < otherSize; c++) {

		for (int r = 0; r < otherSize; r++) {

			for (int d = 0; d < otherSize; d++) {

				Voxel* v = (*other)(c, r, d);

				if (!v)
					continue;

				VoxelLocation l = v->GetLocation();

				this->Set(l.col, l.row, l.dep, true); //make a new voxel
				Voxel* newV = this->container[l.col][l.row][l.dep];
				*newV = *v; //this should make a copy
			}
		}
	}

	RemoveFullPlane();

	isAdded = true;
}

bool Well::CanRotateZCCW(Piece* other) {
	unsigned int size = other->GetSize();
	unsigned int topRow = other->GetTopRow();
	unsigned int leftCol = other->GetLeftCol();

	for (unsigned int d = 0; d < size; d++) {
		for (unsigned int r = 0; r < size; r++) {
			for (unsigned int c = 0; c < size; c++) {
				Voxel* v = (*other)(c, r, d);
				if (v == 0)
					continue;

				VoxelLocation l = v->GetLocation();

				int newRow = size - 1 - c;
				int newCol = r;

				if (!IsThereSpaceHere(leftCol+newCol, topRow+newRow,l.dep))
					return false;

			}
		}
	}
	return true;

}

bool Well::IsThereSpaceHere(int col, int row, int dep) {
	if (!Validate(col, row, dep))
		return false;

	return container[col][row][dep]==0;
}

void Well::RemoveFullPlane() {
	//go through all rows and look for full planes
	for (unsigned int r = 0; r < row; r++) {
		bool isPlaneFull = true;
		for (unsigned int c = 0; c < col && isPlaneFull; c++) {
			for (unsigned int d = 0; d < dep && isPlaneFull; d++) {
				isPlaneFull &= container[c][r][d] != 0;
			}
		}

		if (isPlaneFull) {
//			//remove the full row
//			for (unsigned int c = 0; c < col; c++) {
//				for (unsigned int d = 0; d < dep; d++) {
//					Voxel* v = 0;
//					this->Set(c, r, d, v);
//				}
//			}

			//drop everything above the removed row
			for (unsigned int dropRow = r - 1; dropRow >= 0; dropRow--) {
				for (unsigned int c = 0; c < col; c++) {
					for (unsigned int d = 0; d < dep; d++) {
						container[c][dropRow + 1][d] = container[c][dropRow][d];
						container[c][dropRow][d] = 0;
					}
				}
			}
		}
	}

}

} /* namespace Tetris3D */
