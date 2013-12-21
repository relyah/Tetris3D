/*
 * AbstractPiece.h
 *
 *  Created on: 21 Dec 2013
 *      Author: bert
 */

#ifndef ABSTRACTPIECE_H_
#define ABSTRACTPIECE_H_

#include <vector>

#include "TetrisCommon.h"
#include "Voxel.h"

namespace Tetris3D {

typedef std::vector<Voxel*> DepthArray;
typedef std::vector<DepthArray> RowArray;
typedef std::vector<RowArray> PieceArray;

class AbstractPiece {
public:
	AbstractPiece(int col, int row, int dep);
	virtual ~AbstractPiece();

	void Set(unsigned int col, unsigned int row, unsigned int dep, bool flag);
	void Set(unsigned int col, unsigned int row, unsigned int dep, Voxel* voxel);

	Voxel* operator()(const unsigned int col, const unsigned int row, const unsigned int dep);

	int GetFirstRow();

	virtual bool IsChanged()=0;

	unsigned int GetCol() const {
		return col;
	}

	unsigned int GetDep() const {
		return dep;
	}

	unsigned int GetRow() const {
		return row;
	}

protected:
	PieceArray container;
	unsigned int col;
	unsigned int row;
	unsigned int dep;

	virtual void CreateContainer();
	virtual bool Validate(unsigned int _col, unsigned int _row, unsigned int _dep) {
		return Validate(col, _col) && Validate(row, _row) && Validate(dep, _dep);
	}

private:

	bool Validate(unsigned int max, unsigned int position) {
		return position < max;
	}

};

} /* namespace Tetris3D */

#endif /* ABSTRACTPIECE_H_ */
