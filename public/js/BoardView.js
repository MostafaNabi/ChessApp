// Onclick functions for the navbar

function BoardView(game_type, container_id, fen) {
    this.url = '/'+game_type;
    this.container_id = container_id;
    this.selected_tile = null; // {div, x, y}

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
    this.init();
}

BoardView.prototype.init = function() {
    this.drawBoard();
}

BoardView.prototype.drawBoard = function(fen) {
    // Set up chess board
    var self = this;
    for(var y=7; y>=0; y--) {
        var row = document.createElement('div');
        $(row).class('board_row');
        $('#'+self.container_id).append(row);

        for(var x=0; x<8; x++) {
            var tile = document.createElement('div');
            if((y % 2 == 0 && x % 2 == 0) || (y % 2 != 0 && x % 2 != 0)) {
                $(tile).class('black_board_tile');
            } else {
                $(tile).class('white_board_tile');
            }
            tile.addEventListener(function(e) {
                self.selectTile(y, x);
            });
        }
    }
}

/*
    Build board from a FEN string
*/
BoardView.prototype.build_from_fen = function(fen) {
    var matches = fen.match(/(([KQBNRPkqbnrp\/1-8]+)(\ [bw]\ )(-|[KQkq]+\ )(-\ |[a-h][1-8]\ )(\d+\ )(\d+))/);
    if(matches == null) {
        window.alert('Fen string is not in correct form');
        return;
    }
}

BoardView.prototype.display = function() {
    $('.board_container').hide();
    $('#'+this.container_id).show();
}

/*
    Draw board from server response
*/
BoardView.prototype.draw = function(board) {

}

/*
    Get div from the given position
*/
BoardView.prototype.getTile = function(x,y) {
    var con = document.getElementById(this.container_id);
    var row = 7 - y;
    var col = x;
    return el.children[row][col];
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

BoardView.prototype.isSameColour = function(orig, dest) {
    if(orig.classList.contains('white_board_tile')  && dest.classList.contains('white_board_tile') {
        return true;
    }

    if(orig.classList.contains('black_board_tile')  && dest.classList.contains('black_board_tile') {
        return true;
    }
    return false;
}


BoardView.prototype.selectTile = function(y, x) {
    var self = this;
    var dest_tile = self.getTile(x,y);

    // invalid selection
    if(this.selected_tile == null && dest == null) {
        return;
    }

    // new selection
    if(this.selected_tile == null && dest != null) {
        this.selected_tile = {'div':dest, 'x':x, 'y':y};
        this.setHighlight(x,y, 'selected_tile');
    }


    // changing same colour
    if(self.isSameColour(this.selected_tile.div, dest)) {
        this.removeHighlight(this.selected_tile.x, this.selected_tile.y, 'selected_tile');
        this.setHighlight(x, y, 'selected_tile');
        this.selected_tile = {'div':dest, 'x':x, 'y':y};
    }

    // convert y,x co-ordinates into square number starting from 0
    var orig_square = (8*this.selected_tile.y) + this.selected_tile.x;
    var dest_square = (8*y) + x;

    // send ajax request to move
    var xhr = new XMLHttpRequest();
    xhr.open(this.url + '/make_move?orig='+orig_square+'&dest='+dest_square);
    xhr.onreadystatechange = function() {
        if(xhr.readyState === XMLHttpRequest.DONE) {
            if(xhr.status === 200) {
                var resp = JSON.parse(xhr.response);
                if(resp.moved) {
                    self.draw(resp.board);
                }
            }
        }
    }
    xhr.send();
};

/*
    Draw board from server response
*/
BoardView.prototype.draw = function(board) {

}
