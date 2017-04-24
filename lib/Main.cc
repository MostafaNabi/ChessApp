#include <string>
#include <iostream>
#include <algorithm>
#include "Chess.h"

using std::cout;
using std::endl;

int main() {
    Chess chess(SINGLEPLAYER, 3);
    
    
    while(true) {
        int s1;
        int  s2;
        cout << "Player " << chess.board.get_current_turn() << " Move: " << endl;
        std::cin >> s1;
        std::cin >> s2;
        Result r = chess.make_move((Square) s1, Square(s2));
        if(r == 0) {cout << "Invalid move" << endl; continue;}
        cout << "Result: " << r << endl;
        if(r == CHECKMATE) {cout << "Checkmate!" << endl; break;}
        if(r == PROMOTE_PAWN) {
            cout << "Promote Pawn!" << endl;
            int p;
            std::cin >> p;
            chess.promote_pawn((Square) s2, (Piece)p);
        }
    cout << chess.request_move() << endl;
    }
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
