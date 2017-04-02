{
    "targets": [{
        "target_name": "ChessAddon",
        "sources": ["lib/Types.cc","lib/Bitboard.cc","lib/Board.cc","lib/Moves.cc","lib/Chess.cc","lib/WebInterface.cc","lib/ChessAddon.cc"],
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
