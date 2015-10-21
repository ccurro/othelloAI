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

chrono::time_point<std::chrono::system_clock> tic() {
    return chrono::system_clock::now();
}

chrono::duration<double> toc(chrono::time_point<std::chrono::system_clock> start) {
    chrono::time_point<std::chrono::system_clock> end = chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    return elapsed_seconds;
}


int player::heuristic(vector<int> positions) {
    return accumulate(positions.begin(), positions.end(), 0);
}

int player::miniMax(othelloBoard board, int depth, bool maximizingPlayer, int & nodesVisited, chrono::time_point<std::chrono::system_clock> start) {
    chrono::duration<double> elapsed_seconds = toc(start);
    if (elapsed_seconds.count() > 0.99*limit) {
        return numeric_limits<int>::max() -1;
    }

    int bestValue;
    unordered_map<int, list<int>> validMoves = board.validMoves(symbol);

    // check if game is complete
    int gameComplete = false;
    if (validMoves.begin() == validMoves.end()) {
        unordered_map<int, list<int>> otherValidMoves = board.validMoves(-symbol);
        if (otherValidMoves.begin() == otherValidMoves.end()) {
            gameComplete = true;
        }
    }

    // if (gameComplete == true)
        // return numeric_limits<int>::max();

    if (depth == 0 || gameComplete) {
        // call heuristic - in this case most pieces
        bestValue = heuristic(board.positions);
        if (symbol == -1)
            bestValue = -1*bestValue;
        return bestValue;
    }

    if (maximizingPlayer) {
        bestValue = numeric_limits<int>::min();
        for (auto kv : validMoves) {
            othelloBoard scratchBoard = board;
            scratchBoard.updatePositions(kv,symbol);
            nodesVisited++;
            int val = miniMax(scratchBoard, depth -1, false,nodesVisited, start);
            bestValue = max(val,bestValue);
        } 
        return bestValue;
    } else {
        bestValue = numeric_limits<int>::max();
        for (auto kv : validMoves) {
            othelloBoard scratchBoard = board;
            scratchBoard.updatePositions(kv,-symbol);
            nodesVisited++;
            int val = miniMax(scratchBoard, depth -1, true, nodesVisited, start);
            bestValue = min(val,bestValue);
        } 
        return bestValue;
    }
    return bestValue;    
}


pair<int, list<int>> player::computerMove(othelloBoard board, unordered_map<int, list<int>> validMoves) {
        chrono::time_point<std::chrono::system_clock> start = tic();
        // vector<int> move;
        //all of the alphabeta work.

        // Pick Random move
        // unordered_map<int, list<int>>::iterator kv = validMoves.begin();
        // pair<int, list<int>> move = *kv;

        // Pick move that maximizes discs flipped
        // int nDiscs = 0;
        // pair<int, list<int>> move;
        // for (auto kv : validMoves) {
        //     list<int> flips = kv.second;
        //     if (flips.size() > nDiscs) {
        //         move = kv;
        //         nDiscs = flips.size();
        //     }
        // }

        // miniMax
        int nodesVisited = 0;
        pair<int, list<int>> move;
        pair<int, list<int>> tmpmove;
        int bestVal = numeric_limits<int>::min();
        int d;
        for (d = 1; d < 64 - board.nMoves; d++) {
            cout << "Searching at depth " << d << endl;
            int val;
            int nodesVisitedTmp = nodesVisited;
            for (auto kv : validMoves) {
                othelloBoard scratchBoard = board;
                scratchBoard.updatePositions(kv,symbol);
                nodesVisited++;
                val = miniMax(scratchBoard, d, true, nodesVisitedTmp, start);
                if (val > bestVal && val != (numeric_limits<int>::max() -1)) {
                    bestVal = val;
                    tmpmove = kv;
                } else if (val == (numeric_limits<int>::max() -1)) {
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

player::player(bool a, bool b, int c, int d) {
        humanPlayer = a;
        playerId = b; // implicit conversion from bool to int
        n = c; // number of entries on board
        symbol = d;
    }

pair<int, list<int>> player::selectMove(othelloBoard board, unordered_map<int, list<int>> validMoves) { 
        // vector<int> move;
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