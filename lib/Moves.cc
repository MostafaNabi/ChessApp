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
            case PAWN:   return (pawn_move_bb(s, c, board) | pawn_attack_bb(s, c, board));
            case PIECETYPE_NONE : return Bitboard();
        }
    }

    // Returns a move bitboard with pseudo-legal moves (No validation for checks)
    Bitboard king_move_bb(Square s, Colour c, const Board& board) {
        Bitboard move_bb;

        if(!(Bitboard::rank(7) & s)) {move_bb |= Square(s+8);}
        if(!(Bitboard::rank(0) & s)) {move_bb |= Square(s-8);}
        if(!(Bitboard::file(7) & s)) {move_bb |= Square(s+1);}
        if(!(Bitboard::file(0) & s)) {move_bb |= Square(s-1);}

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
        Bitboard move_bb;
        return Bitboard();
    }


    Bitboard knight_move_bb(Square s, Colour c, const Board& board) {
        Bitboard move_bb;

        // Forwards
        if( !(Bitboard::rank(6) & s) && !(Bitboard::rank(7) & s) ) {
            if(!(Bitboard::file(0) & s)) {move_bb |= Square(s+15);}
            if(!(Bitboard::file(7) & s)) {move_bb |= Square(s+17);}
        }

        // Backwards
        if( !(Bitboard::rank(0) & s) && !(Bitboard::rank(1) & s) ) {
            if(!(Bitboard::file(0) & s)) {move_bb |= Square(s-17);}
            if(!(Bitboard::file(7) & s)) {move_bb |= Square(s-15);}
        }

        // Right
        if( !(Bitboard::file(6) & s) && !(Bitboard::file(7) & s) ) {
            if(!(Bitboard::rank(0) & s)) {move_bb |= Square(s-6);}
            if(!(Bitboard::rank(7) & s)) {move_bb |= Square(s+10);}
        }

        // Left
        if( !(Bitboard::file(0) & s) && !(Bitboard::file(1) & s) ) {
            if(!(Bitboard::rank(0) & s)) {move_bb |= Square(s-10);}
            if(!(Bitboard::rank(7) & s)) {move_bb |= Square(s+6);}
        }

        Bitboard same_bb;
        if(c == WHITE ) {same_bb = board.all_white_bb();}
        else {same_bb = board.all_black_bb();}

        // remove positons that would overlap with own pieces
        return Bitboard(move_bb ^ (move_bb & same_bb));
    }

    Bitboard rook_move_bb(Square s, Colour c, const Board& board) {
        Bitboard move_bb;
        move_bb |= direction_mask(s, c, NORTH, board);
        move_bb |= direction_mask(s, c, SOUTH, board);
        move_bb |= direction_mask(s, c, EAST, board);
        move_bb |= direction_mask(s, c, WEST, board);
        return move_bb;
    }

    
    Bitboard pawn_move_bb(Square s, Colour c, const Board& board) {
        Bitboard move_bb;
        Bitboard all_bb = (board.all_black_bb() | board.all_white_bb());
        
        // No checks for occupency except moving two squares, do checks at the end by complementing with all_bb
        if(c == WHITE) {
            if(!(Bitboard::rank(7) & s)) {
                move_bb |= Square(s+8);
            }
            
            if( (Bitboard::rank(1) & s) && !(all_bb & Square(s+8)) ) {
                move_bb |= Square(s+16);
            }
        } else {
            if(!(Bitboard::rank(0) & s)) {
                move_bb |= Square(s-8);
            }
            if( (Bitboard::rank(6) & s) && !(all_bb & Square(s-8)) ) {
                move_bb |= Square(s-16);
            }
        }
        
        // remove positons that would overlap with other pieces
        return Bitboard(move_bb ^ (move_bb & all_bb));
    }
    
    Bitboard pawn_attack_bb(Square s, Colour c, const Board& board) {
        Bitboard atk_bb;
        
        if(c == WHITE) {
            if(!(Bitboard::rank(7) & s)) {
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
        Bitboard opp_bb;
        if(c == WHITE ) {same_bb = board.all_white_bb(); opp_bb = board.all_black_bb();}
        else {same_bb = board.all_black_bb(); opp_bb = board.all_white_bb();}
        
        // remove positons that would overlap with own pieces
        atk_bb &= opp_bb;
        return Bitboard(atk_bb ^ (atk_bb & same_bb));
    }


    
    
    // ------------ Utility Functions ------------------
    
    
    Bitboard direction_bb(Square s, Direction d) {
        switch(d) {
            case NORTH: return Bitboard::north(s);
            case EAST: return Bitboard::east(s);
            case SOUTH: return Bitboard::south(s);
            case WEST: return Bitboard::west(s);
            default: return Bitboard(0);
        }
    }
    
        
    Bitboard direction_mask(Square s, Colour c, Direction d, const Board& board) {
        Bitboard dir_bb = direction_bb(s, d);
        Bitboard same_bb;
        Bitboard opp_bb;
        if(c == WHITE) {same_bb = board.all_white_bb(); opp_bb = board.all_black_bb();}
        else {same_bb = board.all_black_bb(); opp_bb = board.all_white_bb();}
        
        Bitboard same_intersect = dir_bb & same_bb;
        Bitboard opp_intersect  = dir_bb & opp_bb;
        
        if( same_intersect == 0 && opp_intersect == 0) {
            return dir_bb;
        }
        
        Bitboard same_intersect_point;
        Bitboard same_intersect_mask;
        
        Bitboard opp_intersect_point;
        Bitboard opp_intersect_mask;
        
        if(d == NORTH || d == EAST) {
            same_intersect_point = Bitboard::lsb(same_intersect);
            same_intersect_mask = Bitboard::lsb_mask(same_intersect_point) ^ same_intersect_point;
            
            opp_intersect_point = Bitboard::lsb(opp_intersect);
            opp_intersect_mask = Bitboard::lsb_mask(opp_intersect_point);
            
        } else {
            same_intersect_point = Bitboard::msb(same_intersect);
            same_intersect_mask = Bitboard::msb_mask(same_intersect_point) ^ same_intersect_point;
            
            opp_intersect_point = Bitboard::msb(opp_intersect);
            opp_intersect_mask = Bitboard::msb_mask(opp_intersect_point);
        }
        
        
        if( same_intersect_point != 0 && opp_intersect_point  == 0) {
            return (same_intersect_mask & dir_bb);
        }
        
        if( same_intersect_point == 0 && opp_intersect_point  != 0) {
            return (opp_intersect_mask & dir_bb);
        }
        
        
        if(d == NORTH || d == EAST) {
            if(same_intersect_point < opp_intersect_point ) {
                return (same_intersect_mask & dir_bb);
            
            } else {
                return (opp_intersect_mask & dir_bb);
            }
        } else {
            if(same_intersect_point > opp_intersect_point ) {
                return (same_intersect_mask & dir_bb);
                
            } else {
                return (opp_intersect_mask & dir_bb);
            }
        }
    }
    
}
