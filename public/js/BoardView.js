// Onclick functions for the navbar

function BoardView(game_type, container_id) {
    this.game_type  = game_type;
    this.container_id = container_id;
    this.popup = document.createElement('div');

    this.selected_square = null;
    this.last_moved_square = null;
    this.current_turn = 'white';

    this.websocket = new WebSocket('ws:'+window.location.host+'?game_type='+game_type);

    this.piece_map = {
        0:'chess_piece_white_king',
        1:'chess_piece_white_queen',
        2:'chess_piece_white_bishop',
        3:'chess_piece_white_knight',
        4:'chess_piece_white_rook',
        5:'chess_piece_white_pawn',

        6:'chess_piece_black_king',
        7:'chess_piece_black_queen',
        8:'chess_piece_black_bishop',
        9:'chess_piece_black_knight',
        10:'chess_piece_black_rook',
        11:'chess_piece_black_pawn',
        12:'chess_piece_none'
    }

    var self = this;
    this.websocket.onopen = function() {
        self.init();
    }
}

BoardView.prototype.changeTurn = function() {
    if(this.current_turn == 'white') {
        this.current_turn = 'black';
    } else {
        this.current_turn = 'white';
    }
}

BoardView.prototype.init = function() {
    this.setupWebsocket();
    this.setupBoard();
    this.setupPopup();
}


BoardView.prototype.setupWebsocket = function() {
    var self = this;
    self.websocket.addEventListener('message', function(event) {
        var resp = JSON.parse(event.data);
        switch(resp.event) {
            case 'make_move_result': {
                self.make_move_result(resp);
                break;
            }

            case 'request_move_result': {
                self.changeTurn();
                self.request_board();
                break;
            }

            case 'request_board_result': {
                self.request_board_result(resp);
                break;
            }
            
            case 'promote_pawn_result': {
                self.promote_pawn_result(resp);
                break;
            }
        }
    });
}

BoardView.prototype.setupPopup = function() {
    this.popup.style.display = 'none';
    this.popup.id = 'user_input_popup';
    this.popup.className = 'popup';
    var oc =  (this.game_type == 'singleplayer') ? 'SinglePlayerBoardView' : 'TwoPlayerBoardView';
    if(this.game_type)
    this.popup.innerHTML =  "<div class='white_pawn_promotion'>" +
                                "<div class='chess_piece_white_queen' onclick='"+oc+".promote_pawn(1)'></div>" +
                                "<div class='chess_piece_white_bishop' onclick='"+oc+".promote_pawn(2)'></div>" +
                                "<div class='chess_piece_white_knight' onclick='"+oc+".promote_pawn(3)'></div>" +
                                "<div class='chess_piece_white_rook' onclick='"+oc+".promote_pawn(4)'></div>" +
                            "</div>" +
                            "<div class='black_pawn_promotion'>" +
                                "<div class='chess_piece_black_queen' onclick='"+oc+".promote_pawn(7)'></div>" +
                                "<div class='chess_piece_black_bishop' onclick='"+oc+".promote_pawn(8)'></div>" +
                                "<div class='chess_piece_black_knight' onclick='"+oc+".promote_pawn(9)'></div>" +
                                "<div class='chess_piece_black_rook' onclick='"+oc+".promote_pawn(10)'></div>" +
                            "</div>";
    $(this.popup).find('.white_pawn_promotion').hide();
    $(this.popup).find('.black_pawn_promotion').hide();
    document.getElementById(this.container_id).appendChild(this.popup);
}

BoardView.prototype.setupBoard = function(fen) {
    // Set up chess board
    var self = this;
    for(var y=7; y>=0; y--) {
        var row = document.createElement('div');
        $(row).addClass('board_row');
        $('#'+self.container_id + ' .board_container').append(row);

        for(var x=0; x<8; x++) {
            var tile = document.createElement('div');
            if((y % 2 == 0 && x % 2 == 0) || (y % 2 != 0 && x % 2 != 0)) {
                $(tile).addClass('black_board_tile');
            } else {
                $(tile).addClass('white_board_tile');
            }
            $(row).append(tile);
            (function(tile, x,y) {
                tile.addEventListener('click', function() {
                    self.selectTile(x, y);
                });
            })(tile,x,y);
        }
    }
    this.request_board();
}

/*
    Build board from a FEN string
*/
BoardView.prototype.buildFromFen = function(fen) {
    var matches = fen.match(/(([KQBNRPkqbnrp\/1-8]+)(\ [bw]\ )(-|[KQkq]+\ )(-\ |[a-h][1-8]\ )(\d+\ )(\d+))/);
    if(matches == null) {
        window.alert('Fen string is not in correct form');
        return;
    }
}

BoardView.prototype.display = function() {
    $('.navigation_display_container').hide();
    console.log('showing', this.container_id);
    $('#'+this.container_id).show();
}


BoardView.prototype.getTile = function(sq) {
    var x = sq % 8;
    var y = Math.floor(sq/8);
    var con = $('#'+this.container_id + ' .board_container')[0];
    var row = 7 - y;
    var col = x;
   // console.log('getTile', row, col, con.children[row]);
    return con.children[row].children[col];
}

BoardView.prototype.setHighlight = function(sq, highlight) {
    var tile = this.getTile(sq);
    $(tile).addClass(highlight);
}

BoardView.prototype.removeHighlight = function(sq, highlight) {
    var tile = this.getTile(sq);
    $(tile).removeClass(highlight);
}

BoardView.prototype.removeAllHighlight = function(highlight) {
    $('#'+this.container_id + ' .board_row div').removeClass(highight);
}

BoardView.prototype.isWhite = function(sq) {
    var black = ['chess_piece_white_king','chess_piece_white_queen','chess_piece_white_bishop',
                'chess_piece_white_knight','chess_piece_white_rook','chess_piece_white_pawn'];

    var tile = this.getTile(sq);
    for(var i=0; i<black.length; i++) {
        if(tile.classList.contains(black[i])) {
            return true;
        }
    }
    return false;
}

BoardView.prototype.isBlack = function(sq) {
    var black = ['chess_piece_black_king','chess_piece_black_queen','chess_piece_black_bishop',
                'chess_piece_black_knight','chess_piece_black_rook','chess_piece_black_pawn'];

    var tile = this.getTile(sq);
    for(var i=0; i<black.length; i++) {
        if(tile.classList.contains(black[i])) {
            return true;
        }
    }
    return false;
}

BoardView.prototype.isSameColour = function(orig, dest) {
    if(this.isWhite(orig) && this.isWhite(dest)) {
        return true;
    }
    if(this.isBlack(orig) && this.isBlack(dest)) {
        return true;
    }
    return false;
}

BoardView.prototype.hasPiece = function(sq) {
    return (this.isWhite(sq) || this.isBlack(sq));
}


BoardView.prototype.selectTile = function(x, y) {
    var orig = this.selected_square;
    var dest = (8*y) + x;

    if(this.game_type == 1 && this.current_turn != 'white') {
        return;
    }
    // invalid selection
    if(orig == null && !this.hasPiece(dest)) {
        return;
    }

    // new selection
    if(orig == null && this.hasPiece(dest)) {
        if(this.isWhite(dest) && this.current_turn != 'white') {
            return;
        } else if(this.isBlack(dest) && this.current_turn != 'black') {
            return;
        }
        this.selected_square = dest;
        this.setHighlight(dest, 'selected_tile');
        return;
    }

    // changing same colour
    if(this.isSameColour(orig, dest)) {
        this.removeHighlight(orig, 'selected_tile');
        this.setHighlight(dest, 'selected_tile');
        this.selected_square = dest;
        return;
    }
    this.make_move(orig, dest);
};


BoardView.prototype.make_move = function(orig, dest) {
    var req = {'event':'make_move', 'orig':orig, 'dest':dest}
    this.websocket.send(JSON.stringify(req));
}

BoardView.prototype.promote_pawn = function(piece) {
    var req = {'event':'promote_pawn', 'orig':this.last_moved_square, 'piece':piece}
    this.websocket.send(JSON.stringify(req));
}

BoardView.prototype.request_move = function() {
    var req = {'event':'request_move'}
    this.websocket.send(JSON.stringify(req));
}

BoardView.prototype.request_board = function() {
    var req = {'event':'request_board'}
    this.websocket.send(JSON.stringify(req));
}


BoardView.prototype.make_move_result = function(resp) {
        // INVALID_MOVE
    if(resp.result == 0) {
        $('#'+this.container_id + ' .message')[0].innerHTML = 'Invalid Move!';
        return;
    }

    var orig  = resp.prev_orig;
    var dest  = resp.prev_dest;
    this.last_moved_square = dest;


    //------------------ Special Results -------------------
    // check mate
    if(resp.result == 4) {
        $('#'+this.container_id + ' .message')[0].innerHTML = 'CheckMate!';
        this.selected_square = null;
        this.request_board();
        return;
    }

    // pawn promotion
    if(resp.result == 2) {
        $('#'+this.container_id + ' .message')[0].innerHTML = 'Pawn Promotion!';
        $(this.popup).show();
        $(this.popup).find('.'+this.current_turn+'_pawn_promotion').show();
        return;
    }


    //------------------ Normal Results -------------------

    // normal move
    if(resp.result == 1) {
        $('#'+this.container_id + ' .message')[0].innerHTML = 'Normal Move!';
    }



    // check
    if(resp.result == 3) {
        $('#'+this.container_id + ' .message')[0].innerHTML = 'Check!';
    }


    this.changeTurn();
    this.selected_square = null;

    this.request_board();
    if(this.game_type == 1) {
        this.request_move();
    }
}

BoardView.prototype.request_move_result = function(resp) {
}

BoardView.prototype.request_board_result = function(resp) {
    this.drawPieces(resp.result);
}

BoardView.prototype.promote_pawn_result = function(resp) {
    $(this.popup).hide();
    $(this.popup).find('.'+self.current_turn+'_pawn_promotion').hide();
    this.changeTurn();
    this.selected_square = null;
    this.request_board();
    if(this.game_type == 1) {
        this.request_move();
    }
}


/*
    Draw board from server response
*/
BoardView.prototype.drawPieces = function(board) {
  //  console.log('retrieved board length', board, board.length);
    for(var i=0; i<board.length; i++) {        
        var tile = this.getTile(i);
        var x = i % 8;
        var y = Math.floor(i/8);
        $(tile).removeClass();
        if((y % 2 == 0 && x % 2 == 0) || (y % 2 != 0 && x % 2 != 0)) {
            $(tile).addClass('black_board_tile');
        } else {
            $(tile).addClass('white_board_tile');
        }
        if(this.last_moved_square != null) {
            //this.setHighlight(this.last_moved_square, 'last_moved_tile');
        }
        $(tile).addClass(this.piece_map[board[i]]);
    }
}
