#include <list>
#include "board.h"
using namespace std;

class player {
    bool humanPlayer;

    int n;
    int heuristic(vector<int> positions);
    int miniMax(othelloBoard board, int depth, bool maximizingPlayer);
    pair<int, list<int>> computerMove(othelloBoard board, unordered_map<int, list<int>> validMoves);

    pair<int, list<int>>  interactiveMove(unordered_map<int, list<int>> validMoves);

public:
    int symbol;
    int playerId;
    player(bool a, bool b, int c, int d);

    pair<int, list<int>> selectMove(othelloBoard board, unordered_map<int, list<int>> validMoves);
};