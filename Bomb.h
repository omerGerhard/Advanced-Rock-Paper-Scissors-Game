/*
 * Bomb.h
 *
 *  Created on: 22 במרץ 2018
 *      Author: omerg
 */

#ifndef BOMB_H_
#define BOMB_H_



#include "Piece.h"

class Bomb : public Piece204156384{


public:

	Bomb(Player * _player) : Piece204156384(PieceType::BombType , _player){};

	bool isWinning(PieceType type) const override{
		(void)type;
		return true;
	}

	char getRepr() const override{
		return Piece204156384::formatRepr('B');
	}

	bool canMove() const override{
		return false;
	}

};




#endif /* BOMB_H_ */
