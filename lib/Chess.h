#ifndef CHESS_H
#define CHESS_H
#include <string>
#include "Moves.h"


class Chess {
public:

    // ------- Variables --------
    Board board;



    // ------- Constructors --------
    Chess();
    Chess(int ai);
    Chess(std::string fen);
    Chess(std::string fen, int ai);

    // No copy and move constructors
    Chess(const Chess& other);
    Chess(Chess&& other);

    Chess& operator=(const Chess& other);
    Chess& operator=(Chess&& other);

    /*
        Take primitive values from WebInterface and convert them into
        enums
    */
    bool make_move(Square orig, Colour col, Square dest);
};

// Provides interface between Nodejs and C++
#endif
