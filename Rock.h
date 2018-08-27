
#ifndef ROCK_H_
#define ROCK_H_



#include "Piece.h"


class Rock : public Piece204156384{

public:

	Rock(Player * _player) : Piece204156384(PieceType::RockType , _player){};

	bool isWinning(PieceType type) const override;

	char getRepr() const override{
		return this->formatRepr('R');
	}

	bool canMove() const override{
		return true;
	}


};

#endif /* ROCK_H_ */
