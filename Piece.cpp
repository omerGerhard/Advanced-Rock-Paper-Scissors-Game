/*
 * Piece.cpp
 *
 *  Created on: 22 במרץ 2018
 *      Author: omerg
 */

#include "Player.h"
#include "Parser.h"
#include "Piece.h"


#include "Game.h"

#include "Scissors.h"
#include "Joker.h"
#include "Rock.h"
#include "Bomb.h"
#include "Paper.h"
#include "Flag.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;


Piece204156384::Piece204156384(PieceType _type,Player * _player):type(_type), pos(NULL), captured(true), player(_player) {}

char Piece204156384::formatRepr(char c) const{
	if(player->isLower())
		return tolower(c);
	else
		return toupper(c);
}

FightResult Piece204156384::fight(Piece204156384 *piece){

	if(piece == NULL)
		return FightResult::None;

	if(piece->player == player){
		return FightResult::Invalid;
	}

	bool res1 = isWinning(piece->getDynamicType());
	bool res2 = piece->isWinning(this->getDynamicType());

	if(res1 && !res2){
		piece->kill();
		return FightResult::Win;
	}
	else if(res2 && !res1){
		this->kill();
		return FightResult::Lose;
	}
	else{
		piece->kill();
		this->kill();
		return FightResult::Tie;
	}
}

 Piece204156384* Piece204156384::pieceFactory(Player * player, PieceType type){
	 switch(type){
	 	 case PieceType::ScissorsType:
	 		 return new Scissors(player);
		 case PieceType::JokerType:
			 return new Joker(player);
		 case PieceType::RockType:
			 return new Rock(player);
		 case PieceType::BombType:
			 return new Bomb(player);
		 case PieceType::PaperType:
			 return new Paper(player);
		 case PieceType::FlagType:
			 return new Flag(player);
		 default:
			 return NULL;
	 }
 }

 void Piece204156384::kill(){
	 this->captured = true;
 }

 bool Piece204156384::isCaptured() const{
	 return this->captured;
 }

 PiecePos *Piece204156384::getPos(){
	 return pos;
 }

void Piece204156384::setPos(int row, int col){
	  if(pos == NULL)
		  pos = new PiecePos(row,col);
	  else
		  pos->setPos(row,col);
}

PieceType Piece204156384::charToPieceType(char c){
	c = toupper(c);
	switch(c){
		case 'R':
			return PieceType::RockType;
		case 'P':
			return PieceType::PaperType;
		case 'S':
			return PieceType::ScissorsType;
		case 'B':
			return PieceType::BombType;
		case 'F':
			return PieceType::FlagType;
		case 'J':
			return PieceType::JokerType;
		default:
			return PieceType::NoneType;
	}
}

PieceType Piece204156384::getDynamicType() const{
	return getType();
}

PieceType Piece204156384::getType() const{
	return this->type;
}

bool Piece204156384::isInitLineValid(const vector<string> &line) const{
	if(line.size() != 3)
		return false;
/*	for(int i=0;i<3;i++){
		if(line[i].length() != 1){
			if(i > 0 && line[i].length() == 2)
				continue;
			return false;
		}

	}*/
	return true;
}

int Piece204156384::validIndex(const string &toCheck, int length){
	for(int i=0; i<length; i++){
		if(!('0' <= toCheck[i] && toCheck[i]<='9')){
			return 0;
		}
	}
	return 1;
}


Log Piece204156384::initPosition(Game &game, const vector<string> &line){

	this->captured = false;

	if(!isInitLineValid(line))
		return Log::IllegalFormat;

	if(!validIndex(line[1],line[1].length()) || !validIndex(line[2],line[2].length()))
		return Log::IllegalFormat;

	int row = stoi(line[2])-1, col = stoi(line[1])-1;

	if(!game.isInBoard(row,col)){
	  return Log::OutOfRange;
	}
	if(game.setPiecePosition(row,col,this) == FightResult::Invalid){
	  return Log::PieceCollision;
	}
	return Log::Success;
}


