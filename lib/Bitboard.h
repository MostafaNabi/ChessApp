#ifndef BITBOARD_H
#define BITBOARD_H


/*
 Rather than having a 64-bit integer, have an array storing 64 unsigned integers?
 Hmm do i really want to do this
 */


#include <stdint.h>
#include "Types.h"

class Bitboard {
public:
    // -------- Variables ----------
    uint64_t bb;

    const uint64_t Rank[8] = {
        0x00000000000000FF,
        0x000000000000FF00,
        0x0000000000FF0000,
        0x00000000FF000000,
        0x000000FF00000000,
        0x0000FF0000000000,
        0x00FF000000000000,
        0xFF00000000000000
    };

    const uint64_t File[8] = {
        //    8765432187654321876543218765432187654321876543218765432187654321
        0x0101010101010101,
        0x0202020202020202,
        0x0404040404040404,
        0x0808080808080808,
        0x1010101010101010,
        0x2020202020202020,
        0x4040404040404040,
        0x8080808080808080
    };



    // ---- Constructors -----------
    Bitboard();
    Bitboard(uint64_t bb);

    // Copy and move constructors
    Bitboard(const Bitboard& other);
    Bitboard(Bitboard&& other);

    // Destructor
    ~Bitboard();

    // --------- Copy and Move Operators
    Bitboard& operator=(const Bitboard& other);
    Bitboard& operator=(Bitboard&& other);

    // ------- Functions -----------
    uint64_t bitboard();
    // Bitboard a bitboard representing the rank
    Bitboard rank(unsigned int r);
    Bitboard file(unsigned int f);

    unsigned int to_rank(Square s);
    unsigned int to_file(Square s);


    // ------- Bitboard Operators --------------
    bool operator== (const Bitboard b) const;
    bool operator!= (const Bitboard b) const;
    bool operator! () const;
    explicit operator bool() const;

    bool operator> (unsigned int i) const;
    bool operator> (const Bitboard b) const;

    bool operator>= (unsigned int i) const;
    bool operator>= (const Bitboard b) const;

    bool operator< (unsigned int i) const;
    bool operator< (const Bitboard b) const;

    bool operator<= (unsigned int i) const;
    bool operator<= (const Bitboard b) const;



    Bitboard operator& (const Bitboard b) const;
    void operator&= (const Bitboard b);

    Bitboard operator| (const Bitboard b) const;
    void operator|= (const Bitboard b);

    Bitboard operator^ (const Bitboard b) const;
    void operator^= (const Bitboard b);

    // ------- Square Operators --------------
    Bitboard operator& (const Square s) const;
    void operator&= (const Square s);

    Bitboard operator| (const Square s) const;
    void operator|= (const Square s);

    Bitboard operator^ (const Square s) const;
    void operator^= (const Square s);



private:
};
#endif
