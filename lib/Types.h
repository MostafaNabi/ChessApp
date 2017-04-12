#ifndef TYPES_H
#define TYPES_H

// Inspired by stockfish
#include <string>
enum GameType {
    SINGLEPLAYER = 1,
    TWOPLAYER = 2
};


enum Colour {
    BLACK = 0,
    WHITE = 1,
    COLOUR_NONE = 2
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
    SQ_56, SQ_57, SQ_58, SQ_59, SQ_60, SQ_61, SQ_62, SQ_63,
};

enum Direction {
    NORTH = 8, EAST = 1, SOUTH = -8, WEST = -1,
    NORTH_EAST = 9, NORTH_WEST = 7, SOUTH_EAST = -7, SOUTH_WEST = -9
};


namespace Types {
    extern const std::string DEFAULT_FEN;

    Colour get_piece_colour(Piece p);
    PieceType get_piece_type(Piece p);
    std::string remove_all_char(std::string s, char c);
    std::string replace_all_char(std::string s, char c, char n);
    std::string replace_all_char(std::string s, char c, std::string n);
}

#endif
