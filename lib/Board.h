#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <regex>
#include "Bitboard.h"

class Board {

public:

    // ------- Variables -------
    Bitboard bitboards[12];
    Bitboard castling_rights;
    Colour current_turn;

    // ------- Constructors --------
    Board();

    // Copy and move constructors
    Board(const Board& other);
    Board(Board&& other);

    // Destructor
    ~Board();

    // ----Copy and Move Operators ---------
    Board& operator=(const Board& other);
    Board& operator=(Board&& other);


    // ---- Functions --------
    void update_turn();
    
    Piece get_piece_at(Square s) const;
    Bitboard get_board_for(Piece p) const;
    void set_board_for(Piece p, Bitboard b);


    Bitboard all_white_bb() const;
    Bitboard all_black_bb() const;


    void move_piece(Move move);
    void castle(CastlingRights cr);
    void promote_pawn(Square s, Piece piece);
    
    
    void set_castling_flags(Move m);
    Colour infer_player_colour(Square orig) const;

    void build_from_fen(std::string fen);

};

#endif
