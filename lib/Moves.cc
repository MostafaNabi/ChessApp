#include <stdexcept>
#include "Moves.h"

namespace Moves {
    bool is_valid_move(Square orig, Colour c, Square dest, MoveType t, Board b) {
            return false;
    }

    MoveType infer_move_type(Square orig, Colour c, Square dest, Board b) {
        return NORMAL;
    }

    Colour infer_player_colour(Square orig, Board b) {
        Piece p = b.get_piece_at(orig);
        return Types::get_piece_colour(p);
    }
}
