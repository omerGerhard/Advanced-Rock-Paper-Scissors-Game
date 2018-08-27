/*
 * Parser.h
 *
 *  Created on: 22 במרץ 2018
 *      Author: omerg
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <iostream>



class Game;
class Player;


enum class Log : int{
	Success,
	IllegalFormat,
	PieceOverflow,
	PieceCollision,
	OutOfRange,
	MissingFlags,
	EndOfFile,
	FileError,
	CapturedFlag,
	CantMove
};

class Parser{

static bool validatePieceChar(char);

static void lineToVector(std::vector<std::string> &tokens, std::string);


public:


	static Log init(Game &game, Player &player, int &lineError);
	static Log move(Game &game, Player &player ,const std::string filename, int &lineError);
	static Log moveLine(Game &game, std::ifstream& file);


};



#endif /* PARSER_H_ */
