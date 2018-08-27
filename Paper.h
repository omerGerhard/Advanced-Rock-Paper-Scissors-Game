/*
 * Paper.h
 *
 *  Created on: 22 במרץ 2018
 *      Author: omerg
 */

#ifndef PAPER_H_
#define PAPER_H_



#include "Piece.h"


class Paper : public Piece204156384{

public:

	Paper(Player * _player) : Piece204156384(PieceType::PaperType , _player){};

	bool isWinning(PieceType type) const override;

	char getRepr() const override{
		return this->formatRepr('P');
	}

	bool canMove() const override{
		return true;
	}


};



#endif /* PAPER_H_ */
