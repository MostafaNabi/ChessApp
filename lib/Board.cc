#include <stdexcept>
#include <iostream>
#include <string>
#include "Board.h"

typedef unsigned int uint;

// ------ Constructors -------------
Board::Board() {
    this->boards[0]  = Bitboard(0x0000000000000010); // White King
    this->boards[1]  = Bitboard(0x0000000000000008); // White Queen
    this->boards[2]  = Bitboard(0x0000000000000024); // White Bishop
    this->boards[3]  = Bitboard(0x0000000000000042); // White Knight
    this->boards[4]  = Bitboard(0x0000000000000081); // White Rook
    this->boards[5]  = Bitboard(0x000000000000FF00); // White Pawn

    this->boards[6]  = Bitboard(0x1000000000000000); // Black King
    this->boards[7]  = Bitboard(0x0800000000000000); // Black Queen
    this->boards[8]  = Bitboard(0x2400000000000000); // Black Bishop
    this->boards[9]  = Bitboard(0x4200000000000000); // Black Knight
    this->boards[10] = Bitboard(0x8100000000000000); // Black Rook
    this->boards[11] = Bitboard(0x00FF000000000000); // Black Pawn

    this->current_turn = WHITE;
    this->w_castle_rights = 3;
    this->b_castle_rights = 3;
}

Board::Board(std::string fen) {
    this->build_from_fen(fen);
}

void Board::build_from_fen(std::string fen) {
    std::regex reg("(([KQBNRPkqbnrp\\/[1-8]+)(\\ [bw]\\ )([-KQkq]+\\ )(- | [a-h][1-8]\\ )(\\d\\ )(\\d))");
    std::smatch matches;
    std::regex_match(fen, matches, reg);

    // Extract string matches
    std::string b_str = matches[1];
    std::string turn_str = matches[2];
    std::string castle_str = matches[3];
    std::string enpassant_str = matches[4];
    std::string halfmove_str = matches[5];
    std::string fullmove_str = matches[6];

    std::cout << "Extracted board     string: " << b_str << std::endl;
    std::cout << "Extracted turn      string: " << turn_str << std::endl;
    std::cout << "Extracted castle    string: " << castle_str << std::endl;
    std::cout << "Extracted enpassant string: " << enpassant_str << std::endl;
    std::cout << "Extracted halfmove  string: " << halfmove_str << std::endl;
    std::cout << "Extracted fullmove  string: " << fullmove_str << std::endl;


    // convert to correct types and overwrite
    // reset board string be 64chars long
    unsigned int end_i = 1;
    for(unsigned int i=0; i<b_str.size(); i++) {
        // set minimum range for substring
        if(i-1 > end_i) {
            end_i = i-1;
        }
        if(b_str[i] == '/') {
            b_str = b_str.substr(0, end_i) + b_str.substr(i+1);
        }

        if(b_str[i] == '1') {
            b_str[i] = '_';
            continue;
        }
        if(b_str[i] == '2') {
            b_str = b_str.substr(0, end_i) + std::string("__") + b_str.substr(i+1);
        }
        if(b_str[i] == '3') {
            b_str = b_str.substr(0, end_i) + std::string("___") + b_str.substr(i+1);
        }
        if(b_str[i] == '4') {
            b_str = b_str.substr(0, end_i) + std::string("____") + b_str.substr(i+1);
        }
        if(b_str[i] == '5') {
            b_str = b_str.substr(0, end_i) + std::string("_____") + b_str.substr(i+1);
        }
        if(b_str[i] == '6') {
            b_str = b_str.substr(0, end_i) + std::string("______") + b_str.substr(i+1);
        }
        if(b_str[i] == '7') {
            b_str = b_str.substr(0, end_i) + std::string("_______") + b_str.substr(i+1);
        }
        if(b_str[i] == '8') {
            b_str = b_str.substr(0, end_i) + std::string("________") + b_str.substr(i+1);
        }
    }
    std::cout << "completed parsing board string: " << b_str << std::endl;
    std::cout << "Board string lenth: " << b_str.size() << std::endl;



}

// Copy and move constructors
Board::Board(const Board& other) {
    for(uint i=0; i<12; i++) {
        this->boards[i] = other.boards[i];
    }

    this->w_castle_rights = other.w_castle_rights;
    this->b_castle_rights = other.b_castle_rights;
}

Board::Board(Board&& other) {
    for(uint i=0; i<12; i++) {
        this->boards[i] = other.boards[i];
    }
    this->w_castle_rights = other.w_castle_rights;
    this->b_castle_rights = other.b_castle_rights;
}

// Destructor, no dynamic memory
Board::~Board() {

}

// ----Copy and Move Operators ---------
Board& Board::operator=(const Board& other) {
    if(&other != this) {
        for(uint i=0; i<12; i++) {
            this->boards[i] = other.boards[i];
        }
        this->w_castle_rights = other.w_castle_rights;
        this->b_castle_rights = other.b_castle_rights;
    }
    return *this;
}


Board& Board::operator=(Board&& other) {
    for(uint i=0; i<12; i++) {
        this->boards[i] = other.boards[i];
    }
    this->w_castle_rights = other.w_castle_rights;
    this->b_castle_rights = other.b_castle_rights;
    return *this;
}

// ------------- Board Operators ---------------------
Piece Board::get_piece_at(Square s) const{
    uint bitpos = 1 << s;

    for(uint i=0; i<12; i++) {
        if(boards[i] & bitpos) {
            return (Piece)i;
        }
    }
    return PIECE_NONE;
}

bool Board::make_move(Square orig, Square dest, MoveType type) {
    return false;
}
