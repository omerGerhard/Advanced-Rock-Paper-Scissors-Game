

#ifndef GAME_H_
#define GAME_H_


#include <iostream>
#include <string>
#include <vector>


class Joker;
class Parser;
class Player;
class Piece204156384;
enum class FightResult : int;
enum class Log : int;
enum class PieceType : int;

#define ROWS 10
#define COLS 10


class Game
{
	int turn;
	int numOfTurns;
	Player *players[2];
	Piece204156384* board[ROWS][COLS];

	void changeTurn();

	int getPlayerIndex(const Player *player) const;

	int getOpponent(int) const;

	void positioning();

	bool isGameOver() const;

	void createOutputFile(const Player* winner);

	Player *calculateWinner() const;

	void printBoard(std::ofstream&);

	static bool isSuccess(Log);

	bool isOneStepMove(int x, int y, Piece204156384 *piece);

public:

	Game();
	~Game();

	void runGame();

	FightResult setPiecePosition(int x,int y, Piece204156384 *piece);

	Log setPieceInitialPosition(Piece204156384 *piece, std::vector<std::string> &line);

	Log makeTurn(Game &game, Piece204156384 *piece, int x,int y, int jokerX, int jokerY, PieceType changeTo, bool withJoker);

	Piece204156384 *getBoardContent(int x,int y);

	bool isInBoard(int x, int y);

	void consoleErrorMessage(Player &player);

};













#endif /* GAME_H_ */
