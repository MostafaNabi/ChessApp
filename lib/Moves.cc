#include <stdexcept>
#include <iostream>
#include "Moves.h"

namespace Moves {
    
//-----------------------------------------------------------------------------
// ------------------------- Move Validation ----------------------------------
// ----------------------------------------------------------------------------
    
    bool is_valid_move(Move move, const Board& board) {
         /* if(board.infer_player_colour(move.origin) != c) {
              return false;
          }*/
        
        MoveType move_type = infer_move_type(move, board);
        switch(move_type) {
            case NORMAL: return validate_normal_move(move, board);
                
            case CASTLE: {
                CastlingRights cr = (CastlingRights)move.destination;
                return can_castle(cr, board);
            }
            
            case PAWN_PROMOTION: {
                bool valid = validate_normal_move(move, board);
                if(valid) {
                    return can_promote_pawn(move, board);
                }
            }
                
            default: return validate_normal_move(move, board);
        }
    }

    bool validate_normal_move(Move move, const Board& board) {
        Bitboard move_bb = get_move_bitboard(move.origin, board);
        
        // Destination square is not within legal moves
        if((move_bb & move.destination) == 0) {
            return false;
        }
        
        // Move would result in check
        if(results_in_check(move, board)) {
            return false;
        }
        return true;
    }
    
    
// ----------------------------------------------------------------------------
// ------------------------- Check and Checkmate ------------------------------
// ----------------------------------------------------------------------------
    
    
    bool is_in_checkmate(Colour c, const Board& board) {
        std::vector<Move> all_moves = all_player_move_list(c, board);
        for(Move move : all_moves) {
            if(!results_in_check(move, board)) {
                return false;
            }
        }
        return true;
    }
    
    bool is_in_check(Colour c, const Board& board) {
        // Get position of c's king
        Bitboard king_bb;
        Bitboard opp_atk_bb;
        
        if(c == WHITE) {
            king_bb = board.get_board_for(WHITE_KING);
            opp_atk_bb = all_player_attack_bb(BLACK, board);
        } else {
            king_bb = board.get_board_for(BLACK_KING);
            opp_atk_bb = all_player_attack_bb(WHITE, board);
        }
        return ( (king_bb & opp_atk_bb) != 0 );
    }

    
    bool results_in_check(Move move, const Board& board) {
        Board temp = board;
        temp.move_piece(move);
        return is_in_check(board.get_current_turn(), temp);
    }
    
    bool any_results_in_check(std::vector<Move> moves, const Board& board) {
        for(Move m : moves) {
            Board temp = board;
            if(results_in_check(m, temp)) {
                return true;
            }
        }
        return false;
        
    }
    
    bool all_result_in_check(std::vector<Move> moves, const Board& board) {
        for(Move m : moves) {
            Board temp = board;
            if(!results_in_check(m, temp)) {
                return false;
            }
        }
        return true;
    }
    
    
    bool can_castle(CastlingRights cr, const Board& board) {
        Colour col = (cr == WHITE_KINGSIDE_CR || cr == WHITE_QUEENSIDE_CR) ? WHITE : BLACK;
        Bitboard opp_atk_bb = (col == WHITE) ? all_player_attack_bb(BLACK, board) : all_player_attack_bb(WHITE, board);
        Bitboard same_bb = (col == WHITE) ? board.all_white_bb() : board.all_black_bb();
        
        if(is_in_check(col, board)) {
            return false;
        }
        
        if(col == WHITE && ((board.castling_rights & WHITE_KING_CR) != 0) && ((board.castling_rights & cr) != 0)) {
            // check for occupied squares and squares under attack
            Bitboard pass_through_bb;
            if(cr == WHITE_KINGSIDE_CR) {
                pass_through_bb |= SQ_5;
                pass_through_bb |= SQ_6;
                
            } else {
                pass_through_bb |= SQ_2;
                pass_through_bb |= SQ_3;
            }
            return ( (opp_atk_bb & pass_through_bb) == 0 && (same_bb & pass_through_bb) == 0);
        }
        
        if(col == BLACK && ((board.castling_rights & BLACK_KING_CR) != 0) && ((board.castling_rights & cr) != 0)) {
            Bitboard pass_through_bb;
            if(cr == BLACK_KINGSIDE_CR) {
                pass_through_bb |= SQ_61;
                pass_through_bb |= SQ_62;
            } else {
                pass_through_bb |= SQ_58;
                pass_through_bb |= SQ_59;
            }
            return ( (opp_atk_bb & pass_through_bb) == 0 && (same_bb & pass_through_bb) == 0);
        }
        
        return false;
    }
    
    bool can_promote_pawn(Move move, const Board& board) {
        Piece piece = board.get_piece_at(move.origin);
        if(piece == WHITE_PAWN && ((Bitboard::rank(7) & move.destination) != 0)) {
            return true;
        }
        
        if(piece == BLACK_PAWN && ((Bitboard::rank(0) & move.destination) != 0)) {
            return true;
        }
        return false;
    }
    
    bool can_promote_pawn(Square s, const Board& board) {
        Piece piece = board.get_piece_at(s);
        if(piece == WHITE_PAWN && ((Bitboard::rank(7) & s) != 0)) {
            return true;
        }
        
        if(piece == BLACK_PAWN && ((Bitboard::rank(0) & s) != 0)) {
            return true;
        }
        return false;
    }
    
    
// ----------------------------------------------------------------------------
// ------------------------- Determining Move types ---------------------------
// ----------------------------------------------------------------------------
    
    MoveType infer_move_type(Move move, const Board& board) {
        if(is_castling(move, board)) {
            return CASTLE;
            
        } else if(is_promoting_pawn(move, board)) {
            return PAWN_PROMOTION;
            
        } else {
            return NORMAL;
        }
    }
    
    bool is_castling(Move move, const Board& board) {
        Colour c = board.get_current_turn();
        Piece p = board.get_piece_at(move.origin);
        
        if(c == WHITE && p == WHITE_KING) {
            if(move.origin == (int)WHITE_KING_CR && (move.destination == (int)WHITE_KINGSIDE_CR ||
                                                     move.destination == (int)WHITE_QUEENSIDE_CR)) {
                return true;
            }
        } else if(c == BLACK && p == BLACK_KING) {
            if(move.origin == (int)BLACK_KING_CR && (move.destination == (int)BLACK_KINGSIDE_CR ||
                                                     move.destination == (int)BLACK_QUEENSIDE_CR)) {
                return true;
            }
        }
        return false;
    }
    
    bool is_promoting_pawn(Move move, const Board& board) {
        Piece piece = board.get_piece_at(move.origin);
        
        if(piece == WHITE_PAWN && ((Bitboard::rank(7) & move.destination) != 0)) {
            return true;
        }
        
        if(piece == BLACK_PAWN && ((Bitboard::rank(0) & move.destination) != 0)) {
            return true;
        }
        return false;
    }

    
    

// ----------------------------------------------------------------------------
// ------------------------- Move and Attack Bitboards -----------------------------------
// ----------------------------------------------------------------------------
    std::vector<Move> all_player_move_list(Colour c, const Board& board) {
        std::vector<Move> move_list;
        
        if(c == WHITE) {
            for(Piece p :Types::ALL_WHITE_PIECES) {
                std::vector<Move> list = all_move_list_for(p, board);
                move_list.insert(move_list.end(), list.begin(), list.end());
            }
        } else {
            for(Piece p :Types::ALL_BLACK_PIECES) {
                std::vector<Move> list = all_move_list_for(p, board);
                move_list.insert(move_list.end(), list.begin(), list.end());
            }
        }
        
        std::vector<Move> castle_moves = all_castling_options(c, board);
        move_list.insert(move_list.end(), castle_moves.begin(), castle_moves.end());
        return move_list;
    }
    
    
    std::vector<Move> all_castling_options(Colour c, const Board& board) {
        std::vector<Move> list;
        if(c == WHITE) {
            if(can_castle(WHITE_KINGSIDE_CR, board)) {
                Move m = Move( (Square)WHITE_KING_CR, (Square)WHITE_KINGSIDE_CR, CASTLE);
                list.push_back(m);
            }
            
            if(can_castle(WHITE_QUEENSIDE_CR, board)) {
                Move m = Move( (Square)WHITE_KING_CR, (Square)WHITE_QUEENSIDE_CR, CASTLE);
                list.push_back(m);
            }
        } else if(c == BLACK) {
            if(can_castle(BLACK_KINGSIDE_CR, board)) {
                Move m = Move( (Square)BLACK_KING_CR, (Square)BLACK_KINGSIDE_CR, CASTLE);
                list.push_back(m);
            }
            
            if(can_castle(BLACK_QUEENSIDE_CR, board)) {
                Move m = Move( (Square)BLACK_KING_CR, (Square)BLACK_QUEENSIDE_CR, CASTLE);
                list.push_back(m);
            }
        }
        return list;
    }
    
    std::vector<Move> all_player_attack_list(Colour c, const Board& board) {
        std::vector<Move> move_list;
        
        if(c == WHITE) {
            for(Piece p :Types::ALL_WHITE_PIECES) {
                std::vector<Move> list = all_attack_list_for(p, board);
                move_list.insert(move_list.end(), list.begin(), list.end());
            }
        } else {
            for(Piece p :Types::ALL_BLACK_PIECES) {
                std::vector<Move> list = all_attack_list_for(p, board);
                move_list.insert(move_list.end(), list.begin(), list.end());            }
        }
        return move_list;
    }
    
    
    std::vector<Move> all_move_list_for(Piece p, const Board& board) {
        std::vector<Move> move_list;
        Bitboard piece_bb =  board.get_board_for(p);
        
        std::vector<Square> orig_list = piece_bb.all_bit_indexes();
        
        for(Square orig: orig_list) {
            Bitboard move_bb = get_move_bitboard(orig, board);
            std::vector<Square> dest_list = move_bb.all_bit_indexes();
            
            for(Square dest : dest_list) {
                Move m = Move(orig, dest);
                if(is_valid_move(m, board)) {
                    m.move_type = infer_move_type(m, board);
                    move_list.push_back(m);
                }
            }
        }
        return move_list;
    }
    
    std::vector<Move> all_attack_list_for(Piece p, const Board& board) {
        std::vector<Move> atk_list;
        Bitboard piece_bb =  board.get_board_for(p);
        
        std::vector<Square> orig_list = piece_bb.all_bit_indexes();
        
        for(Square orig: orig_list) {
            Bitboard atk_bb = get_attack_bitboard(orig, board);
            std::vector<Square> dest_list = atk_bb.all_bit_indexes();
            
            for(Square dest : dest_list) {
                Move m = Move(orig, dest);
                if(is_valid_move(m, board)) {
                    m.move_type = infer_move_type(m, board);
                    atk_list.push_back(m);
                }
            }
        }
        return atk_list;
    }
    
    Bitboard all_player_move_bb(Colour c, const Board& board) {
        Bitboard move_bb;
        
        if(c == WHITE) {
            for(Piece p :Types::ALL_WHITE_PIECES) {
                move_bb |= all_move_bb_for(p, board);
            }
        } else {
            for(Piece p :Types::ALL_BLACK_PIECES) {
                move_bb |= all_move_bb_for(p, board);
            }
        }
        return move_bb;
    }
    Bitboard all_player_attack_bb(Colour c, const Board& board) {
        Bitboard atk_bb;
        if(c == WHITE) {
            for(Piece p :Types::ALL_WHITE_PIECES) {
                atk_bb |= all_attack_bb_for(p, board);
            }
        } else {
            for(Piece p :Types::ALL_BLACK_PIECES) {
                atk_bb |= all_attack_bb_for(p, board);
            }
        }
        return atk_bb;
    }
    
    Bitboard all_move_bb_for(Piece p, const Board& board) {
        Bitboard piece_bb =  board.get_board_for(p);
        Bitboard move_bb;
        
        std::vector<Square> positions = piece_bb.all_bit_indexes();
        for (Square s : positions) {
            move_bb |= get_move_bitboard(s, board);
        }
        return move_bb;
    }
    
    
    Bitboard all_attack_bb_for(Piece p, const Board& board) {
        Bitboard piece_bb =  board.get_board_for(p);
        Bitboard atk_bb;
        std::vector<Square> positions = piece_bb.all_bit_indexes();
        for (Square s : positions) {
            atk_bb |= get_attack_bitboard(s, board);
        }
        return atk_bb;
    }
    
    
    
    Bitboard get_move_bitboard(Square s, const Board& board) {
        Piece p = board.get_piece_at(s);
        PieceType type = Types::get_piece_type(p);
        switch(type) {
            case KING:   return king_move_bb(s, board);
            case QUEEN:  return queen_move_bb(s, board);
            case BISHOP: return bishop_move_bb(s, board);
            case KNIGHT: return knight_move_bb(s, board);
            case ROOK:   return rook_move_bb(s, board);
            case PAWN:   return pawn_move_bb(s, board);
            case PIECETYPE_NONE : return Bitboard();
            default: return Bitboard();
        }
    }
    
    Bitboard get_attack_bitboard(Square s, const Board& board) {
        Piece p = board.get_piece_at(s);
        PieceType type = Types::get_piece_type(p);
        switch(type) {
            case KING:   return king_attack_bb(s, board);
            case QUEEN:  return queen_attack_bb(s, board);
            case BISHOP: return bishop_attack_bb(s, board);
            case KNIGHT: return knight_attack_bb(s, board);
            case ROOK:   return rook_attack_bb(s, board);
            case PAWN:   return pawn_attack_bb(s, board);
            case PIECETYPE_NONE : return Bitboard();
            default: return Bitboard();
        }
    }

    // Returns a move bitboard with pseudo-legal moves (No validation for checks)
    Bitboard king_move_bb(Square s, const Board& board) {
        Bitboard move_bb = king_attack_bb(s, board);
        Colour c = board.get_current_turn();
        Bitboard same_bb = (c == WHITE) ? board.all_white_bb() : board.all_black_bb();

        // remove positons that would overlap with own pieces
        return Bitboard(move_bb ^ (move_bb & same_bb));
    }
    
    Bitboard king_attack_bb(Square s, const Board& board) {
        Bitboard atk_bb;
        
        atk_bb |= Bitboard::lsb(Bitboard::north(s));
        atk_bb |= Bitboard::lsb(Bitboard::east(s));
        atk_bb |= Bitboard::msb(Bitboard::south(s));
        atk_bb |= Bitboard::msb(Bitboard::west(s));
        
        atk_bb |= Bitboard::lsb(Bitboard::north_east(s));
        atk_bb |= Bitboard::lsb(Bitboard::north_west(s));
        atk_bb |= Bitboard::msb(Bitboard::south_east(s));
        atk_bb |= Bitboard::msb(Bitboard::south_west(s));
        
        return atk_bb;
    }


    Bitboard queen_move_bb(Square s, const Board& board) {
        Bitboard move_bb = queen_attack_bb(s, board);
        Colour c = board.get_current_turn();
        Bitboard same_bb = (c == WHITE) ? board.all_white_bb() : board.all_black_bb();
        return Bitboard(move_bb ^ (move_bb & same_bb));
    }
    
    Bitboard queen_attack_bb(Square s, const Board& board) {
        Bitboard atk_bb = rook_attack_bb(s, board) | bishop_attack_bb(s, board);
        return atk_bb;
    }
    
    

    Bitboard bishop_move_bb(Square s, const Board& board) {
        Bitboard move_bb = bishop_attack_bb(s, board);
        Colour c = board.get_current_turn();
        Bitboard same_bb = (c == WHITE) ? board.all_white_bb() : board.all_black_bb();
        return Bitboard(move_bb ^ (move_bb & same_bb));
    }
    
    Bitboard bishop_attack_bb(Square s, const Board& board) {
        Bitboard atk_bb;
        atk_bb |= direction_mask(s, NORTH_EAST, board);
        atk_bb |= direction_mask(s, NORTH_WEST, board);
        atk_bb |= direction_mask(s, SOUTH_EAST, board);
        atk_bb |= direction_mask(s, SOUTH_WEST, board);
        return atk_bb;
    }


    Bitboard knight_move_bb(Square s, const Board& board) {
        Bitboard move_bb = knight_attack_bb(s, board);
        Colour c = board.get_current_turn();
        Bitboard same_bb = (c == WHITE) ? board.all_white_bb() : board.all_black_bb();
        return Bitboard(move_bb ^ (move_bb & same_bb));
    }
    
    
    Bitboard knight_attack_bb(Square s, const Board& board) {
        Bitboard atk_bb;
        
        // Forwards
        if( !(Bitboard::rank(6) & s) && !(Bitboard::rank(7) & s) ) {
            if(!(Bitboard::file(0) & s)) {atk_bb |= Square(s+15);}
            if(!(Bitboard::file(7) & s)) {atk_bb |= Square(s+17);}
        }
        
        // Backwards
        if( !(Bitboard::rank(0) & s) && !(Bitboard::rank(1) & s) ) {
            if(!(Bitboard::file(0) & s)) {atk_bb |= Square(s-17);}
            if(!(Bitboard::file(7) & s)) {atk_bb |= Square(s-15);}
        }
        
        // Right
        if( !(Bitboard::file(6) & s) && !(Bitboard::file(7) & s) ) {
            if(!(Bitboard::rank(0) & s)) {atk_bb |= Square(s-6);}
            if(!(Bitboard::rank(7) & s)) {atk_bb |= Square(s+10);}
        }
        
        // Left
        if( !(Bitboard::file(0) & s) && !(Bitboard::file(1) & s) ) {
            if(!(Bitboard::rank(0) & s)) {atk_bb |= Square(s-10);}
            if(!(Bitboard::rank(7) & s)) {atk_bb |= Square(s+6);}
        }
        return atk_bb;
    }

    Bitboard rook_move_bb(Square s, const Board& board) {
        Colour c = board.get_current_turn();
        Bitboard move_bb = rook_attack_bb(s, board);
        Bitboard same_bb = (c == WHITE) ? board.all_white_bb() : board.all_black_bb();
        return Bitboard(move_bb ^ (move_bb & same_bb));
    }
    
    
    Bitboard rook_attack_bb(Square s, const Board& board) {
        Bitboard atk_bb;
        atk_bb |= direction_mask(s, NORTH, board);
        atk_bb |= direction_mask(s, SOUTH, board);
        atk_bb |= direction_mask(s, EAST, board);
        atk_bb |= direction_mask(s, WEST, board);
        return atk_bb;
    }

    
    Bitboard pawn_move_bb(Square s, const Board& board) {
        Bitboard move_bb;
        Bitboard same_bb;
        Bitboard opp_bb;
        Colour c = board.get_current_turn();
        if(c == WHITE ) {same_bb = board.all_white_bb(); opp_bb = board.all_black_bb();}
        else {same_bb = board.all_black_bb(); opp_bb = board.all_white_bb();}
        Bitboard all_bb = same_bb | opp_bb;
        
        
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
        move_bb ^= (move_bb & all_bb);
        Bitboard atk_bb = pawn_attack_bb(s, board);
        atk_bb &= opp_bb;
        move_bb |= atk_bb;
        
        // remove positons that would overlap with other pieces
        return Bitboard(move_bb ^ (move_bb & same_bb));
    }
    
    Bitboard pawn_attack_bb(Square s, const Board& board) {
        Bitboard atk_bb;
        Colour c = board.get_current_turn();

        if(c == WHITE) {
            if(!(Bitboard::rank(7) & s)) {
                if(!(atk_bb.file(0) & s) ) {atk_bb |= Square(s+7);}
                if(!(atk_bb.file(7) & s)) {atk_bb |= Square(s+9);}
            }
        } else {
            if(!(atk_bb.rank(0) & s)) {
                if(!(atk_bb.file(0) & s)) {atk_bb |= Square(s-9);}
                if(!(atk_bb.file(7) & s)) {atk_bb |= Square(s-7);}
            }
        }
        return Bitboard(atk_bb);
    }

    Bitboard direction_bb(Square s, Direction d) {
        switch(d) {
            case NORTH: return Bitboard::north(s);
            case EAST: return Bitboard::east(s);
            case SOUTH: return Bitboard::south(s);
            case WEST: return Bitboard::west(s);
            case NORTH_EAST: return Bitboard::north_east(s);
            case NORTH_WEST: return Bitboard::north_west(s);
            case SOUTH_EAST: return Bitboard::south_east(s);
            case SOUTH_WEST: return Bitboard::south_west(s);
            default: return Bitboard(0);
        }
    }
    
    
    // Change this to always include the pieces it clashes with
    Bitboard direction_mask(Square s, Direction d, const Board& board) {
        Bitboard dir_bb = direction_bb(s, d);
        Bitboard all_bb = board.all_white_bb() | board.all_black_bb();
        
        Bitboard intersect_bb = dir_bb & all_bb;
        Bitboard intersect_point;
        Bitboard intersect_mask;
        
        if(intersect_bb == 0 ){
            return dir_bb;
        }
        
        if(d == NORTH || d == EAST || d == NORTH_EAST || d == NORTH_WEST) {
            intersect_point = Bitboard::lsb(intersect_bb);
            intersect_mask = Bitboard::lsb_mask(intersect_point);
            
        } else {
            intersect_point = Bitboard::msb(intersect_bb);
            intersect_mask = Bitboard::msb_mask(intersect_point);
        }
        
        return (intersect_mask & dir_bb);
    }
}
