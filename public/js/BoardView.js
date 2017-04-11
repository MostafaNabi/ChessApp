// Onclick functions for the navbar

function BoardView(game_type, container_id) {
    this.url = '/'+game_type;
    this.container_id = container_id;
    this.selected_tile = null; // {div, x, y}
    this.current_turn = 'white';

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
    this.init();
}

BoardView.prototype.changeTurn = function() {
    if(this.current_turn == 'white') {
        this.current_turn = 'black';
    } else {
        this.current_turn = 'white';
    }
}

BoardView.prototype.init = function() {
    this.setupBoard();
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
    this.drawBoard();
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

/*
    Get div from the given position
*/
BoardView.prototype.getTile = function(x,y) {
    var con = $('#'+this.container_id + ' .board_container')[0];
    var row = 7 - y;
    var col = x;
    return con.children[row].children[col];
}

BoardView.prototype.setHighlight = function(x,y, highlight) {
    var tile = this.getTile(x,y);
    $(tile).addClass(highlight);
}

BoardView.prototype.removeHighlight = function(x,y, highlight) {
    var tile = this.getTile(x,y);
    $(tile).removeClass(highlight);
}

BoardView.prototype.removeAllHighlight = function(highlight) {
    $('#'+this.container_id + ' .board_row div').removeClass(highight);
}

BoardView.prototype.isWhite = function(tile) {
    var white = ['chess_piece_white_king','chess_piece_white_queen','chess_piece_white_bishop',
                'chess_piece_white_knight','chess_piece_white_rook','chess_piece_white_pawn'];

    for(var i=0; i<white.length; i++) {
        if(tile.classList.contains(white[i])) {
            return true;
        }
    }
    return false;
}

BoardView.prototype.isBlack = function(tile) {
    var black = ['chess_piece_black_king','chess_piece_black_queen','chess_piece_black_bishop',
                'chess_piece_black_knight','chess_piece_black_rook','chess_piece_black_pawn'];

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

BoardView.prototype.hasPiece = function(orig) {
    return (this.isWhite(orig) || this.isBlack(orig));
}


BoardView.prototype.selectTile = function(x, y) {
    var self = this;
    var dest = self.getTile(x,y);

    // invalid selection
    if(this.selected_tile == null && !this.hasPiece(dest)) {
        return;
    }

    // new selection
    if(this.selected_tile == null && this.hasPiece(dest)) {
        if(this.isWhite(dest) && this.current_turn != 'white') {
            return;
        } else if(this.isBlack(dest) && this.current_turn != 'black') {
            return;
        }
        this.selected_tile = {'div':dest, 'x':x, 'y':y};
        this.setHighlight(x,y, 'selected_tile');
    }


    // changing same colour
    if(self.isSameColour(this.selected_tile.div, dest)) {
        this.removeHighlight(this.selected_tile.x, this.selected_tile.y, 'selected_tile');
        this.setHighlight(x, y, 'selected_tile');
        this.selected_tile = {'div':dest, 'x':x, 'y':y};
        return;
    }

    // convert y,x co-ordinates into square number starting from 0
    var orig_square = (8*this.selected_tile.y) + this.selected_tile.x;
    var dest_square = (8*y) + x;

    // send ajax request to move
    var xhr = new XMLHttpRequest();
    xhr.open('GET', this.url + '/make_move?orig='+orig_square+'&dest='+dest_square, true);
    xhr.onreadystatechange = function() {
        if(xhr.readyState === XMLHttpRequest.DONE) {
            if(xhr.status === 200) {
                var resp = JSON.parse(xhr.response);
                if(resp.moved) {
                    self.changeTurn();
                    self.removeHighlight(self.selected_tile.x, self.selected_tile.y, 'selected_tile');
                    self.setHighlight(x, y, 'last_moved_tile');
                    self.selected_tile = null;
                    self.drawPieces(resp.board);
                }
            }
        }
    }
    xhr.send();
};


/*
    Retrieve Board
*/
BoardView.prototype.drawBoard = function(fen) {
    var self = this;
    // send ajax request to move
    var xhr = new XMLHttpRequest();
    xhr.open('GET', this.url + '/retrieve_board', true);
    xhr.onreadystatechange = function() {
        if(xhr.readyState === XMLHttpRequest.DONE) {
            if(xhr.status === 200) {
                var resp = JSON.parse(xhr.response);
                self.drawPieces(resp.board);
            }
        }
    }
    xhr.send();
}

/*
    Draw board from server response
*/
BoardView.prototype.drawPieces = function(board) {
    console.log('retrieved board length', board, board.length);
    for(var i=0; i<board.length; i++) {
        var y = Math.floor(i / 8);
        var x = i % 8;
        var tile = this.getTile(x, y);
        $(tile).removeClass();
        if((y % 2 == 0 && x % 2 == 0) || (y % 2 != 0 && x % 2 != 0)) {
            $(tile).addClass('black_board_tile');
        } else {
            $(tile).addClass('white_board_tile');
        }
        $(tile).addClass(this.piece_map[board[i]]);
    }
}
