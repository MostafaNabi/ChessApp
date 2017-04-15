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


app.get('/singleplayer/retrieve_board', function (req, res) {
    res.send(single_wi.retrieve_board());
});

app.get('/singleplayer/build_from_fen', function (req, res) {
});

app.get('/singleplayer/make_move', function (req, res) {
    var orig_square = parseInt(req.query.orig);
    var dest_square = parseInt(req.query.dest);
    var result = single_wi.make_move(orig_square, dest_square);
    var str = 'cout << "Moved ' + orig_square + ', ' + dest_square + '" << ';
    str += 'chess.make_move(SQ_' + orig_square + ', SQ_' + dest_square + ') << endl;';
    console.log(str);    if(result != 0) {
        var resp = JSON.parse(single_wi.retrieve_board());
        resp.result = result;
        res.json(resp);
    } else {
        res.json({result: 0});
    }
});

app.get('/singleplayer/promote_pawn', function (req, res) {
    var piece = parseInt(req.query.piece);
    var square = parseInt(req.query.square);
    var resp = {};
    result = single_wi.promote_pawn(square, piece);
    console.log("pawn promotion: square="+square + ", piece=" + piece + ", result="+result);
    if(result) {
        var resp = JSON.parse(single_wi.retrieve_board());
        resp.promoted = true;
        res.json(resp);
    } else {
        res.json({promoted : false})
    }
});


app.get('/twoplayer/retrieve_board', function (req, res) {
    res.send(two_wi.retrieve_board());
});


app.get('/twoplayer:build_from_fen', function (req, res) {
});

app.get('/twoplayer/make_move', function (req, res) {
    var orig_square = parseInt(req.query.orig);
    var dest_square = parseInt(req.query.dest);
    var result = two_wi.make_move(orig_square, dest_square);
    
    var str = "cout << Moved " + orig_square + ", " + dest_square + " << ";
    str += "chess.make_move(" + orig_square + ", " + dest_square + ") << endl;";
    console.log(str);
    if(result != 0) {
        var resp = JSON.parse(two_wi.retrieve_board());
        resp.result = result;
        res.json(resp);
    } else {
        res.json({result: 0});
    }
});

app.get('/twoplayer/promote_pawn', function (req, res) {
    var piece = res.query.piece;
    var square = res.query.square;
    console.log("pawn promotion: square="+square + ", piece=" + piece);
    var resp = {};
    result = two_wi.promote_pawn(square, piece);
    if(result) {
        var resp = JSON.parse(two_wi.retrieve_board());
        resp.promoted = true;
        res.json(resp);
    } else {
        res.json({promoted : false})
    }
});

app.listen(8080, function () {
  console.log('Example app listening on port 8080!')
});
