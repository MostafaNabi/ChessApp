
#include <stdexcept>
#include <iostream>
#include <algorithm>
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

uint64_t Bitboard::bitboard() {
    return this->bb;
}

Bitboard Bitboard::rank(uint r) {
    if(r > 7) {
        throw std::out_of_range ("Given rank is out of range");
    }
    return Bitboard(this->Rank[r]);
}

Bitboard Bitboard::file(uint f) {
    if(f > 7) {
        throw std::out_of_range ("Given file is out of range");
    }
    return Bitboard(this->File[f]);
}

uint Bitboard::to_rank(Square s) {
    return (s / 8);
}

uint Bitboard::to_file(Square s) {
    return (s % 8);
}

/*
    Left shift the file for the (rank the square is on + 1) * 8
    to remove the square the rank is one. The bits will fall of the
    bitboard due to overflow. E.g. get bits north of square 22
    00000010  00000010
    00000010  00000010
    00000010  00000010
    00000010  00000010
    00000010  00000010
    000000x0  00000000
    00000010  00000000
    00000010  00000000
*/

Bitboard Bitboard::north(Square s) {
    uint file_index = this->to_file(s);
    Bitboard file_bb = this->file(file_index);

    uint rank_index = this->to_rank(s);
    file_bb <<= (8*(rank_index+1));
    return file_bb;
}

/*
    Same thing as for north but right shift
*/
Bitboard Bitboard::south(Square s) {
   // Bitboard b = this->north(s);
   // return ((~b & this->file(this->to_file(s))) ^ s);

    uint file_index = this->to_file(s);
    Bitboard file_bb = this->file(file_index);

    uint rank_index = this->to_rank(s);
    file_bb >>= (8*(7-rank_index+1));
    return file_bb;
   
}

/*
    Left shift the bits in the rank by the
    file the square is on + 1. Then intersect with the rank.
    The shifted bits will move onto a different rank so by interecting we
    remove them.
*/
Bitboard Bitboard::east(Square s) {
    uint rank_index = this->to_rank(s);
    Bitboard rank_bb = this->rank(rank_index);
    uint file_index = this->to_file(s);
    rank_bb <<= (file_index+1);
    rank_bb &= this->rank(rank_index);
    return rank_bb;
}

/*
    Same thing as for east but right shift
*/
Bitboard Bitboard::west(Square s) {
    uint rank_index = this->to_rank(s);
    Bitboard rank_bb = this->rank(rank_index);
    uint file_index = this->to_file(s);
    rank_bb >>= (7-file_index+1);
    rank_bb &= this->rank(rank_index);
    return rank_bb;
}


// ------------- Bitboard Operators ---------------------
bool Bitboard::operator== (Bitboard b) const {
    return (this->bb == b.bb);
}

bool Bitboard::operator!= (Bitboard b) const {
    return (this->bb != b.bb);
}


bool Bitboard::operator! () const {
    if(this->bb == 0) {
        return true;
    } else {
        return false;
    }
}


Bitboard::operator bool() const {
    if(this->bb == 0) {
        return false;
    } else {
        return true;
    }
}

// ------------- Boolean Operators ---------------
bool Bitboard::operator> (unsigned int i) const {
    return (this->bb > i);
}

bool Bitboard::operator> (const Bitboard b) const {
    return (this->bb > b.bb);
}

bool Bitboard::operator>= (unsigned int i) const {
    return (this->bb >= i);
}

bool Bitboard::operator>= (const Bitboard b) const {
    return (this->bb >= b.bb);
}

bool Bitboard::operator< (unsigned int i) const {
    return (this->bb < i);
}

bool Bitboard::operator< (const Bitboard b) const {
    return (this->bb < b.bb);
}

bool Bitboard::operator<= (unsigned int i) const {
    return (this->bb <= i);
}

bool Bitboard::operator<= (const Bitboard b) const {
    return (this->bb <= b.bb);
}


// ------------- Bitboard Operators ---------------
Bitboard Bitboard::operator& (Bitboard b) const {
    return Bitboard(this->bb & b.bb);
}

void Bitboard::operator&= (Bitboard b) {
    this->bb &= b.bb;
}

Bitboard Bitboard::operator| (Bitboard b) const {
    return Bitboard(this->bb | b.bb);
}

void Bitboard::operator|= (Bitboard b) {
    this->bb |= b.bb;
}

Bitboard Bitboard::operator^ (Bitboard b) const {
    return Bitboard(this->bb ^ b.bb);
}

void Bitboard::operator^= (Bitboard b) {
    this->bb ^= b.bb;
}

Bitboard Bitboard::operator~ () const {
    return Bitboard(~this->bb);
}

Bitboard Bitboard::operator<< (int s) {
    return Bitboard(this->bb << s);
}

void Bitboard::operator<<= (int s) {
    this->bb = this->bb << s;
}

Bitboard Bitboard::operator>> (int s) {
    return Bitboard(this->bb >> s);
}

void Bitboard::operator>>= (int s) {
    this->bb = this->bb >> s;
}

// ------------- Square Operators ---------------
Bitboard Bitboard::operator& (const Square s) const {
    uint64_t i = 1;
    uint64_t sb = i << (int)s;
    return Bitboard(this->bb & sb);
}

void Bitboard::operator&= (const Square s) {
    uint64_t i = 1;
    uint64_t sb = i << (int)s;
    this->bb &= sb;
}

Bitboard Bitboard::operator| (const Square s) const {
    uint64_t i = 1;
    uint64_t sb = i << (int)s;
    std::cout << sb << " " << (int)s << std::endl;
    return Bitboard(this->bb | sb);
}

void Bitboard::operator|= (const Square s) {
    uint64_t i = 1;
    uint64_t sb = i << (int)s;
    this->bb |= sb;
}

Bitboard Bitboard::operator^ (const Square s) const {
    uint64_t i = 1;
    uint64_t sb = i << (int)s;
    return Bitboard(this->bb ^ sb);
}

void Bitboard::operator^= (const Square s) {
    uint64_t i = 1;
    uint64_t sb = i << (int)s;
    this->bb ^= sb;
}

void Bitboard::pretty_print() {
    std::cout << std::bitset<8>((this->bb & this->Rank[7]) >> 56) << std::endl;
    std::cout << std::bitset<8>((this->bb & this->Rank[6]) >> 48) << std::endl;
    std::cout << std::bitset<8>((this->bb & this->Rank[5]) >> 40) << std::endl;
    std::cout << std::bitset<8>((this->bb & this->Rank[4]) >> 32) << std::endl;
    std::cout << std::bitset<8>((this->bb & this->Rank[3]) >> 24) << std::endl;
    std::cout << std::bitset<8>((this->bb & this->Rank[2]) >> 16) << std::endl;
    std::cout << std::bitset<8>((this->bb & this->Rank[1]) >> 8) << std::endl;
    std::cout << std::bitset<8>((this->bb & this->Rank[0])) << std::endl;
}

    

