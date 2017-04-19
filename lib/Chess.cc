#include <stdexcept>
#include <iostream>
#include "Chess.h"

Chess::Chess(GameType g) {
    if(g == SINGLEPLAYER) {
        throw std::invalid_argument("Singleplayer games must be given an AI");
    }
    this->game_type = g;
}

Chess::Chess(GameType g, int ai) {
    if(g == TWOPLAYER) {
        throw std::invalid_argument("Twoplayer games cannot have an AI");
    }
    this->game_type = g;
    this->set_ai_difficulty(ai);
}

Chess::Chess(const Chess& other) {
    this->board = other.board;
    this->game_type = other.game_type;
}

Chess::Chess(Chess&& other) {
    this->board = std::move(other.board);
    this->game_type = other.game_type;
}

Chess& Chess::operator=(const Chess& other) {
    this->board = other.board;
    this->game_type = other.game_type;
    return *this;
}

Chess& Chess::operator=(Chess&& other) {
    this->board = std::move(other.board);
    this->game_type = other.game_type;
    return *this;
}

void Chess::build_from_fen(std::string fen) {
    this->board.build_from_fen(fen);
}

void Chess::set_ai_difficulty(int ai) {
    if(ai < 1 || ai > 10) {
        throw std::invalid_argument("AI difficulty must be between 1 and 10");
    }
    this->depth = ai;
    // set AI
}


Result Chess::request_move() {
    if(this->game_type != SINGLEPLAYER) {
        throw std::logic_error("Cannot request if not singleplayer");
    }
    
    std::clock_t start = std::clock();

    
    
    if(this->board.get_current_turn() == BLACK) {
        std::cout << "Black is thinking..." << std::endl;
    }
    else {
        std::cout << "White is thinking..." << std::endl;
    }
    
    Move best_move;
    double best_eval = INT_MIN;
    std::vector<Move> move_list = Moves::all_player_move_list(this->board.get_current_turn(), this->board);
    for(Move m : move_list) {
        Board temp = this->board;
        temp.make_move(m);
        double eval = Evaluation::negamax(temp, this->depth);
        if(eval > best_eval) {
            best_move = m;
            best_eval = eval;
        }
    }
    double duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout << "Made move (" << best_move.origin << "," << best_move.destination << ") in " << duration <<  std::endl;

    
    return this->make_move(best_move.origin, best_move.destination);
}


Result Chess::make_move(Square orig, Square dest) {
    Colour c = this->board.get_current_turn();
    if(Moves::is_in_checkmate(c, this->board)) {
        return INVALID_MOVE;
    }
    Move move = Move(orig, dest);
    MoveType move_type = Moves::infer_move_type(move, this->board);
    
    bool is_valid = Moves::is_valid_move(move, this->board);
    if(!is_valid) {
        return INVALID_MOVE;
    }
    
    board.make_move(move);
    
    if(move_type == PAWN_PROMOTION) {
        return PROMOTE_PAWN;
        
    } else if(Moves::is_in_checkmate(Colour(c*-1), board)) {
        return CHECKMATE;
        
    } else if(Moves::is_in_check(Colour(c*-1), this->board)) {
        return CHECK;
        
    } else {
        return VALID_MOVE;
    }
}


// Given the square the pawn is on after having been moved,
// Do another check and then promote it to the given piece
bool Chess::promote_pawn(Square s, Piece piece) {
    if(!Moves::can_promote_pawn(s, this->board)) {
        return false;
    }
    
    PieceType type = Types::get_piece_type(piece);
    if(type == PIECETYPE_NONE || type == PAWN) {
        return false;
    }
    
    this->board.promote_pawn(s, piece);
    return true;
}



std::vector<Piece> Chess::retrieve_board() {
    std::vector<Piece> v;

    for(int i=0; i<64; i++) {
        Square s = (Square)i;
        Piece p = this->board.get_piece_at(s);
        v.push_back(p);
    }
    return v;
}
