#include <string>
#include <iostream>
#include "Chess.h"

using std::cout;
using std::endl;

int main() {
    Bitboard bitb;
    Bitboard north = bitb.north(SQ_22);

    cout << "-North--" << endl;
    north.pretty_print();
    cout << "--------" << endl;

    cout << "-South--" << endl;
    Bitboard south = bitb.south(SQ_22);
    south.pretty_print();
    cout << "--------" << endl;

    cout << "--East--" << endl;
    Bitboard east = bitb.east(SQ_22);
    east.pretty_print();
    cout << "--------" << endl;
   
    cout << "--West--" << endl;
    Bitboard west = bitb.west(SQ_22);
    west.pretty_print();
    cout << "--------" << endl;

    return 0;
}