
#include <stdexcept>
#include "Bitboard.h"

typedef unsigned int uint;
// ------ Constructors -------------
Bitboard::Bitboard() : Bitboard(0) {
}

Bitboard::Bitboard(uint64_t bb) {
    this->bb = bb;
}

Bitboard::Bitboard(const Bitboard &other) {
    this->bb = other.bb;
}

Bitboard::Bitboard(Bitboard&& other) {
    this->bb = other.bb;
}

Bitboard::~Bitboard() {

}

// ------------- Copy and Move Operators ---------------
Bitboard& Bitboard::operator=(const Bitboard& other) {
    if(&other != this) {
        this->bb = other.bb;
    }
    return *this;
}


Bitboard& Bitboard::operator=(Bitboard&& other) {
    if(&other != this) {
        this->bb = other.bb;
    }
    return *this;
}

// ---------- Functions -------------
uint64_t Bitboard::rank(uint r) {
    if(r > 7) {
        throw std::out_of_range ("Given rank is out of range");
    }
    return this->Rank[r];
}

uint64_t Bitboard::file(uint f) {
    if(f > 7) {
        throw std::out_of_range ("Given file is out of range");
    }
    return this->File[f];
}

uint Bitboard::to_rank(Square s) {
    return (s / 8);
}

uint Bitboard::to_file(Square s) {
    return (s % 8);
}

// ----------------- Rank ----------------------------
uint64_t Bitboard::rank_infront(Square s) {
    return (this->bb & this->Rank[this->to_rank(s)+1]);
}

uint64_t Bitboard::rank_behind(Square s) {
    return (this->bb & this->Rank[this->to_rank(s)-1]);
}

// Get all files less than current file, BITWISE AND with
// current rank and BITWISE AND with bb
uint64_t Bitboard::rank_left(Square s) {
    uint r = this->to_rank(s);
    uint f = this->to_file(s);
    uint64_t rank_left_bb = 0;

    for(uint i=f-1; i>0; i--) {
        rank_left_bb |= this->Rank[r] & this->File[i];
    }
    return (rank_left_bb & this->bb);
}

uint64_t Bitboard::rank_right(Square s) {
    uint r = this->to_rank(s);
    uint f = this->to_file(s);
    uint64_t rank_right_bb = 0;

    for(uint i=f+1; i<8; i++) {
        rank_right_bb |= this->Rank[r] & this->File[i];
    }
    return (rank_right_bb & this->bb);
}

// ----------------- File ----------------------------
uint64_t Bitboard::file_right(Square s) {
    return (this->bb & this->File[this->to_file(s)+1]);
}

uint64_t Bitboard::file_left(Square s) {
    return (this->bb & this->File[this->to_file(s)-1]);
}

// Get all files ranks infront, BITWISE AND with
// current file and BITWISE AND with bb
uint64_t Bitboard::file_infront(Square s) {
    uint r = this->to_rank(s);
    uint f = this->to_file(s);
    uint64_t file_infront_bb = 0;

    for(uint i=r+1; i<8; i++) {
        file_infront_bb |= this->File[f] & this->Rank[i];
    }
    return (file_infront_bb & this->bb);
}

uint64_t Bitboard::file_behind(Square s) {
    uint r = this->to_rank(s);
    uint f = this->to_file(s);
    uint64_t file_infront_bb = 0;

    for(uint i=r-1; i>0; i--) {
        file_infront_bb |= this->File[f] & this->Rank[i];
    }
    return (file_infront_bb & this->bb);
}

// ------------- Bitboard Operators ---------------------
uint64_t Bitboard::operator& (Bitboard b) const {
    return (this->bb & b.bb);
}

void Bitboard::operator&= (Bitboard b) {
    this->bb &= b.bb;
}

uint64_t Bitboard::operator| (Bitboard b) const {
    return (this->bb | b.bb);
}

void Bitboard::operator|= (Bitboard b) {
    this->bb |= b.bb;
}

uint64_t Bitboard::operator^ (Bitboard b) const {
    return (this->bb ^ b.bb);
}

void Bitboard::operator^= (Bitboard b) {
    this->bb ^= b.bb;
}

// ------------- Square Operators ---------------
uint64_t Bitboard::operator& (const Square s) const {
    return (this->bb & s);
}

void Bitboard::operator&= (const Square s) {
    this->bb &= s;
}

uint64_t Bitboard::operator| (const Square s) const {
    return (this->bb & s);
}

void Bitboard::operator|= (const Square s) {
    this->bb |= s;
}

uint64_t Bitboard::operator^ (const Square s) const {
    return (this->bb ^ s);
}

void Bitboard::operator^= (const Square s) {
        this->bb ^= s;
}
