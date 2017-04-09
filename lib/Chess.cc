#include <stdexcept>
#include <iostream>
#include "Chess.h"

typedef unsigned int uint;


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
    // set AI
}

bool Chess::make_move(Square orig, Square dest) {
    // Determine move type
    Colour col = Moves::infer_player_colour(orig, this->board);
    MoveType type = Moves::infer_move_type(orig, col, dest, this->board);

    // Validate move
    bool is_valid = Moves::is_valid_move(orig, col, dest, type, this->board);
    std::cout << "Is valid: " << is_valid << std::endl;
    if(is_valid) {
        return this->board.make_move(orig, dest, type);
    } else {
        return false;
    }
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
