
ChessLogic.isValidMove = function(srcx, srcy, destx, desty, colour, board) {
    if(srcx == srcy && destx == desty) {return null}

    // src piece
    var src_piece = board.getPieceAt(srcx, srcy);
    var dest_piece = board.getPieceAt(destx, desty);

    if(src_piece.colour != board.current_turn) {
        return null;
    }

    var move_bb;
    if(dest_piece != null) {
        move_bb = this.getAttackBitboard(x, y, board);
    } else {
        move_bb = this.getMoveBitboard(x, y, board);
    }

    var dest_bb = convertToBinary(destx, desty);
    return move_bb.match(dest_bb);
}


ChessLogic.getMoveBitboard = function(x, y, board) {
    var p = board.getPieceAt(x, y);
    switch(p.type) {
        case 'king'  : return ChessLogic.kingMoveBitboard(p.x, p.y, board); break;
        case 'queen' : return ChessLogic.queenMoveBitboard(p.x, p.y, board); break;
        case 'bishop': return ChessLogic.bishopMoveBitboard(p.x, p.y, board); break;
        case 'knight': return ChessLogic.knightMoveBitboard(p.x, p.y, board); break;
        case 'rook'  : return ChessLogic.rookMoveBitboard(p.x, p.y, board); break;
        case 'pawn'  : return ChessLogic.pawnMoveBitboard(p.x, p.y, board); break;
    }
}


ChessLogic.getAttackBitboard = function(x, y, board) {
    var p = board.getPieceAt(x, y);
    switch(p.type) {
        case 'king'  : return ChessLogic.kingMoveBitboard(p.x, p.y, board); break;
        case 'queen' : return ChessLogic.queenMoveBitboard(p.x, p.y, board); break;
        case 'bishop': return ChessLogic.bishopMoveBitboard(p.x, p.y, board); break;
        case 'knight': return ChessLogic.knightMoveBitboard(p.x, p.y, board); break;
        case 'rook'  : return ChessLogic.rookMoveBitboard(p.x, p.y, board); break;
        case 'pawn'  : return ChessLogic.pawnAttackBitboard(p.x, p.y, board); break;
    }
}

/*
    Squares a king could move to if it was in the given position in the given board.
    Not including its current position
*/
ChessLogic.getKingMoveBitboard = function(srcx, srcy, colour, board) -> uint64 {
    let curr_bb = convertToBinary(x: pos.x, y: pos.y);
    var move_bb = 0;

    // king can go one square forwards and backwards. Overflow takes care of
    // situations where the piece goes over the edge.
    move_bb = move_bb | curr_pos_bb << 8 | curr_pos_bb >> 8;

    // King can go one square left and right and hence cannot be on the edge.
    if(pos.x < 7) {
        move_bb = move_bb | curr_pos_bb << 9 | curr_pos_bb << 1 | curr_pos_bb >> 7;
    }

    if(pos.x > 0) {
        move_bb = move_bb | curr_pos_bb << 7 | curr_pos_bb >> 1 | curr_pos_bb >> 9;
    }

    // remove squares taken up by same colour pieces
    let same_bb = (colour == ChessColour.White) ? board.getAllWhiteBitboard() : board.getAllBlackBitboard();
    move_bb = move_bb ^ (same_bb & move_bb);
    return move_bb;
}





// ---------------------------------------------------------------------------------------------
// --------------------------------------- Moves -----------------------------------------------
// ---------------------------------------------------------------------------------------------
// --------- Moves bitboards do not include the position the piece is occupying ----------------
ChessLogic.getMoveBitboard = function(x, y, colour, board) {
    let pos = src.position;
    let colour = src.chess_piece!.colour;
    switch(src.chess_piece!.type) {
    case ChessPieceType.King:
        return self.getKingMoveBitboard(pos: pos, colour: colour, board:board);

    case ChessPieceType.Queen:
        return self.getQueenMoveBitboard(pos: pos, colour: colour, board:board);

    case ChessPieceType.Bishop:
        return self.getBishopMoveBitboard(pos: pos, colour: colour, board:board);

    case ChessPieceType.Knight:
        return self.getKnightMoveBitboard(pos: pos, colour: colour, board:board);

    case ChessPieceType.Rook:
        return self.getRookMoveBitboard(pos: pos, colour: colour, board:board);

    case ChessPieceType.Pawn:
        return self.getPawnMoveBitboard(pos: pos, colour: colour, board:board);
    }
}
