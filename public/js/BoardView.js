// Onclick functions for the navbar

function BoardView() {
//    this.singleplayer_board = Board();
  //  this.twoplayer_board = Board();

}


BoardView.prototype.init = function() {

}

BoardView.prototype.setupSinglePlayer = function() {
    $('.navigation_display_container').hide();
    $('#singleplayer_container').show();
}

BoardView.prototype.setupTwoPlayer = function(container_id) {
    $('.navigation_display_container').hide();
    $('#twoplayer_container').show();
}

BoardView.prototype.setupAbout = function(container_id) {
    $('.navigation_display_container').hide();
    $('#about_container').show();
}



