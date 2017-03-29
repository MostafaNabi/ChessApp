#include <string>
#include <assert.h>
#include <iostream>
// #include "Types.h"
#include "Bitboard.h"

using std::cout;
using std::endl;

void types_tests() {

    // Test Types function
    Piece wk = W_KING;
    Piece wq = W_QUEEN;
    Piece wb = W_BISHOP;
    Piece wn = W_KNIGHT;
    Piece wr = W_ROOK;
    Piece wp = W_PAWN;

    assert(Types::get_piece_colour(wk) == WHITE);
    assert(Types::get_piece_colour(wq) == WHITE);
    assert(Types::get_piece_colour(wb) == WHITE);
    assert(Types::get_piece_colour(wn) == WHITE);
    assert(Types::get_piece_colour(wr) == WHITE);
    assert(Types::get_piece_colour(wp) == WHITE);

    cout << "All white get_piece_colour tests passed" << endl;

    assert(Types::get_piece_type(wk) == KING);
    assert(Types::get_piece_type(wq) == QUEEN);
    assert(Types::get_piece_type(wb) == BISHOP);
    assert(Types::get_piece_type(wn) == KNIGHT);
    assert(Types::get_piece_type(wr) == ROOK);
    assert(Types::get_piece_type(wp) == PAWN);

    cout << "All white get_piece_type tests passed" << endl;

    // black pices and string tests

    // Test Types function
    Piece bk = B_KING;
    Piece bq = B_QUEEN;
    Piece bb = B_BISHOP;
    Piece bn = B_KNIGHT;
    Piece br = B_ROOK;
    Piece bp = B_PAWN;
    Piece none = PIECE_NONE;

    assert(Types::get_piece_colour(bk) == BLACK);
    assert(Types::get_piece_colour(bq) == BLACK);
    assert(Types::get_piece_colour(bb) == BLACK);
    assert(Types::get_piece_colour(bn) == BLACK);
    assert(Types::get_piece_colour(br) == BLACK);
    assert(Types::get_piece_colour(bp) == BLACK);
    assert(Types::get_piece_colour(none) == COLOUR_NONE);


    cout << "All black and none get_piece_colour tests passed" << endl;

    assert(Types::get_piece_type(bk) == KING);
    assert(Types::get_piece_type(bq) == QUEEN);
    assert(Types::get_piece_type(bb) == BISHOP);
    assert(Types::get_piece_type(bn) == KNIGHT);
    assert(Types::get_piece_type(br) == ROOK);
    assert(Types::get_piece_type(bp) == PAWN);
    assert(Types::get_piece_type(none) == PIECETYPE_NONE);


    cout << "All black and none get_piece_type tests passed" << endl;

    std::string s = "The quick brown fox jumps over the lazy dog";
    s = Types::remove_all_char(s, 'o');
    s = Types::replace_all_char(s, ' ', '_');
    s = Types::replace_all_char(s, '_', "_space_");

    assert(s == "The_space_quick_space_brwn_space_fx_space_jumps_space_ver_space_the_space_lazy_space_dg");
    cout << "Replace and remove char tests passed" << endl;
}

void bitboard_tests() {
    cout << "Creating following bitboard: " << endl;
    cout << "00000000" << endl;
    cout << "00000000" << endl;
    cout << "00000000" << endl;
    cout << "00000000" << endl;
    cout << "000x1000" << endl;
    cout << "00010001" << endl;
    cout << "11100110" << endl;
    cout << "00000000" << endl;

    Bitboard b = Bitboard(0x0000000010886700);

    assert(b.bitboard() == 0x0000000010886700);
    assert(b.rank(0) == 0);
    assert(b.rank(1) == 0x6700);
    assert(b.rank(2) == 0x880000);
    assert(b.rank(3) == 0x10000000);
    assert(b.rank(4) == 0);
    assert(b.rank(5) == 0);
    assert(b.rank(6) == 0);
    assert(b.rank(7) == 0);

    cout << "All rank tests passed for bitboard" << endl;
    // 1000 0000 0000 0000 0000 0000 0000
    cout << "File 0: " << b.file(0) <<  endl;
    assert(b.file(0) == 0x0000000000000100);
    assert(b.file(1) == 0x0000000000000200);
    assert(b.file(2) == 0x0000000000000400);
    assert(b.file(3) == 0x0000000000080000);
    assert(b.file(4) == 0x0000000010000000);
    assert(b.file(5) == 0x0000000000002000);
    assert(b.file(6) == 0x0000000000004000);
    assert(b.file(7) == 0x0000000000800000);

    cout << "All file tests passed for bitboard" << endl;

    assert(b.rank_infront(SQ_10) == 0x880000);
    assert(b.rank_behind(SQ_10) == 0);
    assert(b.rank_left(SQ_10) == 0x300);
    assert(b.rank_right(SQ_10) == 0x6000);

    cout << "Rank front,behind, left and right passed" << endl;

    assert(b.file_infront(SQ_27) == 0);
    assert(b.file_behind(SQ_27) == 0x80000);
    assert(b.file_left(SQ_27) == 0x400);
    assert(b.file_right(SQ_27) == 0x10000000);

    cout << "File front,behind, left and right passed" << endl;

    Bitboard b2 = Bitboard(0xFF);
    Bitboard b3 = b2;

    // Copy operator
    assert(b2 == b3);

    cout << "Bitboard copy operator passed" << endl;
    Bitboard b4 = std::move(b3);

    assert(b4 == b2);
    cout << "Bitboard move operator passed" << endl;

    b4 &= 0x0F;
    assert(b4 == 0x0F);
    assert((b4 & b2) == 0x0F);
    assert((b4 | b2) == 0xFF);
    assert((b4 ^ b2) == 0xF0);

    b4 ^= b2;
    assert(b4 == 0xF0);

    b4 |= b2;
    assert(b4 == 0xFF);

    cout << "Bitboard AND, OR and NOR operator passed" << endl;
    assert((b4 & SQ_0) == 0x01);
    assert((b4 & SQ_1) == 0x02);
    assert((b4 | SQ_8) == 0x1FF);
    assert((b4 | SQ_63) == 0x80000000000000FF);

    b4 &= 0x1;
    assert(b4 == 1);
    b4 |= 2;
    assert(b4 == 3);
    assert((b4 ^ 2) == 1);
    b4 ^= 2;
    assert(b4 == 1);
    cout << "Bitboard Square  AND, OR and NOR operator passed" << endl;
}

void board_tests() {

}

void moves_tests() {

}

void chess_tests() {

}

int main() {
    types_tests();
    bitboard_tests();
}
