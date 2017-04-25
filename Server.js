const express = require('express');
const http = require('http');
const url = require('url');
const WebSocket = require('ws');

const app = express();


// Addon for creating web interfaces
const ChessAddon = require('./build/Release/ChessAddon.node');
var id_counter = 0;

// Defining middleware to serve static file
app.use(express.static(__dirname+'/public'));

app.get('/', function (req, res) {
    res.sendFile(__dirname + '/views/index.html');
});

const server = http.createServer(app);
const wss = new WebSocket.Server({server: server});
wss.on('connection', function connection(ws) {
    var id = id_counter;
    id_counter++;
    console.log('Socket[' + id + '] connected.');

    var loc = url.parse(ws.upgradeReq.url, true);
    var gt = parseInt(loc.query.game_type);
    var wi;
    if(gt == 1) {
        wi = new ChessAddon.WebInterface(gt, 3);
    } else {
        wi = new ChessAddon.WebInterface(gt);
    }
    
    ws.on('open', function() {
        console.log('Socket[' + id + '] open.');
    });
    
    ws.on('message', function(data) {
        var req = JSON.parse(data);
        switch(req.event) {
            case 'make_move': {
                var result = wi.make_move(req.orig, req.dest);
                var resp = {
                    event: 'make_move_result',
                    result: result,
                    origin: req.orig, 
                    destination: req.dest
                }
                ws.send(JSON.stringify(resp));
                break;
            }

            case 'request_move': {
                var result = wi.request_move();
                var resp = JSON.parse(result);
                resp.event = 'request_move_result';
                ws.send(JSON.stringify(resp));
                break;
            }

            case 'request_board': {
                var resp = {'event':'request_board_result'};
                resp.result = JSON.parse(wi.retrieve_board()).board;
                ws.send(JSON.stringify(resp));
                break;
            }

            case 'promote_pawn': {
                var p = parseInt(req.piece);
                var orig = parseInt(req.orig);
                var result = wi.promote_pawn(orig, p);
                var resp = {
                    event: 'promote_pawn_result',
                    result: result
                }
                ws.send(JSON.stringify(resp));
                break;
            }
        }
    });

    ws.on('close', function() {
        console.log('Socket[' + id + '] closed.');
        ws.close();
    });
});

server.listen(8080, function listening() {
  console.log('Listening on 8080');
});