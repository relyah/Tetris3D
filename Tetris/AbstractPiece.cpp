/*
 * AbstractPiece.cpp
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#include "AbstractPiece.h"

namespace Tetris3D {

AbstractPiece::AbstractPiece(int col, int row, int dep) {
	this->col = dep;
	this->row = row;
	this->dep = dep;
	CreateContainer();
}

AbstractPiece::~AbstractPiece() {
	for (unsigned int c = 0; c < col; c++) {
		for (unsigned int r = 0; r < row; r++) {
			for (unsigned int d = 0; d < dep; d++) {
				Voxel* v = container[c][r][d];
				if (v != 0) {
					delete v;
					v = 0;
				}
				container[c][r][d] = 0;
			}
		}
	}
}

void AbstractPiece::Set(unsigned int col, unsigned int row, unsigned int dep, bool flag) {
	if (!Validate(col, row, dep))
		return;

	Voxel* v = 0;
	if (flag) {
		v = new Voxel();

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
	Set(col, row, dep, v);
}

void AbstractPiece::Set(unsigned int col, unsigned int row, unsigned int dep, Voxel* voxel) {
	if (!Validate(col, row, dep))
		return;

	Voxel* oldVoxel = container[col][row][dep];

	if (oldVoxel != 0) {
		delete oldVoxel;
		oldVoxel = 0;
	}
	container[col][row][dep] = voxel;

}

Voxel* AbstractPiece::operator()(const unsigned int col, const unsigned int row, const unsigned int dep) {
	if (!Validate(col, row, dep))
		return 0;
	return container[col][row][dep];
}

void AbstractPiece::CreateContainer() {
	container = PieceArray(col);
	for (unsigned int c = 0; c < col; c++) {
		container[c] = RowArray(row);
		for (unsigned int r = 0; r < row; r++) {
			container[c][r] = DepthArray(dep);
			for (unsigned int d = 0; d < dep; d++) {
				container[c][r][d] = 0;
			}
		}
	}
}

int AbstractPiece::GetFirstRow() {
	for (unsigned int r = 0; r < row; r++) {
		for (unsigned int c = 0; c < col; c++) {
			for (unsigned int d = 0; d < dep; d++) {
				if (container[col][row][dep])
					return row;
			}
		}
	}
	return 0;
}

} /* namespace Tetris3D */
