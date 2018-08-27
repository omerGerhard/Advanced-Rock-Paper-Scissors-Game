


#include "Joker.h"
#include "Parser.h"
#include <vector>
#include <string>



PieceType Joker::getDynamicType() const {
	if(!dynamicPiece)
		return PieceType::NoneType;
	return this->dynamicPiece->getType();
}


bool Joker::changeType(PieceType type){

	if(type == PieceType::FlagType || type == PieceType::JokerType)
		return false;

	delete dynamicPiece;
	dynamicPiece = Piece204156384::pieceFactory(player,type);

	return true;
}


//=====================changed after grades were given=====================
Log Joker::initPosition(Game &game, const std::vector<std::string>& line) {

	if(!isInitLineValid(line)) return Log::IllegalFormat;
	char dynamicChar = line[3][0];
	PieceType dynamicType = Piece204156384::charToPieceType(dynamicChar);
	if(!changeType(dynamicType)) return Log::IllegalFormat;

	return Piece204156384::initPosition(game,line);

}
//=========================================================================


bool Joker::isInitLineValid(const std::vector<std::string> &line) const {
	if((int)line.size() != 4)
		return false;
	if(line[3].length() != 1)
		return false;
	return true;
}
