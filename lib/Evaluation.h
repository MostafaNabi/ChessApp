//
//  Evaluation.hpp
//  ChessXcode
//
//  Created by Mostafa Nabi on 17/04/2017.
//  Copyright © 2017 Mostafa Nabi. All rights reserved.
//
// resources: http://stackoverflow.com/questions/17379849/simple-minimax-evaluation-function-for-chess-position
// https://www.quora.com/What-are-some-heuristics-for-quickly-evaluating-chess-positions
// https://chess.stackexchange.com/questions/347/what-is-an-accurate-way-to-evaluate-chess-positions
// http://chessprogramming.wikispaces.com/Piece-Square+Tables
// http://chessprogramming.wikispaces.com/Negamax



// Reference for piece value and piece value tables
// http://chessprogramming.wikispaces.com/Evaluation
// https://chessprogramming.wikispaces.com/Simplified+evaluation+function


#ifndef Evaluation_h
#define Evaluation_h

#include <limits>
#include "Moves.h"


namespace Evaluation {
    
    const int PAWN_VALUE = 100;
    const int KNIGHT_VALUE = 350;
    const int BISHOP_VALUE = 350;
    const int ROOK_VALUE = 525;
    const int QUEEN_VALUE = 1000;
    const int KING_VALUE = 10000;
    const int DEPTH = 5;
    const int MAX = std::numeric_limits<int>::max();
    const int MIN = std::numeric_limits<int>::min();

    /* pawn
     0,  0,  0,  0,  0,  0,  0,  0,
     50, 50, 50, 50, 50, 50, 50, 50,
    */
    
    
    /*
     rank 0: Encourage pawns to cover castling locations and mid pawns to move
     rank 1: Discourage pawns to leabe castling locations, encourage end pawns to move one
     square forward (escape route when castling)
     rank 2: Encourage pawns to take the center stage
     rank 3: Continue encouraging center pawns to go forward, but do not give any extra incentive for other pawns
     rank 4: Encourage all pawns to continue pushing forward.
     rank 5: Pawns are close to queening, encourage all pawns to press forward
     rank 6: Pawns are close to queening, encourage all pawns to press forward
     rank 7: No need for mobility functionto give queening bonus as it will be given by material evalutation.
    */
    static constexpr int WHITE_PAWN_OPENING_TABLE[64] = {
        0,  0,  0,  0,  0,  0,  0,  0, // rank 0
        5, 10, 10,-20,-20, 10, 10,  5, // rank 1
        5, -5,-10,  0,  0,-10, -5,  5, // rank 2
        0,  0,  0, 20, 20,  0,  0,  0, // rank 3
        5,  5, 10, 25, 25, 10,  5,  5, // rank 4
        10, 10, 20, 30, 30, 20, 10, 10, // rank 5
        50, 50, 50, 50, 50, 50, 50, 50, // rank 6
        0,  0,  0,  0,  0,  0,  0,  0, // rank 7
    };
    
    static constexpr int WHITE_KNIGHT_OPENING_TABLE[64] = {
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50
    };
    
    static constexpr int WHITE_BISHOP_OPENING_TABLE[64] = {
        -20,-10,-10,-10,-10,-10,-10,-20
        -10,  5,  0,  0,  0,  0,  5,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10,  0, 10, 10, 10, 10,  0,-10,
        -10,  5,  5, 10, 10,  5,  5,-10,
        -10,  0,  5, 10, 10,  5,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -20,-10,-10,-10,-10,-10,-10,-20
    };
    
    static constexpr int WHITE_ROOK_OPENING_TABLE[64] = {
         0,  0,  0,  5,  5,  0,  0,  0
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
         5, 10, 10, 10, 10, 10, 10,  5,
         0,  0,  0,  0,  0,  0,  0,  0,
    };
    
    
    
    static constexpr int WHITE_QUEEN_OPENING_TABLE[64] = {
        -20,-10,-10, -5, -5,-10,-10,-20
        -10,  0,  5,  0,  0,  0,  0,-10,
        -10,  5,  5,  5,  5,  5,  0,-10,
          0,  0,  5,  5,  5,  5,  0, -5,
         -5,  0,  5,  5,  5,  5,  0, -5,
        -10,  0,  5,  5,  5,  5,  0,-10,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
    };
    
    
    
    static constexpr int WHITE_KING_OPENING_TABLE[64] = {
         20, 30, 10,  0,  0, 10, 30, 20,
         20, 20,  0,  0,  0,  0, 20, 20,
        -10,-20,-20,-20,-20,-20,-20,-10,
        -20,-30,-30,-40,-40,-30,-30,-20,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30,
        -30,-40,-40,-50,-50,-40,-40,-30
    };
    
    
    static constexpr int BLACK_PAWN_OPENING_TABLE[64] = {
        0,  0,  0,  0,  0,  0,  0,  0, // rank 0
        50, 50, 50, 50, 50, 50, 50, 50, // rank 1
        10, 10, 20, 30, 30, 20, 10, 10, // rank 2
        5,  5, 10, 25, 25, 10,  5,  5, // rank 3
        0,  0,  0, 20, 20,  0,  0,  0, // rank 4
        5, -5,-10,  0,  0,-10, -5,  5, // rank 5
        5, 10, 10,-20,-20, 10, 10,  5, // rank 6
        0,  0,  0,  0,  0,  0,  0,  0, // rank 7
    };
    
    
    static constexpr int BLACK_KNIGHT_OPENING_TABLE[64] = {
        -50,-40,-30,-30,-30,-30,-40,-50,
        -40,-20,  0,  0,  0,  0,-20,-40,
        -30,  0, 10, 15, 15, 10,  0,-30,
        -30,  5, 15, 20, 20, 15,  5,-30,
        -30,  0, 15, 20, 20, 15,  0,-30,
        -30,  5, 10, 15, 15, 10,  5,-30,
        -40,-20,  0,  5,  5,  0,-20,-40,
        -50,-40,-30,-30,-30,-30,-40,-50
    };
    
    static constexpr int BLACK_BISHOP_OPENING_TABLE[64] = {
        -20,-10,-10,-10,-10,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5, 10, 10,  5,  0,-10,
        -10,  5,  5, 10, 10,  5,  5,-10,
        -10,  0, 10, 10, 10, 10,  0,-10,
        -10, 10, 10, 10, 10, 10, 10,-10,
        -10,  5,  0,  0,  0,  0,  5,-10,
        -20,-10,-10,-10,-10,-10,-10,-20
    };
    
    
    static constexpr int BLACK_ROOK_OPENING_TABLE[64] = {
         0,  0,  0,  0,  0,  0,  0,  0,
         5, 10, 10, 10, 10, 10, 10,  5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
        -5,  0,  0,  0,  0,  0,  0, -5,
         0,  0,  0,  5,  5,  0,  0,  0
    };
    
    
    static constexpr int BLACK_QUEEN_OPENING_TABLE[64] = {
        -20,-10,-10, -5, -5,-10,-10,-20,
        -10,  0,  0,  0,  0,  0,  0,-10,
        -10,  0,  5,  5,  5,  5,  0,-10,
         -5,  0,  5,  5,  5,  5,  0, -5,
          0,  0,  5,  5,  5,  5,  0, -5,
        -10,  5,  5,  5,  5,  5,  0,-10,
        -10,  0,  5,  0,  0,  0,  0,-10,
        -20,-10,-10, -5, -5,-10,-10,-20
    };
    
    
    static constexpr int BLACK_KING_OPENING_TABLE[64] = {
        -50,-40,-30,-20,-20,-30,-40,-50,
        -30,-20,-10,  0,  0,-10,-20,-30,
        -30,-10, 20, 30, 30, 20,-10,-30,
        -30,-10, 30, 40, 40, 30,-10,-30,
        -30,-10, 30, 40, 40, 30,-10,-30,
        -30,-10, 20, 30, 30, 20,-10,-30,
        -30,-30,  0,  0,  0,  0,-30,-30,
        -50,-30,-30,-30,-30,-30,-30,-50
    };

    
    double evaluate_board(const Board& board);
    double material_evaluation(const Board& board);
    double mobility_evaluation(const Board& board);

    
    // Use game state to modify fixed values
    int king_value(const Board& b);
    int queen_value(const Board& b);
    int bishop_value(const Board& b);
    int knight_value(const Board& b);
    int rook_value(const Board& b);
    int pawn_value(const Board& b);

    
    // Use game state to modify fixed values
    int pawn_mobility(Square s, const Board& b);
    
    NegamaxResult negamax(const Board& b, Move move, int depth);
    
    
}


#endif /* Evaluation_hpp */
