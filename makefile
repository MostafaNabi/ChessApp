CXX=clang++
CXXFLAGS=-std=c++11 -pedantic
OBJ=./lib/Main.o ./lib/Chess.o ./lib/Evaluation.o ./lib/Moves.o ./lib/Board.o ./lib/Bitboard.o ./lib/Types.o
SRC=./lib/Main.cc ./lib/Chess.cc ./lib/Evaluation.cc ./lib/Moves.cc ./lib/Board.cc ./lib/Bitboard.cc ./lib/Types.cc

Chess: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o Chess

./lib/Main.o: ./lib/Chess.h
./lib/Chess.o: ./lib/Evaluation.h
./lib/Evaluation.o: ./lib/Moves.h
./lib/Moves.o: ./lib/Board.h
./lib/Board.o: ./lib/Bitboard.h
./lib/Bitboard.o: ./lib/Types.h
./lib/Types.o: 

clean:
	rm -f Chess $(OBJ)