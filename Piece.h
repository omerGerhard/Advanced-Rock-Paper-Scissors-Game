/*
 * Piece.h
 *
 *  Created on: 22 במרץ 2018
 *      Author: omerg
 */

#ifndef PIECE_H_
#define PIECE_H_

#include "PiecePos.h"
#include <string>
#include <vector>

using namespace std;

class Player;
class Game;
class Parser;

enum class Log : int;

enum class PieceType : int{
  	JokerType,
  	BombType,
  	RockType,
  	PaperType,
  	ScissorsType,
  	FlagType,
  	NoneType
  };



enum class FightResult : int{
	Win,
	Lose,
	Tie,
	None,
	Invalid
};



class Piece204156384
{
public:


protected:

  PieceType type;

  PiecePos* pos;

  bool captured;

  void kill();


public:

  Player *player;

  Piece204156384(PieceType _type,Player * _player);

  virtual ~Piece204156384() {
	  if(pos != NULL)
		  delete pos;
  };

  virtual bool isWinning(PieceType) const = 0;

  virtual char getRepr() const = 0;

  virtual bool canMove() const = 0;

  bool isCaptured() const;

  void setPos(int x, int y);

  PiecePos *getPos();

  virtual Log initPosition(Game &game, const vector<string>& line);

  FightResult fight(Piece204156384 *);

  virtual PieceType getDynamicType() const;

  PieceType getType() const;

  static Piece204156384* pieceFactory(Player * player, PieceType type);

  static PieceType charToPieceType(char);

  virtual bool isInitLineValid(const vector<string> &line) const;

  bool isMoveLineValid(string line) const;

  char formatRepr(char c) const;

  static int validIndex(const string &toCheck, int length);

};



#endif /* PIECE_H_ */
