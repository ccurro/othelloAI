using namespace std;

class othelloGame {
    othelloBoard board;

public:
    bool complete = false; // boolean if game is complete or not.
    bool newGame = true;
    bool humanPlayer, humanPlayerFirst;

    othelloGame(othelloBoard a, bool b, bool c) {
        board = a; 
        humanPlayer = b;
        humanPlayerFirst = c;
        assert(!(!humanPlayer && humanPlayerFirst)); 
        // make sure humanPlayerFirst isn't true, when there
        // isn't a human player.
    }

    void firstMove() {
        vector<int> pos(board.n,0);
        pos[27] = 1;
        pos[28] = -1;
        pos[35] = -1;
        pos[36] = 1;
        board.updatePositions(pos);
    }

    void move(player p) {
        unordered_map<int, vector<int>> moves = board.validMoves();
        vector<int> pos = p.selectMove(moves);
        board.updatePositions(pos);
    }

    void statusUpdate() {
        complete = true; // for this will stop game after one move.
        cout << "Game is complete.\n";
    }
};