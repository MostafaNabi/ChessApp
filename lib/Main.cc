#include <string>
#include <iostream>
#include <algorithm>
#include "Chess.h"

using std::cout;
using std::endl;

int main() {
    Chess chess(SINGLEPLAYER, 2);
    cout << "Moved 14, 30 = " << chess.make_move(SQ_14, SQ_30) << endl;
    cout << "Moved 53, 37 = " << chess.make_move(SQ_53, SQ_37) << endl;
    cout << "Moved 30, 38 = " << chess.make_move(SQ_30, SQ_38) << endl;
    cout << "Moved 37, 29 = " << chess.make_move(SQ_37, SQ_29) << endl;
    cout << "Moved 38, 46 = " << chess.make_move(SQ_38, SQ_46) << endl;
    cout << "Moved 29, 21 = " << chess.make_move(SQ_29, SQ_21) << endl;
    cout << "Moved 46, 55 = " << chess.make_move(SQ_46, SQ_55) << endl;
    cout << "Moved 21, 12 = " << chess.make_move(SQ_21, SQ_12) << endl;
    cout << "Moved 55, 62 = " << chess.make_move(SQ_55, SQ_62) << endl;
    std::vector<Piece> v = chess.retrieve_board();

    for(int i=0; i<v.size(); i++) {
        if(i % 8 == 0 && i !=0) {
            cout << endl;
        }
        if(v[i] < 10) { cout << "_";}
        cout << v[i] << ",";
    }


    return 0;
}
