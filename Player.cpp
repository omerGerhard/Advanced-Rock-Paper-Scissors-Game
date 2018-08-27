/*
 * Player.cpp
 *
 *  Created on: 22 במרץ 2018
 *      Author: omerg
 */


#include "Player.h"
#include "Piece.h"
#include "Parser.h"


Player::Player(PlayerType _type) : score(0), status(Log::Success),moveFileStream(NULL),type(_type){

	if(_type == player1){
		lower = false;
		positionFile = "player1.rps_board";
		moveFile = "player1.rps_moves";
	}
	else{
		lower = true;
		positionFile = "player2.rps_board";
		moveFile = "player2.rps_moves";
	}

	int index = 0, count = 0;
	for(count=0;count<ROCKS;count++){
		pieces[index+count] = Piece204156384::pieceFactory(this, PieceType::RockType);
	}
	index += count;
	for(count=0;count<PAPERS;count++){
		pieces[index+count] = Piece204156384::pieceFactory(this, PieceType::PaperType);
	}
	index += count;
	for(count=0;count<SCISSORS;count++){
		pieces[index+count] = Piece204156384::pieceFactory(this, PieceType::ScissorsType);
	}
	index += count;
	for(count=0;count<FLAGS;count++){
		pieces[index+count] = Piece204156384::pieceFactory(this, PieceType::FlagType);
	}
	index += count;
	for(count=0;count<BOMBS;count++){
		pieces[index+count] = Piece204156384::pieceFactory(this, PieceType::BombType);
	}
	index += count;
	for(count=0;count<JOKERS;count++){
		pieces[index+count] = Piece204156384::pieceFactory(this, PieceType::JokerType);
	}

}

Player::~Player(){
	for(int i=0; i<NUM_OF_PIECES; i++){
		delete pieces[i];
	}

	if(moveFileStream)
		moveFileStream->close();

	delete moveFileStream;
}

PlayerType Player::getType() const{
	return type;
}

bool Player::isLower() const{
	return lower;
}

void Player::addPoint(){
	score++;
}

const Player::Status& Player::getStatus(){
	return status;
}


void Player::setStatus(Log log, int lineError){
	this->status = Status(log, lineError);
}

const string& Player::getPositionFile(){
	return positionFile;
}

ifstream* Player::getMoveFileStream(){
	if(moveFileStream == NULL){
		moveFileStream = new ifstream(moveFile);
		if(!moveFileStream->is_open())
			return NULL;
	}
	return moveFileStream;
}

bool Player::canMove(){
	int movingPieces = 0;
	for(int i=0; i<NUM_OF_PIECES;i++){
		movingPieces += !this->pieces[i]->isCaptured() && this->pieces[i]->canMove();
	}
	return movingPieces>0;
}

bool Player::hasFlags(){
	int capturedFlags = 0;
	for(int i=0; i<NUM_OF_PIECES;i++){
		if(this->pieces[i]->getType() == PieceType::FlagType){
			capturedFlags += this->pieces[i]->isCaptured();
		}
	}
	return capturedFlags < FLAGS;
}

string Player::toString(){
	return (type == player1) ? "player 1" : "player 2";
}
