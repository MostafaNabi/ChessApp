function Board() {
    this.white_king   = new ChessPiece(new Bitboard(0b00000000000000000000000000000000, 0b00000000000000000000000000010000), 'white', 'king');
    this.white_queen  = new ChessPiece(new Bitboard(0b00000000000000000000000000000000, 0b00000000000000000000000000001000), 'white', 'queen');
    this.white_bishop = new ChessPiece(new Bitboard(0b00000000000000000000000000000000, 0b00000000000000000000000000100100), 'white', 'bishop');
    this.white_knight = new ChessPiece(new Bitboard(0b00000000000000000000000000000000, 0b00000000000000000000000001000010), 'white', 'knight');
    this.white_rook   = new ChessPiece(new Bitboard(0b00000000000000000000000000000000, 0b00000000000000000000000010000001), 'white', 'rook');
    this.white_pawn   = new ChessPiece(new Bitboard(0b00000000000000000000000000000000, 0b00000000000000001111111100000000), 'white', 'pawn');

    this.black_king   = new ChessPiece(new Bitboard(0b00010000000000000000000000000000, 0b00000000000000000000000000000000), 'black', 'king');
    this.black_queen  = new ChessPiece(new Bitboard(0b00001000000000000000000000000000, 0b00000000000000000000000000000000), 'black', 'queen');
    this.black_bishop = new ChessPiece(new Bitboard(0b00100100000000000000000000000000, 0b00000000000000000000000000000000), 'black', 'bishop');
    this.black_knight = new ChessPiece(new Bitboard(0b01000010000000000000000000000000, 0b00000000000000000000000000000000), 'black', 'knight');
    this.black_rook   = new ChessPiece(new Bitboard(0b10000001000000000000000000000000, 0b00000000000000000000000000000000), 'black', 'rook');
    this.black_pawn   = new ChessPiece(new Bitboard(0b00000000111111110000000000000000, 0b00000000000000000000000000000000), 'black', 'pawn');
    
    this.current_turn = 'white';
}

Board.prototype.init = function() {

}


Board.prototype.move = function(srcx, srcy, destx, desty) {
    return true;
}


Board.prototype.getPieceAt = function(xpos, ypos) {
    var all = this.getAllPieces();
    var bb = convertToBitboard(xpos, ypos);
    for(var i=0; i<all.length; i++) {
           if(all[i].bitboard.match(bb)) {
                return all[i];
            }
    }
    return null;
}


Board.prototype.getAllPieces = function() {
    var arr = [this.white_king.copy(), this.white_queen.copy(), this.white_bishop.copy(),
               this.white_knight.copy(), this.white_rook.copy(), this.white_pawn.copy(),
               this.black_king.copy(), this.black_queen.copy(), this.black_bishop.copy(),
               this.black_knight.copy(), this.black_rook.copy(), this.black_pawn.copy()];
    return arr;
}

Board.prototype.getWhitePieces = function() {
    var arr = [this.white_king.copy(), this.white_queen.copy(). this.white_bishop.copy(),
               this.white_knight.copy(), this.white_rook.copy(), this.white_pawn.copy()]
    return arr;
}

Board.prototype.getBlackPieces = function() {
    var arr = [this.black_king.copy(), this.black_queen.copy(), this.black_bishop.copy(),
               this.black_knight.copy(), this.black_rook.copy(), this.black_pawn.copy()];
    return arr;
}
    

// Return a  copy of this object
Board.prototype.copy = function() {
    var board = new Board();
    board.white_king = this.white_king.copy();
    board.white_queen = this.white_queen.copy();
    board.white_bishop = this.white_bishop.copy();
    board.white_knight = this.white_knight.copy();
    board.white_rook = this.white_rook.copy();
    board.white_pawn = this.white_pawn.copy();
    board.black_king = this.black_king.copy();
    board.black_queen = this.black_queen.copy();
    board.black_bishop = this.black_bishop.copy();
    board.black_knight = this.black_knight.copy();
    board.black_rook = this.black_rook.copy();
    board.black_pawn = this.black_pawn.copy();
    board.current_turn = this.current_turn;
    board.selected_tile = this.selected_tile;
    return board;
}


// Bitwise and on all bitboard then convert to string
Board.prototype.draw = function(container_id) {
    $('#'+container_id).removeClass(function(i, c) {
        var matches = c.match('chess_piece[^\ ]+');
        if(matches != null) {
            return matches[0];
        }         
    });
    for(var y=0; y<8; y++) {
        for(var x=0; x<8; x++) {
            var piece = this.getPieceAt(x,y);
            if(piece == null) {continue;}
            var element = $('#'+container_id+' :nth-child('+(8-y)+')').find(':nth-child('+(x+1)+')');
            element.addClass('chess_piece_'+piece.colour+'_'+piece.type);
        }
    }
}



function Bitboard(high, low) {
    this.high = (high || 0b00000000000000000000000000000000) >>> 0;
    this.low  = (low  || 0b00000000000000000000000000000000) >>> 0;
}

Bitboard.prototype.and = function(bb) {
    var res_b = new Bitboard();
    res_b.high = (this.high & bb.high) >>> 0;
    res_b.low = (this.low & bb.low) >>> 0;
    return res_b
}

Bitboard.prototype.or = function(bb) {
    var res_b = new Bitboard();
    res_b.high = (this.high | bb.high) >>> 0;
    res_b.low = (this.low | bb.low) >>> 0;
    return res_b;
}

Bitboard.prototype.match = function(bb) {
    if((this.high & bb.high) >>> 0 > 0) {return true;}
    if((this.low & bb.low) >>> 0 > 0) {return true;}
    return false;
}

Bitboard.prototype.copy = function() {
    var bb = new Bitboard(this.high, this.low);
    return bb;
}



function ChessPiece(bb, colour, type) {
    this.bitboard = bb;
    this.colour = colour;
    this.type = type;
}

ChessPiece.prototype.copy = function() {
    var cp = new ChessPiece(this.bitboard.copy(), this.colour, this.type);
    return cp;
}








