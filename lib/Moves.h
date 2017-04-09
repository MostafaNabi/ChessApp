#ifndef MOVES_H
#define MOVES_H

#include "Board.h"

namespace Moves {
    // Pass by value as we want to modify the Board without altering the original
    bool is_valid_move(Square orig, Colour c, Square dest, MoveType t, Board board);

    MoveType infer_move_type(Square orig, Colour c, Square dest, Board b);
    Colour infer_player_colour(Square orig, Board b);

    Bitboard get_move_bitboard(Square s, Colour c, const Board& board);

    Bitboard king_move_bb   (Square s, Colour c, const Board& board);
    Bitboard queen_move_bb  (Square s, Colour c, const Board& board);
    Bitboard bishop_move_bb (Square s, Colour c, const Board& board);
    Bitboard knight_move_bb (Square s, Colour c, const Board& board);
    Bitboard rook_move_bb   (Square s, Colour c, const Board& board);
    Bitboard pawn_move_bb   (Square s, Colour c, const Board& board);
    Bitboard pawn_attack_bb (Square s, Colour c, const Board& board);

}
#endif
