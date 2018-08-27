

#ifndef SCISSORS_H_
#define SCISSORS_H_

#include "Piece.h"

class Scissors : public Piece204156384{

public:

	Scissors(Player * _player) : Piece204156384(PieceType::ScissorsType , _player){};

	bool isWinning(PieceType type) const override;

	char getRepr() const override{
		return this->formatRepr('S');
	}

	bool canMove() const override{
		return true;
	}

};



#endif /* SCIOSSORS_H_ */
