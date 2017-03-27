/*
 Rather than having a 64-bit integer, have an array storing 64 unsigned integers?
 Hmm do i really want to do this
*/

#include <cstdint>
#include "Types.h"

class Bitboard {
    public:
        // -------- Variables ----------
        uint64_t bb;
        const uint64_t Rank[8] = {
                0b0000000000000000000000000000000000000000000000000000000011111111,
                0b0000000000000000000000000000000000000000000000001111111100000000,
                0b0000000000000000000000000000000000000000111111110000000000000000,
                0b0000000000000000000000000000000011111111000000000000000000000000,
                0b0000000000000000000000001111111100000000000000000000000000000000,
                0b0000000000000000111111110000000000000000000000000000000000000000,
                0b0000000011111111000000000000000000000000000000000000000000000000,
                0b1111111100000000000000000000000000000000000000000000000000000000
            };

        const uint64_t File[8] = {
            //    8765432187654321876543218765432187654321876543218765432187654321
                0b0000000100000001000000010000000100000001000000010000000100000001,
                0b0000001000000010000000100000001000000010000000100000001000000010,
                0b0000010000000100000001000000010000000100000001000000010000000100,
                0b0000100000001000000010000000100000001000000010000000100000001000,
                0b0001000000010000000100000001000000010000000100000001000000010000,
                0b0010000000100000001000000010000000100000001000000010000000100000,
                0b0100000001000000010000000100000001000000010000000100000001000000,
                0b1000000010000000100000001000000010000000100000001000000010000000
            };



        // ---- Constructors -----------
        Bitboard();
        Bitboard(uint64_t bb);

        // Copy and move constructors
        Bitboard(const Bitboard&);
        Bitboard(Bitboard &&);

        // Destructor
        ~Bitboard();

        // ------- Functions -----------
        uint64_t rank(unsigned int r);
        uint64_t file(unsigned int f);

        unsigned int to_rank(Square s);
        unsigned int to_file(Square s);

        uint64_t rank_infront(Square s);
        uint64_t rank_behind(Square s);
        uint64_t rank_left(Square s);
        uint64_t rank_right(Square s);

        uint64_t file_right(Square s);
        uint64_t file_left(Square s);
        uint64_t file_infront(Square s);
        uint64_t file_behind(Square s);

        // ------- Bitboard Operators --------------
        const uint64_t operator&  (const Bitboard b);
        void     operator&= (const Bitboard b);

        const uint64_t operator|  (const Bitboard b);
        void     operator|= (const Bitboard b);

        const uint64_t operator^  (const Bitboard b);
        void     operator^= (const Bitboard b);

        // ------- Square Operators --------------
        const uint64_t operator&  (const Square s);
        void           operator&= (const Square s);

        const uint64_t operator|  (const Square s);
        void           operator|= (const Square s);

        const uint64_t operator^  (const Square s);
        void           operator^= (const Square s);




    private:
};
