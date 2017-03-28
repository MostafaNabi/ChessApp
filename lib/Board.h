#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <regex>
#include "Bitboard.h"

class Board {

public:

    // ------- Variables -------
    Bitboard boards[12];

    Colour current_turn;
    unsigned int w_castle_rights;
    unsigned int b_castle_rights;


    // ------- Constructors --------
    Board();
    Board(std::string fen);

    void build_from_fen(std::string fen);

    // Copy and move constructors
    Board(const Board& other);
    Board(Board&& other);

    // Destructor
    ~Board();

    // ----Copy and Move Operators ---------
    Board& operator=(const Board& other);
    Board& operator=(Board&& other);


    // ---- Functions --------
    Piece get_piece_at(Square s) const;

    bool make_move(Square orig, Square dest, MoveType type);

};

#endif
