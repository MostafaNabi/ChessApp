#ifndef TYPES_H
#define TYPES_H

// Inspired by stockfish
#include <string>

typedef unsigned int uint;

const std::string DEFAULT_FEN = std::string("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

enum Colour {
    BLACK,
    WHITE,
    COLOUR_NONE
};

enum PieceType {
    KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, PIECETYPE_NONE
};

enum Piece {
    W_KING, W_QUEEN, W_BISHOP, W_KNIGHT, W_ROOK, W_PAWN, // 0 - 5
    B_KING, B_QUEEN, B_BISHOP, B_KNIGHT, B_ROOK, B_PAWN,  // 6 - 11
    PIECE_NONE
};

enum MoveType {
    NORMAL, CASTLE, PROMOTION, ENPASSANT
};

enum CastlingSide {
    KINGSIDE = 1, QUEENSIDE = 2
};


enum Square {
    SQ_0,  SQ_1,  SQ_2,  SQ_3,  SQ_4,  SQ_5,  SQ_6,  SQ_7,
    SQ_8,  SQ_9,  SQ_10, SQ_11, SQ_12, SQ_13, SQ_14, SQ_15,
    SQ_16, SQ_17, SQ_18, SQ_19, SQ_20, SQ_21, SQ_22, SQ_23,
    SQ_24, SQ_25, SQ_26, SQ_27, SQ_28, SQ_29, SQ_30, SQ_31,
    SQ_32, SQ_33, SQ_34, SQ_35, SQ_36, SQ_37, SQ_38, SQ_39,
    SQ_40, SQ_41, SQ_42, SQ_43, SQ_44, SQ_45, SQ_46, SQ_47,
    SQ_48, SQ_49, SQ_50, SQ_51, SQ_52, SQ_53, SQ_54, SQ_55,
    SQ_56, SQ_57, SQ_58, SQ_59, SQ_60, SQ_61, SQ_62, SQ_63
};

enum Directions {
    NORTH = 8, EAST = 1, SOUTH = -8, WEST = -1,
    NORTH_EAST = 9, NORTH_WEST = 7, SOUTH_EAST = -7, SOUTH_WEST = -9
};


namespace Types {
    inline Colour get_piece_colour(Piece p) {
        uint i = (int)p;
        if(i < 6) {
            return WHITE;
        } else if(i > 5 || i < 12) {
            return BLACK;
        } else {
            return COLOUR_NONE;
        }
    }

    inline PieceType get_piece_type(Piece p) {
        uint i = (int)p;
        if(i == 0 || i == 6) {return KING;}
        if(i == 1 || i == 7) {return QUEEN;}
        if(i == 2 || i == 8) {return BISHOP;}
        if(i == 3 || i == 9) {return KNIGHT;}
        if(i == 4 || i == 10) {return ROOK;}
        if(i == 5 || i == 11) {return PAWN;}
        return PIECETYPE_NONE;
    }
}

#endif
