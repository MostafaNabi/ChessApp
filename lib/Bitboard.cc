
#include <stdexcept>
#include <iostream>
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
