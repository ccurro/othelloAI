#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <numeric>
#include <limits>
#include <algorithm>  
#include "player.h"

using namespace std;

int player::heuristic(vector<int> positions) {
    return accumulate(positions.begin(), positions.end(), 0);
}

int player::miniMax(othelloBoard board, int depth, bool maximizingPlayer) {
    int bestValue;
    unordered_map<int, list<int>> validMoves = board.validMoves(symbol);

    if (depth == 0) {
        // call heuristic - in this case most pieces
        bestValue = heuristic(board.positions);
        return bestValue;
    }

    if (maximizingPlayer) {
        bestValue = numeric_limits<int>::min();
        for (auto kv : validMoves) {
            othelloBoard scratchBoard = board;
            scratchBoard.updatePositions(kv,symbol);
            int val = miniMax(scratchBoard, depth -1, false);
            bestValue = max(val,bestValue);
        } 
        return bestValue;
    } else {
        bestValue = numeric_limits<int>::max();
        for (auto kv : validMoves) {
            othelloBoard scratchBoard = board;
            scratchBoard.updatePositions(kv,symbol);
            int val = miniMax(scratchBoard, depth -1, true);
            bestValue = max(val,bestValue);
        } 
        return bestValue;
    }
    return bestValue;    
}

pair<int, list<int>> player::computerMove(othelloBoard board, unordered_map<int, list<int>> validMoves) {
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
        pair<int, list<int>> move;
        int bestVal = numeric_limits<int>::min();
        for (auto kv : validMoves) {
            othelloBoard scratchBoard = board;
            scratchBoard.updatePositions(kv,symbol);
            int val = miniMax(scratchBoard, 4, true);
            if (val > bestVal) {
                bestVal = val;
                move = kv;
            }
        }

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