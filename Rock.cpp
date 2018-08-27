
#include "Rock.h"


bool Rock::isWinning(PieceType type) const{
	switch(type){
		case PieceType::RockType:
			return true;
			break;
		case PieceType::ScissorsType:
			return true;
			break;
		case PieceType::BombType:
			return true;
			break;
		case PieceType::FlagType:
			return true;
			break;
		default:
			return false;
	}
}

