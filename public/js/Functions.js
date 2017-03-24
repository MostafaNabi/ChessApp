function convertToPoint(bitpos) {
    var y = bitpos / 8;
    var x = bitpos % 8;
    return {'x:':x, 'y':y};
}

function convertToBitboard(x, y) {
    var bitpos = (8*y) + x;
    var bb = new Bitboard();
    if(bitpos > 32) {
        bitpos -= 32;
        bb.high = Math.pow(2, bitpos);
    } else {
        bb.low = Math.pow(2, bitpos);
    }
    return bb;
 }

