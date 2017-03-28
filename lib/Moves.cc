#include "Moves.h"
#include <stdexcept>

typedef unsigned int uint;

namespace Moves {
    bool is_valid_move(Square orig, Colour c, Square dest, MoveType t, Board& b) {
            return false;
    }

    MoveType infer_move_type(Square orig, Colour c, Square dest, Board& b) {
        return NORMAL;
    }

    Colour infer_player_colour(Square orig, const Board& b) {
        Piece p = b.get_piece_at(orig);
        return Types::get_piece_color(p);
    }
}
