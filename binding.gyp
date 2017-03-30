{
    "targets": [{
        "target_name": "ChessAddon",
        "sources": [ "lib/ChessAddon.cc", "lib/WebInterface.cc", "lib/Bitboard.cc", "lib/Board.cc", "lib/Types.cc", "lib/Chess.cc", "lib/Moves.cc" ],
        "include_dirs": ["./lib"],
        'cflags!': [ '-fno-exceptions' ],
        'cflags_cc!': [ '-std=c++11', '-fno-exceptions' ],
        'conditions': [
            ['OS=="mac"', {
                'xcode_settings': {
                    'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
                }
            }]
        ]
    }]
}
