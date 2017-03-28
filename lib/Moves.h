#ifndef MOVES_H
#define MOVES_H

#include "Board.h"

namespace Moves {
    // Pass by value as we want to modify the Board without altering the original
    bool is_valid_move(Square orig, Colour c, Square dest, MoveType t, Board b);

    MoveType infer_move_type(Square orig, Colour c, Square dest, const Board& b);
    Colour infer_player_colour(Square orig, const Board& b);


    uint64_t king_move_bb   (Square s, Colour c, const Board& b);
    uint64_t queen_move_bb  (Square s, Colour c, const Board& b);
    uint64_t bishop_move_bb (Square s, Colour c, const Board& b);
    uint64_t knight_move_bb (Square s, Colour c, const Board& b);
    uint64_t rook_move_bb   (Square s, Colour c, const Board& b);
    uint64_t pawn_move_bb   (Square s, Colour c, const Board& b);
    uint64_t pawn_attack_bb (Square s, Colour c, const Board& b);





}
#endif
