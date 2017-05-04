#include <string>
#include <iostream>
#include <algorithm>
#include "Chess.h"

// http://inst.eecs.berkeley.edu/~cs61b/fa14/ta-materials/apps/ab_tree_practice/


using std::cout;
using std::endl;

int main() {
    Chess chess(SINGLEPLAYER, 3);
    
    
    std::string fen = "rnb1k1nr/pppp1ppp/5q2/2b1p3/4P3/NP5P/P1PP1PP1/R1BQKBNR b KQkq - 7 4";
    chess.build_from_fen(fen);
    cout << chess.request_move().move_result << endl;
    }
