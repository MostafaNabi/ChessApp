#include <string>
#include <iostream>
#include <algorithm>
#include "Chess.h"

using std::cout;
using std::endl;

int main() {
    Chess chess(SINGLEPLAYER, 2);
    cout << "Moved 12,28: " << chess.make_move(SQ_12, SQ_28) << endl;
    cout << "Moved 63,15: " << chess.make_move(SQ_63, SQ_15) << endl; // ERROR
 
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
