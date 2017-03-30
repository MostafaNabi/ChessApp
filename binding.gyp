{
  "targets": [
    {
      "target_name": "ChessAddon",
      "sources": [ "lib/ChessAddon.css", "lib/WebInterface.cc" ],
      "include_dirs" : ["<!(node -e \"require('nan')\")"]
    }
  ]
}
