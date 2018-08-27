
#include "Scissors.h"

bool Scissors::isWinning(PieceType type) const{
	switch(type){
		case PieceType::ScissorsType:
			return true;
			break;
		case PieceType::PaperType:
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



