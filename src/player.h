#include <list>
#include <chrono>
#include "openings.h"
#include "heuristicEvaluation.h"
using namespace std;

class player {
    bool humanPlayer;

    int n;
    float limit = 1;
    openings openingDatabase;
    heuristicEvaluation heuristic;
    int alphaBeta(othelloBoard board, int depth, int alpha, int beta, bool maximizingPlayer, int & nodesVisited, chrono::time_point<std::chrono::system_clock> start);
    int miniMax(othelloBoard board, int depth, bool maximizingPlayer, int & nodesVisited, chrono::time_point<std::chrono::system_clock> start);
    pair<int, list<int>> computerMove(othelloBoard board, unordered_map<int, list<int>> validMoves);

    pair<int, list<int>>  interactiveMove(unordered_map<int, list<int>> validMoves);

public:
    int symbol;
    int playerId;
    player(bool a, bool b, int c, int d, heuristicEvaluation e);

    pair<int, list<int>> selectMove(othelloBoard board, unordered_map<int, list<int>> validMoves);
};