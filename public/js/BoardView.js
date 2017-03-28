// Onclick functions for the navbar

function BoardView(game_type, container_id, fen) {
    this.url = '/'+game_type;
    this.container_id = container_id;
    this.board = null;
    if(!fen) {
        fen = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1'

    this.selected_piece = null;
    this.piece_map = {
        0:'chess_piece_white_king',
        1:'chess_piece_white_queen',
        2:'chess_piece_white_bishop',
        3:'chess_piece_white_knight',
        4:'chess_piece_white_rook',

        6:'chess_piece_black_king',
        7:'chess_piece_black_queen',
        8:'chess_piece_black_bishop',
        9:'chess_piece_black_knight',
        10:'chess_piece_black_rook',
        11:'chess_piece_black_pawn',
        12:'chess"_piece_none'
    }
}

/*
 Retrieve initial board
*/
BoardView.prototype.BuildFromFEN = function(fen) {
    var matches = fen.match(/(([KQBNRPkqbnrp\/[1-8]+)(\ [bw]\ )([-KQkq]+\ )(- | [a-h][1-8]\ )(\d\ )(\d))/);
    if(matches == null) {
        window.alert('Fen string is not in correct form');
    }
    this.state = {};
    var board_str = matches[1].replace(' ', '');
    var turn = matches[2].replace(' ', '');

    var castlingrights = matches[3].replace(' ', '');

    // ---- Ignore these three for now -------------
    var enpassant = matches[4].replace(' ', '');
    var halfmove = matches[5].replace(' ', '');
    var fullmove =matches[6].replace(' ', '');

    console.log('FEM matches', board_str, turn, castlingrights, enpassant, halfmove, fullmove);

    // --------- Create board --------------------------
    var arr = [[],[],[],[],[],[],[],[]];
    var i = 0; var j = 0;
    for(var k=0; k<board_str.length; k++) {
        var s = board_str[k];
 fensw: switch(s) {
            case '/': i++; j = 0;
            case 'K': arr[i][j] = 0; break;
            case 'Q': arr[i][j] = 1; break;
            case 'B': arr[i][j] = 2; break;
            case 'N': arr[i][j] = 3; break;
            case 'R': arr[i][j] = 4; break;
            case 'P': arr[i][j] = 5; break;
            case 'k': arr[i][j] = 6; break;
            case 'q': arr[i][j] = 7; break;
            case 'b': arr[i][j] = 8; break;
            case 'n': arr[i][j] = 9; break;
            case 'r': arr[i][j] = 10; break;
            case 'p': arr[i][j] = 11; break;

            case '1': arr[i][j] = 12; break;
            case '2': arr[i][j] = 12; j++; fensw('1'); break;
            case '3': arr[i][j] = 12; j++; fensw('2'); break;
            case '4': arr[i][j] = 12; j++; fensw('3'); break;
            case '5': arr[i][j] = 12; j++; fensw('4'); break;
            case '6': arr[i][j] = 12; j++; fensw('5'); break;
            case '7': arr[i][j] = 12; j++; fensw('6'); break;
            case '8': arr[i][j] = 12; j++; fensw('7'); break;
        }
            j++;
    }
    state.board = arr;
    state.turn = (turn == 'w') ? 1 : 0;

    // --------- Castling Rights ---------
    var w_castle_rights = 0;
    var b_castle_rights = 0;
    if(castlingrights == '-') {
        castlingrights.forEach(function(el) {
            if(el == 'K') { w_castle_rights += 1;}
            if(el == 'Q') { w_castle_rights += 2;}
            if(el == 'k') { b_castle_rights += 1;}
            if(el == 'q') { b_castle_rights += 2;}
        });
    }
    state.w_castle_rights = w_castle_rights;
    state.b_castle_rights = b_castle_rights;

}
/*
    Takes an object State in the form
    {
        board: int[][] - where values follow the piece_map definition
        turn : int - 1 for white, 0 for black
        w_castle_rights : (White) 2-bit binary number where 01 is kingside and 10 is queenside
        w_castle_rights : (Black) 2-bit binary number where 01 is kingside and 10 is queenside
    }
*/
BoardView.prototype.updateBoard = function(state) {
    // Make an ajax call to the server updating its board state
    var self = this;
    $.ajax({url: this_url+':init',
            data: JSON.stringify(state);
            type: 'POST',
            success: function() {
                console.log('Initialisation successed: ' + self.url);
            }
            error: function() {
                console.log('Initialisation failed: '+ self.url);
            }
        });
}

BoardView.prototype.display = function() {
    $('.board_container').hide();
    $('#'+this.container_id).show();
}

BoardView.prototype.draw = function(board) {

}

BoardView.prototype.getTile = function(x,y) {
    var con = document.getElementById(this.container_id);
    var row = 7 - y;
    var col = x;
    return el.children[row][col];
}

// Return object with x,y co-ordinates and colour
BoardView.prototype.getPieceAt = function(x,y) {

}

BoardView.prototype.setHighlight = function(x,y, highlight) {
    var tile = this.getTile(x,y);
    $(tile).addClass(highight);
}

BoardView.prototype.removeHighlight = function(x,y, highlight) {
    var tile = this.getTile(x,y);
    $(tile).removeClass(highight);
}

BoardView.prototype.removeAllHighlight = function(highlight) {
    $('#'+this.container_id + ' .board_row div').removeClass(highight);
}


BoardView.prototype.selectTile = function(y, x) {
    var self = this;
    var curr = this.selected_piece;
    var dest = this.board.getPieceAt(x,y);

    // invalid selection
    if(curr == null && dest == null) {
        return;
    }

    // new selection
    if(curr == null && dest != null) {
        this.selected_piece = dest;
        this.setHighlight(x,y, 'selected_tile');
    }

    // changing same colour
    if(curr != null && dest != null) {
        if(curr.colour == dest.colour) {
            this.removeHighlight(curr.x, curr.y, 'selected_piece');
            this.setHighlight(dest.x, dest.y, 'selected_piece');
            this.selected_piece = dest;
        }
    }

    // moving piece, make ajax request
    var d = {};
    d.origin = (8*curr.y) + curr.x;
    d.dest = (8*dest.y) + dest.x;
    d.col = ()

    $.ajax({
        url: '/',
        // dataType: "jsonp",
        data: {'orig': curr.x, 'dest':curr.y, 'col':},
        type: 'POST',
        jsonpCallback: 'callback', // this is not relevant to the POST anymore
        success: function (data) {
            var ret = jQuery.parseJSON(data);
            $('#lblResponse').html(ret.msg);
            console.log('Success: ')
        },
        error: function (xhr, status, error) {
            console.log('Error: ' + error.message);
            $('#lblResponse').html('Error connecting to the server.');
        },
    });
    var moved = this.board.move(curr.x, curr.y, dest.x, dest.y);
    if(moved) {
        this.removeAllHighlight('last_moved_tile');
        this.removeHighlight(curr.x, curr.y, 'selected_piece');
        this.setHighlight(dest.x, dest.y, 'last_moved_tile');
        this.board.draw();
    }

}
