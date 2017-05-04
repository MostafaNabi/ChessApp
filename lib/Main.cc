#include <string>
#include <iostream>
#include <algorithm>
#include "Chess.h"

using std::cin;
using std::cout;
using std::endl;


void singleplayer(int depth) {
    Chess chess(SINGLEPLAYER, depth);
    
    while(true) {
        cout << "Enter your move as follows: origin_square " << endl << "destination_square" << endl;
        int orig;
        cin >> orig;
        int dest;
        cin >> dest;
        
        Square s1 = Square(orig);
        Square s2 = Square(dest);
        Result r = chess.make_move(s1, s2);
        if(r == 0) {
            cout << "Invalid move" << endl;
            continue;
        }
        
        if(r == 2) {
            cout << "Pawn Promotion, Q(1), B(2), N(3), R(4)" << endl;
            int i;
            cin >> i;
            chess.promote_pawn(s2, Piece(i));
        }
        
        if(r == 3) {
            cout << "You put black in check" << endl;
        }
        
        if(r == 4) {
            cout << "You win!" << endl;
            return;
        }
        
        EvaluationResult er = chess.request_move();
        cout << "Black moves: " << er.move.origin << ", " << er.move.destination << endl;
        Result r2 = er.move_result;
        if(r2 == 3) {
            cout << "You are in check" << endl;
        }
        
        if(r2 == 4) {
            cout << "You lose!" << endl;
            return;
        }

    }
}

int perft(Board b, int depth) {
    if(depth == 0) {
        return 1;
    }
    int nodes = 0;
    std::vector<Move> all_moves = Moves::all_player_move_list(b.get_current_turn(), b);
    for(Move m: all_moves) {
        Board temp_b = b;
        temp_b.make_move(m);
        nodes += perft(temp_b, depth -1);
    }
    return nodes;
}

int main() {
    Chess chess(TWOPLAYER);
    cout << "Perft 1: " << perft(chess.board, 1) << endl;
    cout << "Perft 2: " << perft(chess.board, 2) << endl;
    cout << "Perft 3: " << perft(chess.board, 3) << endl;
    cout << "Perft 4: " << perft(chess.board, 4) << endl;
    singleplayer(3);
}



