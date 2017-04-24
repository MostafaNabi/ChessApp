//
//  Evaluation.cpp
//  ChessXcode
//
//  Created by Mostafa Nabi on 17/04/2017.
//  Copyright © 2017 Mostafa Nabi. All rights reserved.
//
#include <iostream>
#include "Evaluation.h"


namespace Evaluation {
    
    
    double evaluate_board(const Board& board) {
        Colour opp_c = (board.get_current_turn() == WHITE) ? BLACK : WHITE;
        
        std::clock_t is_mate_dur = std::clock();
        if(Moves::is_in_checkmate(opp_c, board)) {
            return MAX;
        }
        double duration = ( std::clock() - is_mate_dur ) / (double) CLOCKS_PER_SEC;
   //     std::cout << "Time taken to is_in_checkmate: " << duration << "s" << std::endl;

        
        std::clock_t mat_eval_dur = std::clock();
        std::vector<Square> wk_pos = board.get_board_for(WHITE_KING).all_bit_indexes();
        std::vector<Square> wq_pos = board.get_board_for(WHITE_QUEEN).all_bit_indexes();
        std::vector<Square> wb_pos= board.get_board_for(WHITE_BISHOP).all_bit_indexes();
        std::vector<Square> wn_pos = board.get_board_for(WHITE_KNIGHT).all_bit_indexes();
        std::vector<Square> wr_pos = board.get_board_for(WHITE_ROOK).all_bit_indexes();
        std::vector<Square> wp_pos = board.get_board_for(WHITE_PAWN).all_bit_indexes();
        
        std::vector<Square> bk_pos = board.get_board_for(BLACK_KING).all_bit_indexes();
        std::vector<Square> bq_pos = board.get_board_for(BLACK_QUEEN).all_bit_indexes();
        std::vector<Square> bb_pos = board.get_board_for(BLACK_BISHOP).all_bit_indexes();
        std::vector<Square> bn_pos = board.get_board_for(BLACK_KNIGHT).all_bit_indexes();
        std::vector<Square> br_pos = board.get_board_for(BLACK_ROOK).all_bit_indexes();
        std::vector<Square> bp_pos = board.get_board_for(BLACK_PAWN).all_bit_indexes();
        
        
        // -------------------------- Material  Evaluation ----------------------------
        double king_eval = Evaluation::king_value(board) * (wk_pos.size() - bk_pos.size());
        double queen_eval = Evaluation::queen_value(board) * (wq_pos.size() - bq_pos.size());
        double bishop_eval = Evaluation::bishop_value(board) * (wb_pos.size() - bb_pos.size());
        double knight_eval = Evaluation::knight_value(board) * (wn_pos.size() - bn_pos.size());
        double rook_eval = Evaluation::rook_value(board) * (wr_pos.size() - br_pos.size());
        double pawn_eval = Evaluation::pawn_value(board) * (wp_pos.size() - bp_pos.size());
        double mat_eval = king_eval + queen_eval + bishop_eval + knight_eval + rook_eval + pawn_eval;

        double val = mat_eval * board.get_current_turn();
        
        duration = ( std::clock() - is_mate_dur ) / (double) CLOCKS_PER_SEC;
       // std::cout << "Time taken to material eval: " << duration << "s" << std::endl;
        
        // --------------------- White Mobility Eval -------------------------
        
        double white_mobil_eval = wk_pos.size() + wq_pos.size() + wb_pos.size() + wn_pos.size() + wr_pos.size() + wp_pos.size();
        
        for(Square s : wk_pos) {
            white_mobil_eval += Evaluation::WHITE_KING_OPENING_TABLE[(int)s];
        }
        
        for(Square s : wq_pos) {
            white_mobil_eval += Evaluation::WHITE_QUEEN_OPENING_TABLE[(int)s];
        }
        
        for(Square s : wb_pos) {
            white_mobil_eval += Evaluation::WHITE_BISHOP_OPENING_TABLE[(int)s];

        }
        
        for(Square s : wn_pos) {
            white_mobil_eval += Evaluation::WHITE_KNIGHT_OPENING_TABLE[(int)s];
        }
        
        for(Square s : wn_pos) {
            white_mobil_eval += Evaluation::WHITE_ROOK_OPENING_TABLE[(int)s];
        }
        
        for(Square s : wp_pos) {
            white_mobil_eval += Evaluation::WHITE_PAWN_OPENING_TABLE[(int)s];
        }
        
        // --------------------- Black Mobility Eval -------------------------
        double black_mobil_eval = bk_pos.size() + bq_pos.size() + bb_pos.size() + bn_pos.size() + br_pos.size() + bp_pos.size();
        
        for(Square s : bk_pos) {
            black_mobil_eval += Evaluation::BLACK_KING_OPENING_TABLE[(int)s];
        }
        
        for(Square s : bq_pos) {
            black_mobil_eval += Evaluation::BLACK_QUEEN_OPENING_TABLE[(int)s];
        }
        
        for(Square s : bb_pos) {
            black_mobil_eval += Evaluation::BLACK_BISHOP_OPENING_TABLE[(int)s];
        }
        
        for(Square s : bn_pos) {
            black_mobil_eval += Evaluation::BLACK_KNIGHT_OPENING_TABLE[(int)s];
        }
        
        for(Square s : br_pos) {
            black_mobil_eval += Evaluation::BLACK_ROOK_OPENING_TABLE[(int)s];
        }
        
        for(Square s : bp_pos) {
            black_mobil_eval += Evaluation::BLACK_PAWN_OPENING_TABLE[(int)s];
        }
        val += (white_mobil_eval - black_mobil_eval) * board.get_current_turn();
        
        if(Moves::is_in_check(opp_c, board)) {
            val += 200;
        }
        return val;
    }
    
    
    
    
    
    
    
    
    int king_value(const Board& b) {
        return Evaluation::KING_VALUE;
    }
    
    int queen_value(const Board& b) {
        return Evaluation::QUEEN_VALUE;;
    }
    
    int bishop_value(const Board& b) {
        return Evaluation::BISHOP_VALUE;;
    }
    
    int knight_value(const Board& b) {
        return Evaluation::KNIGHT_VALUE;;
    }
    
    int rook_value(const Board& b) {
        return Evaluation::ROOK_VALUE;;
    }
    
    int pawn_value(const Board& b) {
        return Evaluation::PAWN_VALUE;
    }
    
    NegamaxResult negamax(const Board& b, Move move, int depth) {
        // base case
        Colour opp_c = (b.get_current_turn() == WHITE) ? BLACK : WHITE;
        if(depth == 0) {
            double val = evaluate_board(b);
            return NegamaxResult(val, move);
        }
            
        // get all moves
        Move best_move;
        NegamaxResult best_result(MIN, Move());
        
        std::vector<Move> all_moves = Moves::all_player_move_list(b.get_current_turn(), b);
        for(Move m : all_moves) {
            Board temp = b;
            temp.make_move(m);
            NegamaxResult eval = negamax(temp, m, depth - 1);
            eval.evaluation *= -1;
            if(eval.evaluation > best_result.evaluation) {
                best_result = eval;
                best_result.move = m;
            }
        }
        return best_result;
    }


}
