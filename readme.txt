Chess mages taken from: https://commons.wikimedia.org/wiki/Category:PNG_chess_pieces/Standard_transparent


I have uploaded my software as a zip file, since I used Github for my version control, and including all the
packages I have used the number of files has become rather large.



First to setup the chess app stand-alone

1. The makefile uses the g++ compiler and c++11 library
2. Simply type make and that should do it :)
3. If you want to change the compiler simply modify the makefile
4. The main file runs a singleplayer command line game as well as perft tests.
    It is simple enough to change if you wish.


The server is alot more complicated and hard to test, since to really test the deployment I would need a fresh computer or 
completely uninstall all my packages and reset my work environment.

1. Install the node package manager (npm) 4.2.0 and node 7.8.0.
By installing npm node should will be installed alongside it.
You can download the latest node and npm here: https://nodejs.org/en/
Although that is version 7.10.0 it should still work.

2. My package.json file has a list of all my dependencies and versions, 
   after installing node and npm enter the root directory of my application 
   (where the package.json file is) and enter:
        npm install
  This should install required packages.

3. Now you can run make to create just the chess app or 
        node-gyp rebuild 
   to create the web app.


4. After node-gyp finishes building do
        npm start
    which will run the node server under localhost:8080

5. There done.


