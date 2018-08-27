

#include "Game.h"
#include "Player.h"
#include "Piece.h"
#include "Parser.h"

#include "Joker.h"

#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#define OUTPUT_FILE "rps.output"

Game::Game() : turn(0),numOfTurns(-1){

	this->players[0] = new Player(player1);
	this->players[1] = new Player(player2);

	for(int i=0; i<COLS;i++){
		for(int j=0; j<ROWS;j++){
			board[i][j] = NULL;
		}
	}
}


Game::~Game(){
	  delete players[0];
	  delete players[1];
}

Piece204156384 *Game::getBoardContent(int row,int col){
	if(!isInBoard(row,col)){
		return NULL;
	}
	return board[row][col];
}

void Game::runGame(){
	positioning();

	if(this->players[this->turn]->getStatus().log == Log::Success && !this->players[this->turn]->hasFlags())
		this->players[this->turn]->setStatus(Log::CapturedFlag);

	else if(this->players[this->turn]->getStatus().log == Log::Success && !this->players[this->turn]->canMove())
		this->players[this->turn]->setStatus(Log::CantMove);

	if(this->players[getOpponent(this->turn)]->getStatus().log == Log::Success && !this->players[getOpponent(this->turn)]->hasFlags())
		this->players[getOpponent(this->turn)]->setStatus(Log::CapturedFlag);

	while(!isGameOver()){
		numOfTurns++;
		ifstream *f = players[this->turn]->getMoveFileStream();
		if(f == NULL){
			players[this->turn]->setStatus(Log::FileError,(numOfTurns/2)+1);
			continue;
		}
		Log log = Parser::moveLine(*this,*f);
		players[this->turn]->setStatus(log,(numOfTurns/2)+1);
		changeTurn();
	}


	Player *winner = calculateWinner();

	if (winner)
		winner->addPoint();

	consoleErrorMessage(*players[0]);
	consoleErrorMessage(*players[1]);

	if(players[0]->getStatus().log != Log::FileError && players[1]->getStatus().log != Log::FileError )
		createOutputFile(winner);
}

void Game::positioning(){
	int lineError1 = -1, lineError2 = -1;
	Log log1, log2;
	log1 = Parser::init(*(this), *(this->players[0]), lineError1);
	log2 = Parser::init(*(this), *(this->players[1]), lineError2);
	players[0]->setStatus(log1,lineError1);
	players[1]->setStatus(log2,lineError2);
}

bool Game::isGameOver() const{
	Log log1 = players[0]->getStatus().log;
	Log log2 = players[1]->getStatus().log;

	if(!isSuccess(log1) || !isSuccess(log2))
		return true;

	else if(log1 == Log::EndOfFile && log2 == Log::EndOfFile)
		return true;
	return false;
}

void Game::consoleErrorMessage(Player &player){
	Player::Status status = player.getStatus();
	switch(status.log){
		case Log::MissingFlags:
			printf("Flags are missing for %s\n",player.toString().c_str());
			break;
		case Log::IllegalFormat:
			printf("Illegal file format for %s in line %d\n",player.toString().c_str(), status.lineError);
			break;
		case Log::OutOfRange:
			printf("Piece position by %s out of legal range in line %d\n",player.toString().c_str(), status.lineError);
			break;
		case Log::PieceCollision:
			printf("Piece position by %s in line %d collides with another piece of its own\n",player.toString().c_str(), status.lineError);
			break;
		case Log::PieceOverflow:
			printf("%s positioned too many pieces of same type, in line %d\n",player.toString().c_str(), status.lineError);
			break;
		case Log::FileError:
			if(numOfTurns == -1)
				printf("Can't open positioning file of %s\n",player.toString().c_str());
			else
				printf("Can't open moves file of %s\n",player.toString().c_str());
			break;
		default:
			break;
	}
}

void Game::createOutputFile(const Player* winner){
	ofstream outfile(OUTPUT_FILE);

	if(!outfile){
		cout << "Error: Can't open output file." << endl;
		return;
	}

	int winnerUI = 0;
	if(winner){
		winnerUI = getPlayerIndex(winner)+1;
	}
	outfile << "Winner: " << winnerUI << endl;
	outfile << "Reason: ";

	if(numOfTurns == -1){

		if(winner == NULL){
			if(players[0]->getStatus().log == Log::CapturedFlag && players[1]->getStatus().log == Log::CapturedFlag){
				outfile << "A tie - all flags are eaten by both players in the position files";
			}
			else
				outfile << "Bad Positioning input file for both players - " << players[0]->toString() << ": line " <<players[0]->getStatus().lineError << ", " << players[1]->toString() << ": line " << players[1]->getStatus().lineError;
		}

		else{
			Player *loser = players[getOpponent(getPlayerIndex(winner))];
			if(loser->getStatus().log == Log::CapturedFlag)
				outfile << "All flags of the opponent are captured";
			else if(winnerUI==2 && (players[0]->getStatus().log == Log::CantMove))
				outfile << "All moving PIECEs of the opponent are eaten" ;
			else
				outfile << "Bad Positioning input file for " << loser->toString() << " - line " << loser->getStatus().lineError << endl;
		}
	}

	else{
		if (winner == NULL){
			if(players[0]->getStatus().log == Log::CapturedFlag && players[0]->getStatus().log == Log::CapturedFlag && players[0]->getStatus().log == Log::CapturedFlag && players[1]->getStatus().log == Log::CapturedFlag){
				outfile << "A tie - all flags are eaten by both players in the position files" << endl;
			}
			else if(players[0]->getStatus().log == Log::EndOfFile && players[0]->getStatus().log == Log::EndOfFile && players[0]->getStatus().log == Log::EndOfFile && players[1]->getStatus().log == Log::EndOfFile){
				outfile << "A tie - both Moves input files done without a winner" << endl;
			}
		}
		else{
			Player *loser = players[getOpponent(getPlayerIndex(winner))];
			Player::Status status = loser->getStatus();
			switch(status.log){
				case Log::CantMove:
					outfile << "All moving PIECEs of the opponent are eaten" << endl;
					break;
				case Log::CapturedFlag:
					outfile << "All flags of the opponent are captured" << endl;
					break;
				default:
					outfile << "Bad Moves input file for " << loser->toString() << " - line " << status.lineError << endl;
			}
		}
	}

	outfile << endl;

	printBoard(outfile);

	outfile.close();

}

void Game::printBoard(ofstream &outfile){
	for(int row=0; row<ROWS; row++){
		for(int col=0; col<COLS; col++){
			Piece204156384 * piece = getBoardContent(row,col);
			if(piece){
				outfile << piece->getRepr();
			}
			else{
				outfile << " ";
			}
		}
		outfile << endl;
	}
}

Player *Game::calculateWinner() const{
	Log log1 = this->players[0]->getStatus().log;
	Log log2 = this->players[1]->getStatus().log;

	if(isSuccess(log1) && !isSuccess(log2)){
		return players[0];
	}
	else if(!isSuccess(log1) && isSuccess(log2)){
		return players[1];
	}
	else if(log1 == Log::EndOfFile && log2 == Log::EndOfFile){
		return NULL;
	}
	else if(!isSuccess(log1) && !isSuccess(log2)){
		return NULL;
	}
	return NULL;

}

bool Game::isSuccess(Log log){
	return log == Log::EndOfFile || log == Log::Success;
}

int Game::getPlayerIndex(const Player *player) const{
	if(player->getType() == player1)
		return 0;
	return 1;
}

void Game::changeTurn(){
	turn = getOpponent(this->turn);
}

int Game::getOpponent(int playerIndex) const{
	return (playerIndex+1)%2;
}

/*
 * pre condition - piece->getPos()==NULL || piece.canMove()==true
 */
FightResult Game::setPiecePosition(int row,int col, Piece204156384 *piece){

	if(piece->getPos())
		board[piece->getPos()->getX()][piece->getPos()->getY()] = NULL;

	piece->setPos(row,col);

	Piece204156384 *opponent = getBoardContent(row,col);

	FightResult res = piece->fight(opponent);

	if(res == FightResult::Invalid){
		return res;
	}

	Piece204156384 *winner = NULL;
	if(res == FightResult::Win || res == FightResult::None)
		winner = piece;
	if(res == FightResult::Lose)
		winner = opponent;
	if(res == FightResult::Tie)
		winner = NULL;

	board[row][col] = winner;

	return res;
}

Log Game::setPieceInitialPosition(Piece204156384 *piece, vector<string> &line){
	return piece->initPosition(*this,line);
}


Log Game::makeTurn(Game &game, Piece204156384 *piece, int row, int col, int jokerRow, int jokerCol, PieceType changeTo, bool withJoker){

	if(piece->player->getType() != game.players[turn]->getType())
		return Log::IllegalFormat;

	if(!piece->canMove())
		return Log::IllegalFormat;

	if(!isOneStepMove(row, col, piece))
		return Log::IllegalFormat;

	FightResult res = setPiecePosition(row,col,piece);
	if(res == FightResult::Invalid){
		return Log::IllegalFormat;
	}

	if(!this->players[getOpponent(this->turn)]->canMove()){
		this->players[getOpponent(this->turn)]->setStatus(Log::CantMove);
	}

	else if(!this->players[getOpponent(this->turn)]->hasFlags()){
		this->players[getOpponent(this->turn)]->setStatus(Log::CapturedFlag);
	}

	if(!this->players[this->turn]->canMove()){
		if(!withJoker)
			return Log::CantMove;
		else
			this->players[(this->turn)]->setStatus(Log::CantMove);
	}

	if(withJoker){
		Piece204156384 *joker = game.getBoardContent(jokerRow,jokerCol);
		if(joker == NULL || joker->getType() != PieceType::JokerType){
			return Log::IllegalFormat;
		}
		else{
			Joker* isJoker = dynamic_cast<Joker*>(joker);
			if(!isJoker->changeType(changeTo)){
				return Log::IllegalFormat;
			}
		}
		if(changeTo == PieceType::BombType && this->players[(this->turn)]->getStatus().log == Log::CantMove)
			return Log::CantMove;
	}

	return Log::Success;
}



bool Game::isOneStepMove(int tarRow, int tarCol, Piece204156384 *piece){
	if(!isInBoard(tarRow,tarCol))
		return false;
	int rowDiff = abs(piece->getPos()->getX() - tarRow);
	int colDiff = abs(piece->getPos()->getY() - tarCol);
	if((rowDiff == 1 && colDiff == 0) || (rowDiff == 0 && colDiff == 1))
		return true;
	return false;
}

bool Game::isInBoard(int row, int col){
	return (row >= 0 && row < COLS && col >= 0 && col < ROWS);
}




