
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <bitset>
#include "Bitboard.h"

constexpr uint64_t Bitboard::Rank[];
constexpr uint64_t Bitboard::File[];
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

uint64_t Bitboard::bitboard() const {
    return this->bb;
}

// ------------- Bitboard Operators ---------------------
bool Bitboard::operator== (const Bitboard& b) const {
    return (this->bb == b.bb);
}

bool Bitboard::operator== (unsigned int i) const {
    return (this->bb == i);
}

bool Bitboard::operator!= (const Bitboard& b) const {
    return (this->bb != b.bb);
}

bool Bitboard::operator!= (unsigned int i) const {
    return (this->bb != i);
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
bool Bitboard::operator> (uint i) const {
    return (this->bb > i);
}

bool Bitboard::operator> (const Bitboard& b) const {
    return (this->bb > b.bb);
}

bool Bitboard::operator>= (uint i) const {
    return (this->bb >= i);
}

bool Bitboard::operator>= (const Bitboard& b) const {
    return (this->bb >= b.bb);
}

bool Bitboard::operator< (uint i) const {
    return (this->bb < i);
}

bool Bitboard::operator< (const Bitboard& b) const {
    return (this->bb < b.bb);
}

bool Bitboard::operator<= (uint i) const {
    return (this->bb <= i);
}

bool Bitboard::operator<= (const Bitboard& b) const {
    return (this->bb <= b.bb);
}


// ------------- Bitboard Operators ---------------
Bitboard Bitboard::operator& (const Bitboard& b) const {
    return Bitboard(this->bb & b.bb);
}

void Bitboard::operator&= (const Bitboard& b) {
    this->bb &= b.bb;
}

Bitboard Bitboard::operator| (const Bitboard& b) const {
    return Bitboard(this->bb | b.bb);
}

void Bitboard::operator|= (const Bitboard& b) {
    this->bb |= b.bb;
}

Bitboard Bitboard::operator^ (const Bitboard& b) const {
    return Bitboard(this->bb ^ b.bb);
}

void Bitboard::operator^= (const Bitboard& b) {
    this->bb ^= b.bb;
}

Bitboard Bitboard::operator~ () const {
    return Bitboard(~this->bb);
}

Bitboard Bitboard::operator<< (uint s) {
    uint64_t temp = this->bb;
    if(s >= 64) {
        temp = temp << 63;
        temp = temp << 1;
    } else {
        temp = temp << s;
    }
    return Bitboard(temp);
}

void Bitboard::operator<<= (uint s) {
    if(s >= 64) {
        this->bb = this->bb << 63;
        this->bb = this->bb << 1;
    } else {
        this->bb = this->bb << s;
    }
}

Bitboard Bitboard::operator>> (uint s) {
    uint64_t temp = this->bb;
    if(s >= 64) {
        temp = temp >> 63;
        temp = temp >> 1;
    } else {
        temp = temp >> s;
    }
    return Bitboard(temp);}

void Bitboard::operator>>= (uint s) {
   if(s >= 64) {
        this->bb = this->bb >> 63;
        this->bb = this->bb >> 1;
    } else {
        this->bb = this->bb >> s;
    }
}

// ------------- Square Operators ---------------
Bitboard Bitboard::operator& (Square s) const {
    uint64_t i = 1;
    uint64_t sb = i << (int)s;
    return Bitboard(this->bb & sb);
}

void Bitboard::operator&= (const Square s) {
    uint64_t i = 1;
    uint64_t sb = i << (int)s;
    this->bb &= sb;
}

Bitboard Bitboard::operator| (Square s) const {
    uint64_t i = 1;
    uint64_t sb = i << (int)s;
    return Bitboard(this->bb | sb);
}

void Bitboard::operator|= (Square s) {
    uint64_t i = 1;
    uint64_t sb = i << (int)s;
    this->bb |= sb;
}

Bitboard Bitboard::operator^ (Square s) const {
    uint64_t i = 1;
    uint64_t sb = i << (int)s;
    return Bitboard(this->bb ^ sb);
}

void Bitboard::operator^= (Square s) {
    uint64_t i = 1;
    uint64_t sb = i << (int)s;
    this->bb ^= sb;
}


// ------------- CastlingRights ---------------
Bitboard Bitboard::operator& (CastlingRights cr) const {
    uint64_t i = 1;
    uint64_t sb = i << (int)cr;
    return Bitboard(this->bb & sb);
}

void Bitboard::operator&= (const CastlingRights cr ) {
    uint64_t i = 1;
    uint64_t sb = i << (int)cr;
    this->bb &= sb;
}

Bitboard Bitboard::operator| (CastlingRights cr) const {
    uint64_t i = 1;
    uint64_t sb = i << (int)cr;
    return Bitboard(this->bb | sb);
}

void Bitboard::operator|= (CastlingRights cr) {
    uint64_t i = 1;
    uint64_t sb = i << (int)cr;
    this->bb |= sb;
}

Bitboard Bitboard::operator^ (CastlingRights cr) const {
    uint64_t i = 1;
    uint64_t sb = i << (int)cr;
    return Bitboard(this->bb ^ sb);
}

void Bitboard::operator^= (CastlingRights cr) {
    uint64_t i = 1;
    uint64_t sb = i << (int)cr;
    this->bb ^= sb;
}



void Bitboard::pretty_print() {
    std::cout << std::bitset<8>((this->bb & this->Bitboard::Rank[7]) >> 56) << std::endl;
    std::cout << std::bitset<8>((this->bb & this->Bitboard::Rank[6]) >> 48) << std::endl;
    std::cout << std::bitset<8>((this->bb & this->Bitboard::Rank[5]) >> 40) << std::endl;
    std::cout << std::bitset<8>((this->bb & this->Bitboard::Rank[4]) >> 32) << std::endl;
    std::cout << std::bitset<8>((this->bb & this->Bitboard::Rank[3]) >> 24) << std::endl;
    std::cout << std::bitset<8>((this->bb & this->Bitboard::Rank[2]) >> 16) << std::endl;
    std::cout << std::bitset<8>((this->bb & this->Bitboard::Rank[1]) >> 8) << std::endl;
    std::cout << std::bitset<8>((this->bb & this->Bitboard::Rank[0])) << std::endl;
}

    

