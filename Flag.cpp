


#include "Flag.h"

bool Flag::isWinning(PieceType type) const {
	switch(type){
		case PieceType::FlagType:
			return true;
			break;
		case PieceType::BombType:
			return true;
			break;
		default:
			return false;
	}
}

char Flag::getRepr() const{
	return this->formatRepr('F');
}


