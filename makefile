COMP = g++-5.3.0

OBJS = main.o Flag.o Game.o Joker.o Paper.o Parser.o Piece.o Player.o Rock.o Scissors.o
EXEC = ex1
CPP_COMP_FLAG = -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG

$(EXEC): $(OBJS)
	$(COMP) $(OBJS) -o $@

main.o: main.cpp Game.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Game.o: Game.cpp Game.h Joker.h Parser.h Piece.h Player.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Joker.o: Joker.cpp Joker.h Parser.h Piece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Paper.o: Paper.cpp Paper.h Piece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Parser.o: Parser.cpp Parser.h Game.h Joker.h Piece.h Game.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Piece.o: Piece.cpp Piece.h Scissors.h Joker.h Rock.h Bomb.h Paper.h Flag.h Player.h Game.h Parser.h PiecePos.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Player.o: Player.cpp Player.h Piece.h Parser.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Rock.o: Rock.cpp Rock.h Piece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Scissors.o: Scissors.cpp Scissors.h Piece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
Flag.o: Flag.cpp Flag.h Piece.h
	$(COMP) $(CPP_COMP_FLAG) -c $*.cpp
clean:
	rm -f $(OBJS) $(EXEC)