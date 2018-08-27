/*
 * Joker.h
 *
 *  Created on: 22 במרץ 2018
 *      Author: omerg
 */

#ifndef JOKER_H_
#define JOKER_H_




#include <string>
#include "Piece.h"


class Joker : public Piece204156384{

public:

	Piece204156384 *dynamicPiece;

	Joker(Player * _player) :Piece204156384(PieceType::JokerType , _player), dynamicPiece(NULL) {};

	~Joker(){
		delete dynamicPiece;
	}

	bool isWinning(PieceType type) const override{
		return dynamicPiece->isWinning(type);
	}

	char getRepr() const override{
		return this->formatRepr('J');
	}

	bool canMove() const override{
		return dynamicPiece->canMove();
	}

	PieceType getDynamicType() const override;

	bool changeType(PieceType type);

	Log initPosition(Game &game, const std::vector<std::string>& line) override;

	bool isInitLineValid(const std::vector<std::string> &line) const override;


};




#endif /* JOKER_H_ */
