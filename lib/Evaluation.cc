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
    int node_count = 0;

    
    double evaluate_board(const Board& board) {
        Colour opp_c = (board.get_current_turn() == WHITE) ? BLACK : WHITE;
        
        if(Moves::is_in_checkmate(board.get_current_turn(), board)) {
            return MIN;
        }
        
        if(Moves::is_in_checkmate(opp_c, board)) {
            return MAX;
        }
        
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
        double wk_num = wk_pos.size();
        double wq_num = wq_pos.size();
        double wb_num = wb_pos.size();
        double wn_num = wn_pos.size();
        double wr_num = wr_pos.size();
        double wp_num = wp_pos.size();

        double bk_num = bk_pos.size();
        double bq_num = bq_pos.size();
        double bb_num = bb_pos.size();
        double bn_num = bn_pos.size();
        double br_num = br_pos.size();
        double bp_num = bp_pos.size();
        
        
        
        double king_eval = Evaluation::king_value(board) * ( wk_num - bk_num);
        double queen_eval = Evaluation::queen_value(board) * (wq_num - bq_num);
        double bishop_eval = Evaluation::bishop_value(board) * (wb_num - bb_num);
        double knight_eval = Evaluation::knight_value(board) * (wn_num - bn_num);
        double rook_eval = Evaluation::rook_value(board) * (wr_num - br_num);
        double pawn_eval = Evaluation::pawn_value(board) * (wp_num - bp_num);
        double mat_eval = king_eval + queen_eval + bishop_eval + knight_eval + rook_eval + pawn_eval;
        
        double val = mat_eval * board.get_current_turn();
        
        // --------------------- White Mobility Eval -------------------------
        
        double white_mobil_eval = wk_pos.size() + wq_pos.size() + wb_pos.size() + wn_pos.size() + wr_pos.size() + wp_pos.size();
        if( !(board.castling_rights & WHITE_KING_CR)) {
            white_mobil_eval -= 200;
        }
        
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
        if( !(board.castling_rights & BLACK_KING_CR)) {
            black_mobil_eval -= 200;
        }
        
        
        
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
      
        if(board.get_current_turn() == WHITE) {
            val += white_mobil_eval;
        } else {
            val += black_mobil_eval;
        }
        
        if(Moves::is_in_check(opp_c, board)) {
            val -= 200;
        }
        
        if(Moves::is_in_check(opp_c, board)) {
            val += 100;
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
    
    EvaluationResult maxi(const Board& b, Move move, int depth, double alpha, double beta) {
        std::vector<Move> all_moves = Moves::all_player_move_list(b.get_current_turn(), b);

        if(depth == 0 || all_moves.size() == 0) {
            double evaluation = evaluate_board(b);
            node_count++;
            EvaluationResult r(evaluation, move);
            return r;
        }
        EvaluationResult best_result(MIN, move);

        for(Move m : all_moves) {
            Board temp_board = b;
            temp_board.make_move(m);
            
            EvaluationResult temp_result = mini(temp_board, m, depth - 1, alpha, beta);
         
            if(temp_result.evaluation >= beta) {
                return EvaluationResult(beta, move); // hard fail, this will never happen in the first level as beta = +infinity
            }
            
            if( temp_result.evaluation > alpha) {
                alpha = temp_result.evaluation;
            }
            
            if(temp_result.evaluation > best_result.evaluation) {
                best_result.evaluation = temp_result.evaluation;
                best_result.move = m;
                best_result.move_list = temp_result.move_list;
                best_result.move_list.push_back(m);
            }
            
            
        }
        return best_result;
    }
    
    EvaluationResult mini(const Board& b, Move move, int depth, double alpha, double beta) {
        std::vector<Move> all_moves = Moves::all_player_move_list(b.get_current_turn(), b);
        
        if(depth == 0 || all_moves.size() == 0) {
            double evaluation = evaluate_board(b);
            node_count++;
            EvaluationResult r(-1*evaluation, move);
            return r;
        }
        EvaluationResult best_result(MAX, move);
        
        for(Move m : all_moves) {
            Board temp_board = b;
            temp_board.make_move(m);
            
            EvaluationResult temp_result = maxi(temp_board, m, depth-1, alpha, beta);
            
            if(temp_result.evaluation <= alpha) { // If this result is worse than the lower bound Max
                return EvaluationResult(alpha, move); // has found we know he wont choose this so cut off.
            }                                     // In the first Mini search alpha = -infinity so this wont happen.
            
            if(temp_result.evaluation < beta) { // Try to find a result thats worse tha Max's upper bound
                beta = temp_result.evaluation;  // but better than his lower bound.
            }
            
            if(temp_result.evaluation < best_result.evaluation) {
                best_result.evaluation = temp_result.evaluation;
                best_result.move = m;
                best_result.move_list = temp_result.move_list;
                best_result.move_list.push_back(m);
            }
        }
        
        return best_result;
    }
    
    
    

}
