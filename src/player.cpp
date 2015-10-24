#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <numeric>
#include <limits>
#include <algorithm>  
#include <ratio>
#include <chrono>
#include "player.h"

using namespace std;

int bigNo = 123456789;

chrono::time_point<std::chrono::system_clock> tic() {
    return chrono::system_clock::now();
}

chrono::duration<double> toc(chrono::time_point<std::chrono::system_clock> start) {
    chrono::time_point<std::chrono::system_clock> end = chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    return elapsed_seconds;
}

int player::alphaBeta(othelloBoard board, int depth, int alpha, int beta, bool maximizingPlayer, int & nodesVisited, chrono::time_point<std::chrono::system_clock> start) {
    chrono::duration<double> elapsed_seconds = toc(start);
    if (elapsed_seconds.count() > 0.99*limit) {
        return numeric_limits<int>::max() -1;
    }

    int bestValue;
    unordered_map<int, list<int>> validMoves = board.validMoves(symbol);
    
    if (depth < 1 || validMoves.begin() == validMoves.end()) {
        // call heuristic - in this case most pieces
        bestValue = heuristic.heuristic(board,60 - board.nMoves,symbol);
        if (symbol == -1)
            bestValue = -1*bestValue;
        return bestValue;
    }

    if (maximizingPlayer) {
        bestValue = -bigNo;
        for (auto kv : validMoves) {
            othelloBoard scratchBoard = board;
            scratchBoard.updatePositions(kv,symbol);
            nodesVisited++;
            int val = alphaBeta(scratchBoard, depth -1, alpha, beta, false, nodesVisited, start);
            bestValue = max(val,bestValue);
            alpha = max(alpha,bestValue);
            if (beta <= alpha) {
                break;
            }
        } 
        return bestValue;
    } else {
        bestValue = bigNo;
        for (auto kv : validMoves) {
            othelloBoard scratchBoard = board;
            scratchBoard.updatePositions(kv,-symbol);
            nodesVisited++;
            int val = alphaBeta(scratchBoard, depth -1, alpha, beta, true, nodesVisited, start);
            bestValue = min(val,bestValue);
            beta = min(beta,bestValue);
            if (beta <= alpha) {
                break;
            }
        } 
        return -bestValue; // minus sign is in question just added
    }
    return bestValue;    
}



pair<int, list<int>> player::computerMove(othelloBoard board, unordered_map<int, list<int>> validMoves) {
        chrono::time_point<std::chrono::system_clock> start = tic();

        // alphabeta
        int nodesVisited = 0;
        pair<int, list<int>> move;

        if (validMoves.size() == 1) {
            move = *validMoves.begin();
            return move;
        }

        if (board.nMoves < 10) {
            pair<bool,pair<int,list<int>>> bookLookup = openingDatabase.getMove(validMoves, board.pastMoves);
            if (bookLookup.first) {
                cout << "Move found in opening database." << endl;
                return bookLookup.second;
            } else {
                cout << "Opening lookup failed, resort to search." << endl;
            }
        }

        pair<int, list<int>> tmpmove;
        int bestVal = -bigNo;
        int d;
        for (d = 1; d < 60 - board.nMoves; d++) {
            cout << "Searching at depth " << d << endl;
            int val;
            int nodesVisitedTmp = nodesVisited;
            for (auto kv : validMoves) {
                othelloBoard scratchBoard = board;
                scratchBoard.updatePositions(kv,symbol);
                nodesVisited++;
                val = alphaBeta(scratchBoard, d, -bigNo, bigNo, true, nodesVisitedTmp, start);
                if (val > bestVal && val != (numeric_limits<int>::max() -1)) {
                    bestVal = val;
                    tmpmove = kv;
                } //else if (val == bestVal && val != (numeric_limits<int>::max() -1)) {
                    //if (rand() % 100  > 50) {
                    //    bestVal = val;
                    //    tmpmove = kv; 
                    //}
                //} 
                else if (val == (numeric_limits<int>::max() -1)) {
                    break;
                }
            }
            if (val != (numeric_limits<int>::max() -1)) {
                    move = tmpmove;
                    nodesVisited = nodesVisitedTmp;
            } else {
                break;
            }
        }

        chrono::duration<double> elapsed_seconds = toc(start);
        cout << "\nCompleted search to depth " << d-1 << endl;
        cout << "\nNodes visited: " << nodesVisited << endl; 
        cout << "Time to move: " << elapsed_seconds.count() << " seconds" << endl << endl;

        return move;
    }

pair<int, list<int>> player::interactiveMove(unordered_map<int, list<int>> validMoves) {
        pair<int, list<int>> move;
        int ind;
        //interactive selection from list.

        cout << "Pick Move: ";
        cin >> ind;

        int i;
        for (auto kv : validMoves) {
            move = kv;
            i++;
            if (i == ind)
                break;
        }

        return move;
    }

player::player(bool a, bool b, int c, int d, heuristicEvaluation e) {
        humanPlayer = a;
        playerId = b; // implicit conversion from bool to int
        n = c; // number of entries on board
        symbol = d;
        if (!humanPlayer) {
            openings db;
            db.sequences = db.generateData(symbol);
            openingDatabase = db;
            heuristic = e;
        }
    }

pair<int, list<int>> player::selectMove(othelloBoard board, unordered_map<int, list<int>> validMoves) { 
        pair<int, list<int>> kv;
        if (humanPlayer == true) {
            cout << "Human Selects Move\n";
            kv = interactiveMove(validMoves);
        }
        else {
            cout << "Computer Selects Move\n";
            kv = computerMove(board, validMoves);
        }
        return kv;
    }