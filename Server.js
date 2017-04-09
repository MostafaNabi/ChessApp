var express = require('express')
var app = express()

// test.js
const ChessAddon = require('./build/Release/ChessAddon.node');

var single_wi = new ChessAddon.WebInterface(1, 3);
var two_wi = new ChessAddon.WebInterface(2);

// Defining middleware to serve static file
app.use(express.static('public'));

app.get('/', function (req, res) {
    res.sendFile(__dirname + '/views/index.html');
});

// Receive FEN description of Board as data
// Return 2D array with pieces in it, as BoardView does
// not hold ANY logic, only displays the board.
app.get('/singleplayer/build_from_fen', function (req, res) {
    // var res = WebInterface.make_move();
});

app.get('/singleplayer/make_move', function (req, res) {
    var orig_square = parseInt(req.query.orig);
    var dest_square = parseInt(req.query.dest);
    console.log("Got parameters", orig_square, dest_square);
    var moved = single_wi.make_move(orig_square, dest_square);
    var resp = {}
    if(moved) {
        var resp = JSON.parse(single_wi.retrieve_board());
        resp.moved = true;
        res.json(resp);
    } else {
        resp.moved = false;
        res.json(resp);
    }
});

app.get('/singleplayer/retrieve_board', function (req, res) {
    res.send(single_wi.retrieve_board());
});

app.get('/twoplayer:build_from_fen', function (req, res) {
});

app.get('/twoplayer/make_move', function (req, res) {
    // var res = WebInterface.make_move();
});

app.listen(8080, function () {
  console.log('Example app listening on port 8080!')
});
