
var express = require('express')
var app = express()

// Defining middleware to serve static file
app.use(express.static('public'));

app.get('/', function (req, res) {
    res.sendFile(__dirname + '/views/index.html')
});

app.get('/twoplayer', function (req, res) {
    res.sendFile(__dirname + '/views/twoplayer.html')
});

app.listen(3000, function () {
  console.log('Example app listening on port 3000!')
});

