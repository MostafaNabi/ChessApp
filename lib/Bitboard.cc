
#include <cstdint>
#include <stdexcept>
#include "Bitboard.h"
// ------ Constructors -------------
Bitboard::Bitboard() : Bitboard(0) {
}

Bitboard::Bitboard(uint64_t bb) {
    this->bb = bb;
}

Bitboard::Bitboard(const Bitboard& other) {
    this->bb = other.bb;
}

Bitboard::Bitboard(Bitboard && other) {
    this->bb = other.bb;
    other.bb = 0;
}

// ---------- Functions -------------
uint64_t Bitboard::rank(unsigned int r) {
    if(r > 7) {
        throw std::out_of_range ("Given rank is out of range");
    }
    return this->Rank[r];
}

uint64_t Bitboard::file(unsigned int f) {
    if(f > 7) {
        throw std::out_of_range ("Given file is out of range");
    }
    return this->File[f];
}

unsigned int Bitboard::to_rank(Square s) {
    return (s / 8);
}

unsigned int Bitboard::to_file(Square s) {
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
    unsigned int r = this->to_rank(s);
    unsigned int f = this->to_file(s);
    uint64_t rank_left_bb = 0;

    for(unsigned int i=f-1; i>0; i--) {
        rank_left_bb |= this->Rank[r] & this->File[i];
    }
    return (rank_left_bb & this->bb);
}

uint64_t Bitboard::rank_right(Square s) {
    unsigned int r = this->to_rank(s);
    unsigned int f = this->to_file(s);
    uint64_t rank_right_bb = 0;

    for(unsigned int i=f+1; i<8; i++) {
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
    unsigned int r = this->to_rank(s);
    unsigned int f = this->to_file(s);
    uint64_t file_infront_bb = 0;

    for(int i=r+1; i<8; i++) {
        file_infront_bb |= this->File[f] & this->Rank[i];
    }
    return (file_infront_bb & this->bb);
}

uint64_t Bitboard::file_behind(Square s) {
    unsigned int r = this->to_rank(s);
    unsigned int f = this->to_file(s);
    uint64_t file_infront_bb = 0;

    for(int i=r-1; i>0; i--) {
        file_infront_bb |= this->File[f] & this->Rank[i];
    }
    return (file_infront_bb & this->bb);
}

// ------------- Bitboard Operators ---------------------
const uint64_t Bitboard::operator& (Bitboard b) {
    return (this->bb & b.bb);
}

void Bitboard::operator&= (Bitboard b) {
    this->bb &= b.bb;
}

const uint64_t Bitboard::operator| (Bitboard b) {
    return (this->bb | b.bb);
}

void Bitboard::operator|= (Bitboard b) {
    this->bb |= b.bb;
}

const uint64_t Bitboard::operator^ (Bitboard b) {
    return (this->bb ^ b.bb);
}

void Bitboard::operator^= (Bitboard b) {
    this->bb ^= b.bb;
}

// ------------- Square Operators ---------------
const uint64_t operator& (const Square s) {
    return (this->bb & s);
}

void operator&= (const Square s) {
    this->bb &= s;
}

const uint64_t operator| (const Square s) {
    return (this->bb & s);
}

void operator|= (const Square s) {
    this->bb |= s;
}

const uint64_t operator^ (const Square s) {
    return (this->bb ^ s);
}

void operator^= (const Square s) {
        this->bb ^= s;
}
