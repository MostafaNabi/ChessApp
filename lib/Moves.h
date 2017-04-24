#ifndef MOVES_H
#define MOVES_H

#include "Bitboard.h"
#include "Board.h"

namespace Moves {
    
// ----------------------------------------------------------------------------
// ------------------------- Move Validation ----------------------------------
// ----------------------------------------------------------------------------
    
    // Pass by value as we want to modify the Board without altering the original
    bool is_valid_move(Move move, const Board& board);
    bool validate_normal_move(Move move, const Board& board);
    
// ----------------------------------------------------------------------------
// ------------------------- Check and Checkmate ------------------------------
// ----------------------------------------------------------------------------
    
    bool is_in_checkmate(Colour c, const Board& board);
    bool is_in_check(Colour c, const Board& board);
    
    // Checks if the move results in the player making the move being in check
    // Assumes given move is legal
    bool results_in_check(Move move, const Board& board);
    
    // Returns true if at least one of the given moves results in check
    // Assumes all given moves all legal
    bool any_results_in_check(std::vector<Move> moves, const Board& board);
    
    // Retuns true if all the given moves result in check
    // Assumes all given moves all legal
    bool all_results_in_check(std::vector<Move> moves, const Board& board);
    
    bool can_castle(CastlingRights cr, const Board& board);
    // Checks before having moved pawn
    bool can_promote_pawn(Move move, const Board& board);
    // Checks after having moved pawn
    bool can_promote_pawn(Square s, const Board& board);


// ----------------------------------------------------------------------------
// ------------------------- Determining Move types ---------------------------
// ----------------------------------------------------------------------------

    // Assumes move is legal, tries checking for special moves
    // If none match then returns normal
    MoveType infer_move_type(Move m, const Board& board);
    bool is_castling(Move move, const Board& board);
    bool is_promoting_pawn(Move move, const Board& board);

// ----------------------------------------------------------------------------
// ------------------------- Move Bitboards -----------------------------------
// ----------------------------------------------------------------------------

    
    std::vector<Move> all_player_move_list(Colour c, const Board& board);
    std::vector<Move> all_castling_options(Colour c, const Board& board);
    std::vector<Move> all_move_list_for(Piece p, const Board& board);
    
    Bitboard all_player_move_bb(Colour c, const Board& board);
    Bitboard all_move_bb_for(Piece p, const Board& board);
    
    std::vector<Move> all_player_attack_list(Colour c, const Board& board);
    std::vector<Move> all_attack_list_for(Piece p, const Board& board);
    
    Bitboard all_player_attack_bb(Colour c, const Board& board);
    Bitboard all_attack_bb_for(Piece p, const Board& board);
    
    Bitboard get_move_bitboard(Square s, const Board& board);
    Bitboard king_move_bb   (Square s, const Board& board);
    Bitboard queen_move_bb  (Square s, const Board& board);
    Bitboard bishop_move_bb (Square s, const Board& board);
    Bitboard knight_move_bb (Square s, const Board& board);
    Bitboard rook_move_bb   (Square s, const Board& board);
    Bitboard pawn_move_bb   (Square s, const Board& board);
    
    // Returns positions pawn puts under threat, even if it
    // cannot attack them
    Bitboard get_attack_bitboard(Square s, const Board& board);
    Bitboard king_attack_bb(Square s, const Board& board);
    Bitboard queen_attack_bb(Square s, const Board& board);
    Bitboard bishop_attack_bb(Square s, const Board& board);
    Bitboard knight_attack_bb(Square s, const Board& board);
    Bitboard rook_attack_bb(Square s, const Board& board);
    Bitboard pawn_attack_bb (Square s, const Board& board);
    
    
    Bitboard direction_bb(Square s, Direction d);
    Bitboard direction_mask(Square s, Direction d, const Board& board);



}
#endif
