var express = require('express')

var WebInterface = require('lib/WebInterface.cc')

// Declare here, do not construct until init function is called
var single_wi;
var two_wi;

var app = express()

// Defining middleware to serve static file
app.use(express.static('public'));

app.get('/', function (req, res) {
    res.sendFile(__dirname + '/views/index.html')
});

// Receive FEN description of Board as data
// Return 2D array with pieces in it, as BoardView does
// not hold ANY logic, only displays the board.
app.post('/singleplayer:init', function (req, res) {
    // var res = WebInterface.make_move();
});

app.post('/singleplayer:make_move', function (req, res) {
    // var res = WebInterface.make_move();
});


app.post('/twoplayer:init', function (req, res) {
}

app.post('/twoplayer:make_move', function (req, res) {
}

app.listen(8080, function () {
  console.log('Example app listening on port 8080!')
});
