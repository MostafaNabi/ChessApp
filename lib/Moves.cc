#include <stdexcept>
#include <iostream>
#include "Moves.h"

namespace Moves {
    bool is_valid_move(Square orig, Colour c, Square dest, MoveType t, Board board) {
        Bitboard move_bb = get_move_bitboard(orig, c, board);
        return ((move_bb & dest) > 0);

    }

    MoveType infer_move_type(Square orig, Colour c, Square dest, Board b) {
        return NORMAL;
    }

    Colour infer_player_colour(Square orig, Board b) {
        Piece p = b.get_piece_at(orig);
        return Types::get_piece_colour(p);
    }

    Bitboard get_move_bitboard(Square s, Colour c, const Board& board) {
        Piece p = board.get_piece_at(s);
        PieceType type = Types::get_piece_type(p);
        switch(type) {
            case KING:   return king_move_bb(s, c, board);
            case QUEEN:  return queen_move_bb(s, c, board);
            case BISHOP: return bishop_move_bb(s, c, board);
            case KNIGHT: return knight_move_bb(s, c, board);
            case ROOK:   return rook_move_bb(s, c, board);
            case PAWN:   return pawn_move_bb(s, c, board);
            case PIECETYPE_NONE : return Bitboard();
        }
    }

    // Returns a move bitboard with pseudo-legal moves (No validation for checks)
    Bitboard king_move_bb(Square s, Colour c, const Board& board) {
        Bitboard move_bb;

        if(!(move_bb.rank(7) & s)) {move_bb |= Square(s+8);}
        if(!(move_bb.rank(0) & s)) {move_bb |= Square(s-8);}
        if(!(move_bb.file(7) & s)) {move_bb |= Square(s+1);}
        if(!(move_bb.file(0) & s)) {move_bb |= Square(s-1);}

        Bitboard same_bb;
        if(c == WHITE ) {same_bb = board.all_white_bb();}
        else {same_bb = board.all_black_bb();}

        // remove positons that would overlap with own pieces
        return Bitboard(move_bb ^ (move_bb & same_bb));
    }


    Bitboard queen_move_bb(Square s, Colour c, const Board& board) {
        return Bitboard();
    }

    Bitboard bishop_move_bb(Square s, Colour c, const Board& board) {
        return Bitboard();
    }


    Bitboard knight_move_bb(Square s, Colour c, const Board& board) {
        Bitboard move_bb;

        // Forwards
        if( !(move_bb.rank(6) & s) && !(move_bb.rank(7) & s) ) {
            if(!(move_bb.file(0) & s)) {move_bb |= Square(s+15);}
            if(!(move_bb.file(7) & s)) {move_bb |= Square(s+17);}
        }

        // Backwards
        if( !(move_bb.rank(0) & s) && !(move_bb.rank(1) & s) ) {
            if(!(move_bb.file(0) & s)) {move_bb |= Square(s-17);}
            if(!(move_bb.file(7) & s)) {move_bb |= Square(s-15);}
        }

        // Right
        if( !(move_bb.file(6) & s) && !(move_bb.file(7) & s) ) {
            if(!(move_bb.rank(0) & s)) {move_bb |= Square(s-6);}
            if(!(move_bb.rank(7) & s)) {move_bb |= Square(s+10);}
        }

        // Left
        if( !(move_bb.file(0) & s) && !(move_bb.file(1) & s) ) {
            if(!(move_bb.rank(0) & s)) {move_bb |= Square(s-10);}
            if(!(move_bb.rank(7) & s)) {move_bb |= Square(s+6);}
        }

        Bitboard same_bb;
        if(c == WHITE ) {same_bb = board.all_white_bb();}
        else {same_bb = board.all_black_bb();}

        // remove positons that would overlap with own pieces
        return Bitboard(move_bb ^ (move_bb & same_bb));
    }

    Bitboard rook_move_bb(Square s, Colour c, const Board& board) {
        return Bitboard();
    }


    Bitboard pawn_move_bb(Square s, Colour c, const Board& board) {
        Bitboard move_bb;
        Bitboard all_bb = (board.all_black_bb() | board.all_white_bb());

        // No checks for occupency except moving two squares, do checks at the end by complementing with all_bb
        if(c == WHITE) {
            if(!(move_bb.rank(7) & s)) {
                move_bb |= Square(s+8);
            }

            if( (move_bb.rank(1) & s) && !(all_bb & Square(s+8)) ) {
                move_bb |= Square(s+16);
            }
        } else {
            if(!(move_bb.rank(0) & s)) {
                move_bb |= Square(s-8);
            }
            if( (move_bb.rank(6) & s) && !(all_bb & Square(s-8)) ) {
                move_bb |= Square(s-16);
            }
        }

        // remove positons that would overlap with other pieces
        return Bitboard(move_bb ^ (move_bb & all_bb));
    }

    Bitboard pawn_attack_bb(Square s, Colour c, const Board& board) {
        Bitboard atk_bb;

        if(c == WHITE) {
            if(!(atk_bb.rank(7) & s)) {
                if(!(atk_bb.file(0) & s)) {atk_bb |= Square(s+7);}
                if(!(atk_bb.file(7) & s)) {atk_bb |= Square(s+9);}
            }
        } else {
            if(!(atk_bb.rank(0) & s)) {
                if(!(atk_bb.file(0) & s)) {atk_bb |= Square(s-9);}
                if(!(atk_bb.file(7) & s)) {atk_bb |= Square(s-7);}
            }
        }
        Bitboard same_bb;
        if(c == WHITE ) {same_bb = board.all_white_bb();}
        else {same_bb = board.all_black_bb();}

        // remove positons that would overlap with own pieces
        return Bitboard(atk_bb ^ (atk_bb & same_bb));
    }

}
