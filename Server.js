var express = require('express')

var WebInterface = require('lib/WebInterface.cc')
var single_if = WebInterface();
var two_if =   WebInterface();

var app = express()

// Defining middleware to serve static file
app.use(express.static('public'));

app.get('/', function (req, res) {
    res.sendFile(__dirname + '/views/index.html')
});

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
