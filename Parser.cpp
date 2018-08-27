

#include "Game.h"

#include "Piece.h"
#include "Player.h"
#include "Parser.h"

#include "Joker.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


Log Parser::init(Game &game, Player &player, int &lineError)
{
  ifstream fin(player.getPositionFile());

  string line;
  Log log = Log::Success;
  int countFlags=0;

  int currentLine = 1;
  if(fin.is_open()){
	  while(!fin.eof()){

		getline(fin, line);
		if(line == "")
			continue;

		vector<string> tokens;
		lineToVector(tokens , line);

		if(tokens[0].length() != 1){
			  log = Log::IllegalFormat;
			  break;
		}

		char pieceChar = tokens[0][0];

		if(!validatePieceChar(pieceChar)){
		  log = Log::IllegalFormat;
		  break;
		}

		Piece204156384 *piece = NULL;
		for(int i=0; i<NUM_OF_PIECES;i++){
		  if(pieceChar == toupper(player.pieces[i]->getRepr()) && player.pieces[i]->getPos() == NULL){
			  piece = player.pieces[i];
			  countFlags += piece->getDynamicType() == PieceType::FlagType;
			  break;
		  }
		}

		if(piece == NULL){
		  log = Log::PieceOverflow;
		  break;
		}

		log = game.setPieceInitialPosition(piece , tokens);

		if(log != Log::Success){
		  break;
		}

		currentLine++;

		}

		if(log == Log::Success && countFlags < FLAGS){
		  log = Log::MissingFlags;
		}

		if(log == Log::Success){
		  lineError = -1;
		}
		else{
		  lineError = currentLine;
		}

		if(fin)
		  fin.close();

	}
	else{
	  log = Log::FileError;
	}

  return log;
}



Log Parser::moveLine(Game &game, ifstream& file)
{
	string line;
	if(file.eof()){
		return Log::EndOfFile;
	}

	getline(file,line);
	while(line == ""){
		getline(file,line);
		if(file.eof())
			return Log::EndOfFile;
	}

	vector<string> tokens;
	lineToVector(tokens , line);

	if((int)tokens.size() != 8 && (int)tokens.size() != 4){
		return Log::IllegalFormat;
	}
	for(int i=0; i<4; i++){
		if(!Piece204156384::validIndex(tokens[i],tokens[i].length()))
			return Log::IllegalFormat;
	}

	int srcCol = stoi(tokens[0])-1 , srcRow = stoi(tokens[1])-1, tarCol = stoi(tokens[2])-1, tarRow = stoi(tokens[3])-1;

	if(!game.isInBoard(srcRow,srcCol) || !game.isInBoard(tarRow,tarCol))
		return Log::IllegalFormat;

	Piece204156384* piece = game.getBoardContent(srcRow,srcCol);
	if(piece == NULL)
	  return Log::IllegalFormat;

	//case of change in joker reprsentation
	if((int)tokens.size() == 8){
		if(tokens[4].length() != 2 || tokens[4][0] != 'J' || tokens[4][1] != ':' || tokens[7].length() != 1){
			return Log::IllegalFormat;
		}

		for(int i=5; i<7; i++){
			if(!Piece204156384::validIndex(tokens[i],tokens[i].length()))
				return Log::IllegalFormat;
		}

		int jokerSrcCol = stoi(tokens[5])-1;
		int jokerSrcRow = stoi(tokens[6])-1;
		if(!game.isInBoard(jokerSrcRow,jokerSrcCol))
			return Log::IllegalFormat;

		char changeChar = tokens[7][0];
		if(!validatePieceChar(changeChar)){
			return Log::IllegalFormat;
		}

		return game.makeTurn(game, piece, tarRow, tarCol, jokerSrcRow, jokerSrcCol, Piece204156384::charToPieceType(changeChar), true);
	}

	else{
		return game.makeTurn(game, piece, tarRow, tarCol, 0, 0 , PieceType::NoneType, false);
	}


}


bool Parser::validatePieceChar(char pieceChar){
	return Piece204156384::charToPieceType(pieceChar) != PieceType::NoneType;
}

void Parser::lineToVector(std::vector<std::string> &tokens, string line){
	istringstream iss(line);

	while(1){
		string sub;
		iss >> sub;
		if(sub == "")
			break;
		tokens.push_back(sub);
	}
}

