#include <string>
#include <iostream>
#include "Types.h"


int main() {

    std::string s("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    s = Types::remove_all_char(s, ' ');
    std::cout << s << std::endl;

}
