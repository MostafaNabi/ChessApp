#include <stdexcept>
#include <iostream>
#include "Board.h"

typedef unsigned int uint;

// ------ Constructors -------------
Board::Board() {
    std::cout << "Called Board empty constructor" << std::endl;
    this->bitboards[0]  = Bitboard(0x0000000000000010); // White King
    this->bitboards[1]  = Bitboard(0x0000000000000008); // White Queen
    this->bitboards[2]  = Bitboard(0x0000000000000024); // White Bishop
    this->bitboards[3]  = Bitboard(0x0000000000000042); // White Knight
    this->bitboards[4]  = Bitboard(0x0000000000000081); // White Rook
    this->bitboards[5]  = Bitboard(0x000000000000FF00); // White Pawn

    this->bitboards[6]  = Bitboard(0x1000000000000000); // Black King
    this->bitboards[7]  = Bitboard(0x0800000000000000); // Black Queen
    this->bitboards[8]  = Bitboard(0x2400000000000000); // Black Bishop
    this->bitboards[9]  = Bitboard(0x4200000000000000); // Black Knight
    this->bitboards[10] = Bitboard(0x8100000000000000); // Black Rook
    this->bitboards[11] = Bitboard(0x00FF000000000000); // Black Pawn

    this->current_turn = WHITE;
    this->castling_rights |= WHITE_KING_CR;
    this->castling_rights |= WHITE_KINGSIDE_CR;
    this->castling_rights |= WHITE_QUEENSIDE_CR;
    this->castling_rights |= BLACK_KING_CR;
    this->castling_rights |= BLACK_KINGSIDE_CR;
    this->castling_rights |= BLACK_QUEENSIDE_CR;
}


// Copy and move constructors
Board::Board(const Board& other) {
    for(uint i=0; i<12; i++) {
        this->bitboards[i] = other.bitboards[i];
    }

    this->castling_rights = other.castling_rights;
}

Board::Board(Board&& other) {
    for(uint i=0; i<12; i++) {
        this->bitboards[i] = other.bitboards[i];
    }
    this->castling_rights = other.castling_rights;
}

// Destructor, no dynamic memory
Board::~Board() {

}

// ----Copy and Move Operators ---------
Board& Board::operator=(const Board& other) {
    if(&other != this) {
        for(uint i=0; i<12; i++) {
            this->bitboards[i] = other.bitboards[i];
        }
        this->castling_rights = other.castling_rights;
    }
    return *this;
}


Board& Board::operator=(Board&& other) {
    for(uint i=0; i<12; i++) {
        this->bitboards[i] = other.bitboards[i];
    }
    this->castling_rights = other.castling_rights;
    return *this;
}

// ------------- Board Operators ---------------------

void Board::update_turn() {
    this->current_turn = (this->current_turn == WHITE) ? BLACK : WHITE;
}

Piece Board::get_piece_at(Square s) const {
    for(int j=0; j<12; j++) {
        if( (this->bitboards[j] & s) > 0) {
            return (Piece)j;
        }
    }
    return PIECE_NONE;
}

Bitboard Board::get_board_for(Piece p) const {
    unsigned int index = (unsigned int)p;
    return this->bitboards[index];
}

void Board::set_board_for(Piece p, Bitboard b) {
    unsigned int index = (unsigned int)p;
    this->bitboards[index] = b;
}

Bitboard Board::all_white_bb() const {
    Bitboard bb;
    for(uint i=0; i<6; i++) {
        bb |= this->bitboards[i];
    }
    return bb;
}

Bitboard Board::all_black_bb() const {
    Bitboard bb;
    for(uint i=6; i<12; i++) {
        bb |= this->bitboards[i];
    }
    return bb;
}


void Board::move_piece(Move move) {
    this->set_castling_flags(move);
    Square orig = move.origin;
    Square dest = move.destination;
    Piece orig_piece = this->get_piece_at(orig);
    Piece dest_piece = this->get_piece_at(dest);
    
    Bitboard orig_piece_bb = this->get_board_for(orig_piece);
    orig_piece_bb ^= orig;
    orig_piece_bb ^= dest;
    this->set_board_for(orig_piece, orig_piece_bb);
    
    if(dest_piece != PIECE_NONE) {
        Bitboard dest_piece_bb = this->get_board_for(dest_piece);
        dest_piece_bb ^= dest;
        this->set_board_for(dest_piece, dest_piece_bb);
    }
}

void Board::castle(CastlingRights cr) {
    Colour col = (cr == WHITE_KINGSIDE_CR || cr == WHITE_QUEENSIDE_CR) ? WHITE : BLACK;
    Piece king = (col == WHITE) ? WHITE_KING : BLACK_KING;
    Piece rook = (col == WHITE) ? WHITE_ROOK : BLACK_ROOK;
    
    Bitboard king_bb = this->get_board_for(king);
    Bitboard rook_bb = this->get_board_for(rook);
    
    king_bb ^= king_bb;
    king_bb |= cr;
    
    if(cr == WHITE_KINGSIDE_CR) { rook_bb ^= SQ_7; rook_bb |= SQ_5; }
    else if(cr == WHITE_QUEENSIDE_CR) { rook_bb ^= SQ_0; rook_bb |= SQ_3; }
    else if(cr == BLACK_KINGSIDE_CR) { rook_bb ^= SQ_63; rook_bb |= SQ_61; }
    else if(cr == BLACK_QUEENSIDE_CR) {rook_bb ^= SQ_56; rook_bb |= SQ_59; }
    this->set_board_for(king, king_bb);
    this->set_board_for(rook, rook_bb);
    
    if(col == WHITE) { this->castling_rights ^= WHITE_KING_CR; }
    else { this->castling_rights ^= BLACK_KING_CR; }
    this->castling_rights ^= cr;
}


void Board::promote_pawn(Square s, Piece piece) {
    Piece orig_piece = this->get_piece_at(s);
    Bitboard orig_bb = this->get_board_for(orig_piece);
    orig_bb ^= s;
    this->set_board_for(orig_piece, orig_bb);
    
    Bitboard promoted_bb = this->get_board_for(piece);
    promoted_bb |= s;
    this->set_board_for(piece, promoted_bb);
}



void Board::set_castling_flags(Move move) {
    Piece p = this->get_piece_at(move.origin);
    
    if(p == WHITE_KING && (this->castling_rights & WHITE_KING_CR) != 0) {
        if( (this->castling_rights & WHITE_KING_CR) != 0) {
            this->castling_rights ^= WHITE_KING_CR;
        }
        
    } else if(p == WHITE_ROOK && move.origin == SQ_7) {
        if( (this->castling_rights & WHITE_KINGSIDE_CR) != 0) {
            this->castling_rights ^= WHITE_KINGSIDE_CR;
        }
        
    } else if(p == WHITE_ROOK && move.origin == SQ_0) {
        if( (this->castling_rights & WHITE_QUEENSIDE_CR) != 0) {
            this->castling_rights ^= WHITE_QUEENSIDE_CR;
        }
        
    } else if(p == BLACK_KING) {
        if( (this->castling_rights & BLACK_KING_CR) != 0) {
            this->castling_rights ^= BLACK_KING_CR;
        }
    } else if(p == BLACK_ROOK && move.origin == SQ_63) {
        if( (this->castling_rights & BLACK_KINGSIDE_CR) != 0) {
            this->castling_rights ^= BLACK_KINGSIDE_CR;
        }
        
    } else if(p == BLACK_ROOK && move.origin == SQ_56) {
        if( (this->castling_rights & BLACK_QUEENSIDE_CR) != 0) {
            this->castling_rights ^= BLACK_QUEENSIDE_CR;
        }
    }
}

Colour Board::infer_player_colour(Square orig) const {
    Piece p = this->get_piece_at(orig);
    return Types::get_piece_colour(p);
}


void Board::build_from_fen(std::string fen) {
    std::regex reg("(([KQBNRPkqbnrp\\/1-8]+)(\\ [bw]\\ )(-|[KQkq]+\\ )(-\\ |[a-h][1-8]\\ )(\\d+\\ )(\\d+))");
    std::smatch matches;
    bool res = std::regex_match(fen, matches, reg);
    if(!res) {
        throw std::invalid_argument("Invalid FEN string");
    }

    // Extract string matches
    std::string b_str = matches[2];
    b_str = Types::remove_all_char(b_str, ' ');

    std::string turn_str = matches[3];
    turn_str = Types::remove_all_char(turn_str, ' ');

    std::string castle_str = matches[4];
    castle_str = Types::remove_all_char(castle_str, ' ');

    std::string enpassant_str = matches[5];
    enpassant_str = Types::remove_all_char(enpassant_str, ' ');

    std::string halfmove_str = matches[6];
    halfmove_str = Types::remove_all_char(halfmove_str, ' ');

    std::string fullmove_str = matches[7];
    fullmove_str = Types::remove_all_char(fullmove_str, ' ');

    // convert to correct types and overwrite
    // reset board string be 64chars long
    b_str = Types::remove_all_char(b_str, '/');
    b_str = Types::replace_all_char(b_str, '1', "_");
    b_str = Types::replace_all_char(b_str, '2', "__");
    b_str = Types::replace_all_char(b_str, '3', "___");
    b_str = Types::replace_all_char(b_str, '4', "____");
    b_str = Types::replace_all_char(b_str, '5', "_____");
    b_str = Types::replace_all_char(b_str, '6', "______");
    b_str = Types::replace_all_char(b_str, '7', "_______");
    b_str = Types::replace_all_char(b_str, '8', "________");

    std::cout << "Extracted board     string: " << b_str << std::endl;
    std::cout << "Extracted turn      string: " << turn_str << std::endl;
    std::cout << "Extracted castle    string: " << castle_str << std::endl;
    std::cout << "Extracted enpassant string: " << enpassant_str << std::endl;
    std::cout << "Extracted halfmove  string: " << halfmove_str << std::endl;
    std::cout << "Extracted fullmove  string: " << fullmove_str << std::endl;

    uint64_t black_rook = 0;
    uint64_t black_knight = 0;
    uint64_t black_bishop = 0;
    uint64_t black_queen = 0;
    uint64_t black_king = 0;
    uint64_t black_pawn = 0;
    uint64_t white_rook = 0;
    uint64_t white_knight = 0;
    uint64_t white_bishop = 0;
    uint64_t white_queen = 0;
    uint64_t white_king = 0;
    uint64_t white_pawn = 0;

    int rank = 56;
    int file =  0;
    for(unsigned int i=0; i<b_str.size(); i++) {
        uint64_t one = 1;
        if( i % 8 == 0) {
            rank = 56 - (8*(i / 8));
        }
        file = (i % 8);
        if(b_str[i] == 'r') {
            black_rook |= (one << (rank + file));
            continue;
        }

        if(b_str[i] == 'n') {
            black_knight |= (one << (rank + file));
            continue;
        }

        if(b_str[i] == 'b') {
            black_bishop |= (one << (rank + file));
            continue;
        }
        if(b_str[i] == 'q') {
            black_queen |= (one << (rank + file));
            continue;
        }
        if(b_str[i] == 'k') {
            black_king |= (one << (rank + file));
            continue;
        }

        if(b_str[i] == 'p') {
            black_pawn |= (one << (rank + file));
            continue;
        }

        if(b_str[i] == 'R') {
            white_rook |= (1 << (rank + file));
            continue;
        }
        if(b_str[i] == 'N') {
            white_knight |= (one << (rank + file));
            continue;
        }
        if(b_str[i] == 'B') {
            white_bishop |= (one << (rank + file));
            continue;
        }
        if(b_str[i] == 'Q') {
            white_queen |= (one << (rank + file));
            continue;
        }
        if(b_str[i] == 'K') {
            white_king |= (one << (rank + file));
            continue;
        }
        if(b_str[i] == 'P') {
            white_pawn |= (one << (rank + file));
            continue;
        }
    }
    this->bitboards[0] = Bitboard(white_king);
    this->bitboards[1] = Bitboard(white_queen);
    this->bitboards[2] = Bitboard(white_bishop);
    this->bitboards[3] = Bitboard(white_knight);
    this->bitboards[4] = Bitboard(white_rook);
    this->bitboards[5] = Bitboard(white_pawn);

    this->bitboards[6] = Bitboard(black_king);
    this->bitboards[7] = Bitboard(black_queen);
    this->bitboards[8] = Bitboard(black_bishop);
    this->bitboards[9] = Bitboard(black_knight);
    this->bitboards[10] = Bitboard(black_rook);
    this->bitboards[11] = Bitboard(black_pawn);

    // parse turn
    if(turn_str == "w") {
        this->current_turn = WHITE;
    } else {
        this->current_turn = BLACK;
    }

    // reset castling rights
    this->castling_rights &= 0;
    this->castling_rights = SQ_4 | SQ_60;

    if(castle_str != "_") {
        for(unsigned int i=0; i<castle_str.size(); i++) {
            if(castle_str[i] == 'K') {
                this->castling_rights |= WHITE_KINGSIDE_CR;
                
            } else if(castle_str[i] == 'Q') {
                this->castling_rights |= WHITE_QUEENSIDE_CR;
                
            } else if(castle_str[i] == 'k') {
                this->castling_rights |= BLACK_KINGSIDE_CR;
                
            } else if(castle_str[i] == 'q') {
                this->castling_rights |= BLACK_QUEENSIDE_CR;
            }
        }
    }
    // ignore enpassant and the rest for now
}
