CXX=clang++
CXXFLAGS=-std=c++11 -pedantic
OBJ=./lib/Main.o ./lib/Chess.o ./lib/Moves.o ./lib/Board.o ./lib/Bitboard.o ./lib/Types.o
SRC=./lib/Main.cpp Chess.cpp Moves.cpp Board.cpp Bitboard.cpp Types.cpp

Chess: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o Chess

./lib/Main.o: ./lib/Chess.h
./lib/Chess.o: ./lib/Moves.h
./lib/Moves.o: ./lib/Board.h
./lib/Board.o: ./lib/Bitboard.h
./lib/Bitboard.o: ./lib/Types.h
./lib/Types.o: 

clean:
	rm -f Chess $(OBJ)