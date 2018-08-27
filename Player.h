/*
 * Player.h
 *
 *  Created on: 22 במרץ 2018
 *      Author: omerg
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#define ROCKS 2
#define PAPERS 5
#define SCISSORS 1
#define BOMBS 2
#define JOKERS 2
#define FLAGS 1

#define NUM_OF_PIECES ROCKS + PAPERS + SCISSORS + BOMBS + JOKERS + FLAGS


#include <fstream>

using namespace std;

class Piece204156384;
enum class Log : int;

enum PlayerType {
	player1,
	player2,
	dummyPlayer
};


class Player{

public:
	typedef struct status_t{
		Log log;
		int lineError;

		status_t(Log log, int lineError = -1) :log(log), lineError(lineError){}
	}Status;

private:
	bool lower;
	int score;
	Status status;
	string positionFile;
	string moveFile;
	ifstream* moveFileStream;
	PlayerType type;

public:

	Piece204156384 *pieces[NUM_OF_PIECES];

	Player(PlayerType _type);

	~Player();

	const Status& getStatus();

	PlayerType getType() const;

	void setStatus(Log log, int lineError = -1);

	bool isLower() const;

	void addPoint();

	const string& getPositionFile();

	ifstream *getMoveFileStream();

	bool canMove();

	bool hasFlags();

	string toString();
};

#endif /* PLAYER_H_ */
