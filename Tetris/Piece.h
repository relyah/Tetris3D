/*
 * Piece.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef PIECE_H_
#define PIECE_H_

#include <vector>

#include "TetrisCommon.h"
#include "Voxel.h"

namespace Tetris3D {

typedef std::vector<Voxel*> DepthArray;
typedef std::vector<DepthArray> RowArray;
typedef std::vector<RowArray> PieceArray;

class Piece {
public:
	Piece(unsigned int size);
	virtual ~Piece();

	void Set(unsigned int col,unsigned  int row, unsigned int dep, bool flag);
	void Set(unsigned int col, unsigned int row, unsigned int dep, Voxel* voxel);

  Voxel* operator() (const unsigned int col, const unsigned int row, const unsigned int dep);

  int GetSize() const {return size;}

private:
	unsigned int size;
	PieceArray piece;

	void CreateContainer();
	bool Validate(unsigned int position);
	bool Validate(unsigned int col, unsigned int row, unsigned int dep);
};

} /* namespace Tetris3D */

#endif /* PIECE_H_ */
