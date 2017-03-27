// Onclick functions for the navbar

function BoardView(container_id) {
    this.container_id = container_id;
    this.board = new Board(this);
    this.selected_piece = null;
}

BoardView.prototype.init = function() {

}

BoardView.prototype.display = function() {
    $('.board_container').hide();
    $('#'+this.container_id).show();
}


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


BoardView.prototype.selectTile = function(y, x) {
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

    // moving piece
    var moved = this.board.move(curr.x, curr.y, dest.x, dest.y);
    if(moved) {
        this.removeAllHighlight('last_moved_tile');
        this.removeHighlight(curr.x, curr.y, 'selected_piece');
        this.setHighlight(dest.x, dest.y, 'last_moved_tile');
        this.board.draw();
    }

}
