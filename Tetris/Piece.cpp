/*
 * Piece.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "Piece.h"

namespace Tetris3D {

Piece::Piece(unsigned int size) {
	this->size = size;
	CreateContainer();
}

Piece::~Piece() {
	for (unsigned int c = 0; c < size; c++) {
		for (unsigned int r = 0; r < size; r++) {
			for (unsigned int d = 0; d < size; d++) {
				Voxel* v = piece[c][r][d];
				if (v != 0) {
					delete v;
					v = 0;
				}
				piece[c][r][d] = 0;
			}
		}
	}
}

void Piece::Set(unsigned int col, unsigned int row, unsigned int dep, bool flag) {
	if (!Validate(col, row, dep))
		return;

	Voxel* v=0;
	if (flag) {
			Voxel* v = new Voxel();

			VoxelColour colour;
			colour.alpha = 1.0;
			colour.red = 0.0;
			colour.green = 0.0;
			colour.blue = 1.0;
			v->SetColour(colour);

			VoxelLocation location;
			location.col = col;
			location.row = row;
			location.dep = dep;
			v->SetLocation(location);

			VoxelDrawPosition position;
			position.x = 0.0;
			position.y = 0.0;
			position.z = 0.0;
			v->SetPosition(position);
	}
	Set(col,row,dep,v);
}

void Piece::Set(unsigned int col, unsigned int row, unsigned int dep, Voxel* voxel) {
	if (!Validate(col, row, dep))
		return;

	Voxel* oldVoxel = piece[col][row][dep];

	if (oldVoxel != 0) {
		delete oldVoxel;
		oldVoxel = 0;
	}
	piece[col][row][dep] = voxel;

}

Voxel* Piece::operator()(const unsigned int col, const unsigned int row, const unsigned int dep) {
	if (!Validate(col, row, dep))
		return 0;
	return piece[col][row][dep];
}

void Piece::CreateContainer() {
	piece = PieceArray(size);
	for (unsigned int c = 0; c < size; c++) {
		piece[c] = RowArray(size);
		for (unsigned int r = 0; r < size; r++) {
			piece[c][r] = DepthArray(size);
			for (unsigned int d = 0; d < size; d++) {
				piece[c][r][d] = 0;
			}
		}
	}
}

bool Piece::Validate(unsigned int position) {
	return position < size;
}

bool Piece::Validate(unsigned int col, unsigned int row, unsigned int dep) {
	return Validate(col) && Validate(row) && Validate(dep);
}

} /* namespace Tetris3D */
