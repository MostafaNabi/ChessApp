#include <string>
#include <iostream>
#include <algorithm>
#include "Chess.h"

using std::cout;
using std::endl;

int main() {
    Chess chess(SINGLEPLAYER, 3);
  /*  cout << chess.board.current_turn << ": " << Evaluation::evaluate_board(chess.board) << endl;
    chess.make_move(SQ_12, SQ_28);
    cout << chess.board.current_turn << ": " << Evaluation::evaluate_board(chess.board) << endl;
    chess.make_move(SQ_53, SQ_37);
    cout << chess.board.current_turn << ": " << Evaluation::evaluate_board(chess.board) << endl;
    chess.make_move(SQ_3, SQ_30);
    cout << chess.board.current_turn << ": " << Evaluation::evaluate_board(chess.board) << endl;
    chess.make_move(SQ_37, SQ_30);
    cout << chess.board.current_turn << ": " << Evaluation::evaluate_board(chess.board) << endl;
    */
    while(true) {
        int s1;
        int  s2;
        cout << "White Move: " << endl;
        std::cin >> s1;
        std::cin >> s2;
        Result r = chess.make_move((Square) s1, Square(s2));
        if(r == 0) {cout << "Invalid move" << endl; continue;}
        cout << r << endl;
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
