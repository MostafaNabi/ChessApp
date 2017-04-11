#include "Types.h"

namespace Types {

    const std::string DEFAULT_FEN = std::string("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    Colour get_piece_colour(Piece p) {
        unsigned int i = (int)p;
        if(i < 6) {
            return WHITE;
        } else if(i > 5 && i < 12) {
            return BLACK;
        } else {
            return COLOUR_NONE;
        }
    }

    PieceType get_piece_type(Piece p) {
        unsigned int i = (int)p;
        if(i == 0 || i == 6) {return KING;}
        if(i == 1 || i == 7) {return QUEEN;}
        if(i == 2 || i == 8) {return BISHOP;}
        if(i == 3 || i == 9) {return KNIGHT;}
        if(i == 4 || i == 10) {return ROOK;}
        if(i == 5 || i == 11) {return PAWN;}
        return PIECETYPE_NONE;
    }

    std::string remove_all_char(std::string s, char c) {
        while(s.find(c) != s.npos) {
            s.erase(s.find(c), 1);
        }
        return s;
    }

    std::string replace_all_char(std::string s, char c, char n) {
        for(unsigned int i=0; i<s.size(); i++) {
            if(s[i] == c) {
                s[i] = n;
            }
        }
        return s;
    }

    std::string replace_all_char(std::string s, char c, std::string n) {
        std::string s2("");
        for(unsigned int i=0; i<s.size(); i++) {
            if(s[i] == c) {
                s2 += n;
            } else {
                s2 += s[i];
            }
        }
        return s2;
    }
}
