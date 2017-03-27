var express = require('express')
var addon = require('lib/demo.cc')
var app = express()

console.log(addon.helloworld());
// Defining middleware to serve static file
app.use(express.static('public'));

app.get('/', function (req, res) {
    res.sendFile(__dirname + '/views/index.html')
});


app.get('/singleplayer', function (req, res) {
    res.send('Hello you are on the singleplayer page');
});

app.listen(8080, function () {
  console.log('Example app listening on port 8080!')
});
