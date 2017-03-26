// Onclick functions for the navbar

function BoardView() {
    this.singleplayer_board = new Board();
    this.twoplayer_board = new Board();
    this.singleplayer_selected_tile = null;
    this.twoplayer_selected_tile = null;
}


BoardView.prototype.init = function() {

}

BoardView.prototype.setupSinglePlayer = function() {
    $('.navigation_display_container').hide();
    $('#singleplayer_container').show();
    this.singleplayer_board.draw('singleplayer_board_container');
}

BoardView.prototype.setupTwoPlayer = function(container_id) {
    $('.navigation_display_container').hide();
    $('#twoplayer_container').show();
    this.twoplayer_board.draw('twoplayer_board_container');
}

BoardView.prototype.setupAbout = function(container_id) {
    $('.navigation_display_container').hide();
    $('#about_container').show();
}


BoardView.prototype.selectTile = function(div, version, y, x) {
    if(version == 'single') {
        this.selectSingleplayerTile(div, y, x);
    } else if(version == 'two') {
        this.selectTwoplayerTile(div, y, x);
    }
}


BoardView.prototype.selectSingleplayerTile = function(div, y, x) {
    if(this.singleplayer_selected_tile == null) {
        this.singleplayer_selected_tile = {'div':div, 'x':x, 'y':y}
        $(div).addClass('selected_tile');
    } else {
        var srcdiv = this.singleplayer_selected_tile.div;
        var srcx = this.singleplayer_selected_tile.x;
        var srcy = this.singleplayer_selected_tile.y;
        var moved = this.singleplayer_board.move(srcx, srcy, x, y);
        if(moved) {
            $(srcdiv).removeClass('selected_tile');
            $('.singleplayer_board_container *_tile').removeClass('last_moved_tile');
            $(div).addClass('last_moved_tile');
            
            var src_class = $(srcdiv).attr('class').match('chess_piece[^\ ]+')[0];
            console.log('src class', src_class, srcdiv);
            $(srcdiv).removeClass(src_class);
                
            $(div).removeClass(function(i, c) {
                var matches = c.match('chess_piece[^\ ]+');
                if(matches != null) {
                    return matches[0];
                }
            });

            $(div).addClass(src_class);
            this.singleplayer_selected_tile = null;
         }
    }
}


BoardView.prototype.selectTwoplayerTile = function(div, y, x) {



}
