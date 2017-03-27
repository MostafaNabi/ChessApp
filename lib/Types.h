// Inspired by stockfish


enum Colour {
    WHITE,
    BLACK,
    NONE
};

enum PieceType {
    PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING
};

enum Piece {
  NO_PIECE,
  W_PAWN, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
  B_PAWN, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
};

enum MoveType {
    NORMAL, CASTLE, PROMOTION, ENPASSANT
};

enum CastlingSide {
    KINGSIDE, QUEENSIDE
};

enum CastlingRights {
    WHITE_KINGSIDE, WHITE_QUEENSIDE, BLACK_KINGSIDE, BLACK_QUEENSIDE
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

//MoveType should be known before move validation is performed
struct Move {
    Square origin;
    Square destination;
    MoveType type;

    Move(Square o, Square d, MoveType t) {
        this->origin = o;
        this->destination = d;
        this->type = t;
    }
};
