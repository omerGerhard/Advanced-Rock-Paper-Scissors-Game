

#ifndef PIECEPOS_H_
#define PIECEPOS_H_


class PiecePos{
	int x;
	int y;

public:

	PiecePos(int x, int y) : x(x) , y(y){};

	void setPos(int x, int y){
		this->x = x;
		this->y = y;
	}

	int getX(){
		return x;
	}

	int getY(){
		return y;
	}

};


#endif /* PIECEPOS_H_ */
