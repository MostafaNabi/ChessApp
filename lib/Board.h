class Board {

public:

    // ------- Variables -------
    Bitboard White_King;
    Bitboard White_Queen;
    Bitboard White_Bishop;
    Bitboard White_Knight;
    Bitboard White_Rook;
    Bitboard White_Pawn;

    Bitboard Black_King;
    Bitboard Black_Queen;
    Bitboard Black_Bishop;
    Bitboard Black_Knight;
    Bitboard Black_Rook;
    Bitboard Black_Pawn;

    Piece[][] mailbox [8][8];

    Colour current_turn;


    // ------- Constructors --------

    Board()

    // Copy and move constructors
    Board(const Board&);
    Board(Board &&);

    // Destructor
    ~Board();


    // ---- Functions --------

    bool move(Move m);
    bool isValidMove(Move m);

}
