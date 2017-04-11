#include <string>
#include <iostream>
#include <algorithm>
#include "Chess.h"

using std::cout;
using std::endl;

int main() {
    Chess chess(SINGLEPLAYER, 2);
    cout << "Moved 8,24: " << chess.make_move(SQ_8, SQ_24) << endl;
    cout << "Moved 0,16: " << chess.make_move(SQ_0, SQ_16) << endl;
    cout << "Moved 16,0: " << chess.make_move(SQ_16, SQ_0) << endl;

    std::vector<Piece> v = chess.retrieve_board();

    for(int i=0; i<v.size(); i++) {
        if(i % 8 == 0 && i !=0) {
            cout << endl;
        }
        if(v[i] < 10) { cout << "_";}
        cout << v[i] << ",";
    }
    cout << endl;
    return 0;
}
