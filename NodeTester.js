// test.js
const ChessAddon = require('./build/Release/ChessAddon.node');


// ------------- Singleplayer Tests -----------

var s1 = new ChessAddon.WebInterface(1, 8);
var t1 = new ChessAddon.WebInterface(2);

//  Correct
s1.build_from_fen("rn1qkbnr/pp2p1pp/2p5/4p3/2BpP1Q1/8/PPPP1PPP/RNB1K2R b KQkq - 0 1");

// Correct
s1.set_ai_difficulty(6);

var moved  = s1.make_move(23, 40);
console.log('Moved should be false: ', moved);
