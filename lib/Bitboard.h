#ifndef BITBOARD_H
#define BITBOARD_H


/*
 Rather than having a 64-bit integer, have an array storing 64 unsigned integers?
 Hmm do i really want to do this
 */

#include <stdexcept>
#include <stdint.h>
#include "Types.h"

class Bitboard {
public:
    // -------- Variables ----------
    uint64_t bb;

    static constexpr uint64_t Rank[8] = {
        0x00000000000000FF,
        0x000000000000FF00,
        0x0000000000FF0000,
        0x00000000FF000000,
        0x000000FF00000000,
        0x0000FF0000000000,
        0x00FF000000000000,
        0xFF00000000000000
    };

    static constexpr uint64_t File[8] = {
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
        // 0100 0000
    /*static constexpr uint64_t BitPositions[64] {
        0x0000000000000001, 0x0000000000000002, 0x0000000000000004, 0x0000000000000008, // 3
        0x0000000000000010, 0x0000000000000020, 0x0000000000000040, 0x0000000000000080, // 7
        0x0000000000000100, 0x0000000000000200, 0x0000000000000400, 0x0000000000000800, // 11,
        0x0000000000001000, 0x0000000000002000, 0x0000000000004000, 0x0000000000008000, // 15
        0x0000000000010000, 0x0000000000020000, 0x0000000000040000, 0x0000000000080000, // 19
        0x0000000000100000, 0x0000000000200000, 0x0000000000400000, 0x0000000000800000, // 23
        0x0000000001000000, 0x0000000002000000, 0x0000000004000000, 0x0000000008000000, // 27
        0x0000000010000000, 0x0000000020000000, 0x0000000040000000, 0x0000000080000000, // 31
        0x0000000100000000, 0x0000000200000000, 0x0000000400000000, 0x0000000800000000, // 35
        0x0000001000000000, 0x0000002000000000, 0x0000004000000000, 0x0000008000000000, // 39
        0x0000010000000000, 0x0000020000000000, 0x0000040000000000, 0x0000080000000000, // 43
        0x0000100000000000, 0x0000200000000000, 0x0000400000000000, 0x0000800000000000, // 47
        0x0001000000000000, 0x0002000000000000, 0x0004000000000000, 0x0008000000000000, // 51
        0x0010000000000000, 0x0020000000000000, 0x0040000000000000, 0x0080000000000000, // 55
        0x0100000000000000, 0x0200000000000000, 0x0400000000000000, 0x0800000000000000, // 59
        0x1000000000000000, 0x2000000000000000, 0x4000000000000000, 0x8000000000000000, // 63
    }
*/


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

    static Bitboard rank(uint r) {
        if(r > 7) {
            throw std::out_of_range ("Given rank is out of range");
        }
        return Bitboard(Rank[r]);
    }

    static Bitboard file(uint f) {
        if(f > 7) {
            throw std::out_of_range ("Given file is out of range");
        }
        return Bitboard(File[f]);
    }

    static unsigned int to_rank(Square s) {
        return (s / 8);
    }

    static unsigned int to_file(Square s) {
        return (s % 8);
    }

    static Bitboard north(Square s) {
        unsigned int file_index = Bitboard::to_file(s);
        Bitboard file_bb = Bitboard::file(file_index);

        unsigned int rank_index = Bitboard::to_rank(s);
        file_bb <<= 8*(rank_index+1);
        return file_bb;
    }

 
    static Bitboard south(Square s) {
        unsigned int file_index = Bitboard::to_file(s);
        Bitboard file_bb = Bitboard::file(file_index);

        unsigned int rank_index = Bitboard::to_rank(s);
        file_bb >>= 8*(7-rank_index+1);
        return file_bb;
    }

    /*
        Left shift the bits in the rank by the
        file the square is on + 1. Then intersect with the rank.
        The shifted bits will move onto a different rank so by interecting we
        remove them.
    */
    static Bitboard east(Square s) {
        unsigned int rank_index = Bitboard::to_rank(s);
        Bitboard rank_bb = Bitboard::rank(rank_index);

        unsigned int file_index = Bitboard::to_file(s);
        rank_bb <<= file_index+1;
        rank_bb &= Bitboard::rank(rank_index);
        return rank_bb;
    }

    /*
        Same thing as for east but right shift
    */
    static Bitboard west(Square s) {
        uint rank_index = Bitboard::to_rank(s);
        Bitboard rank_bb = Bitboard::rank(rank_index);

        uint file_index = Bitboard::to_file(s);
        rank_bb >>= (7-file_index+1);
        rank_bb &= Bitboard::rank(rank_index);
        return rank_bb; 
    }

    // Return bitboard with only the lsb set
    static Bitboard lsb(const Bitboard& b) {
        return Bitboard( ((~b.bb)+1) & b.bb );
    }

    // Return bitboard with only the lsb set
    static Bitboard msb(const Bitboard& b) {
        uint64_t msb = 1;
        unsigned int msb_index = Bitboard::msb_index(b);
        return Bitboard(msb << msb_index);
    }


    // Create new bitboard with only the lsb set
    // At this point the lsb is also the msb
    // 0-based index
    static unsigned int lsb_index(const Bitboard& b) {
        Bitboard lsb = Bitboard::lsb(b);
        return Bitboard::msb_index(lsb);
    }

    // Get position of the msb
    static unsigned int msb_index(const Bitboard& b) {
        Bitboard msb = b;
        unsigned int c = 0;
        while(msb > 1) {
            msb >>= 1;
            c++;
        }
        return c;
    }

    // Sets every bit <= the lsb in the given bitboard
    static Bitboard lsb_mask(unsigned int index) {
        if(index > 63) {
            throw std::out_of_range ("Bit index is 0-based up to 63");
        }
        uint64_t mask = 1;
        while(index > 0) {
            index--;
            mask |= mask << 1;
        }
        return Bitboard(mask);
    }

    // Sets every bit >= the msb in the given bitboard
    static Bitboard msb_mask(unsigned int index) {
        if(index > 63) {
            throw std::out_of_range ("Bit index is 0-based up to 63");
        }
        uint64_t mask = 0x8000000000000000;
        while(index > 0) {
            index--;
            mask |= mask >> 1;
        }
        return Bitboard(mask);
    }


    // ------- Boolean Operators --------------
    bool operator== (const Bitboard& b) const;
    bool operator== (unsigned int i) const;
    
    bool operator!= (const Bitboard& b) const;
    bool operator!= (unsigned int i) const;
    
    bool operator! () const;
    explicit operator bool() const;

    bool operator> (unsigned int i) const;
    bool operator> (const Bitboard& b) const;

    bool operator>= (unsigned int i) const;
    bool operator>= (const Bitboard& b) const;

    bool operator< (unsigned int i) const;
    bool operator< (const Bitboard& b) const;

    bool operator<= (unsigned int i) const;
    bool operator<= (const Bitboard& b) const;


    // ------- Bitboard Operators --------------
    Bitboard operator& (const Bitboard& b) const;
    void operator&= (const Bitboard& b);

    Bitboard operator| (const Bitboard& b) const;
    void operator|= (const Bitboard& b);

    Bitboard operator^ (const Bitboard& b) const;
    void operator^= (const Bitboard& b);

    Bitboard operator~ () const;

    Bitboard operator<< (unsigned int s);
    void operator<<= (unsigned int s);
    Bitboard operator>> (unsigned int s);
    void operator>>= (unsigned int s);


    // ------- Square Operators --------------
    Bitboard operator& (const Square s) const;
    void operator&= (const Square s);

    Bitboard operator| (const Square s) const;
    void operator|= (const Square s);

    Bitboard operator^ (const Square s) const;
    void operator^= (const Square s);

    void pretty_print();


private:
};
#endif
