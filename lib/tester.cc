#include <string>
#include <assert.h>
#include <iostream>
#include "Chess.h"


using std::cout;
using std::endl;

int main() {


    Square s = SQ_11;
    Square s2 = SQ_19;
    Chess chess(TWOPLAYER);
    chess.make_move(s, s2);

}
