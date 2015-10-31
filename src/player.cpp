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
#include "sstream"

using namespace std;

int bigNo = 2000000000;

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
        if (!maximizingPlayer) {
            return numeric_limits<int>::max() -1;
        } else if(maximizingPlayer) {
            return numeric_limits<int>::min() +1;
        }
    }

    unordered_map<int, list<int>> validMoves;
    int bestValue;
    int currSymbol;
    if (maximizingPlayer) {
        validMoves = board.validMoves(symbol);
        currSymbol = symbol;
    } else {
        validMoves = board.validMoves(-symbol);
        currSymbol = -symbol;
    }

    if (depth < 1) {        
    // if (depth < 1 || validMoves.begin() == validMoves.end()) {        
        // call heuristic - in this case most piece
        bestValue = heuristic.heuristic(board,60 - board.nMoves,currSymbol);
        if (symbol == -1)
            bestValue = -1*bestValue;
        return bestValue;
    }

    if (validMoves.size() == 0) {
        unordered_map<int, list<int>> otherValidMoves;
        if (!maximizingPlayer) {
            otherValidMoves = board.validMoves(symbol);
        } else {
            otherValidMoves = board.validMoves(-symbol);
        }
        if (otherValidMoves.size() > 0) {
            return alphaBeta(board, depth -1, alpha, beta, !maximizingPlayer, nodesVisited, start);
        } else {
            bestValue = heuristic.heuristic(board,60 - board.nMoves,currSymbol);
            if (symbol == -1)
                bestValue = -1*bestValue;
            return bestValue;
        }
    }

    if (maximizingPlayer) {
        bestValue = -bigNo;
        for (auto kv : validMoves) {
            othelloBoard scratchBoard = board;
            scratchBoard.updatePositions(kv,symbol);
            // scratchBoard.draw(validMoves,0);
            nodesVisited++;
            int val = alphaBeta(scratchBoard, depth -1, alpha, beta, false, nodesVisited, start);
            bestValue = max(val,bestValue);
            alpha = max(alpha,bestValue);
            if (beta <= alpha) {
                break;
            }
        } 
        // exit(-1);
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
        return bestValue;
    }
    // return bestValue;    
}



pair<int, list<int>> player::computerMove(othelloBoard board, unordered_map<int, list<int>> validMoves) {
        chrono::time_point<std::chrono::system_clock> start = tic();

        // alphabeta
        int nodesVisited = 0;
        pair<int, list<int>> move;

        if (validMoves.size() == 1) {
            move = *validMoves.begin();
            cout << "Only one valid move." << endl;
            return move;
        }

        // if (board.nMoves < 18) {
        //     pair<bool,pair<int,list<int>>> bookLookup = openingDatabase.getMove(validMoves, board.pastMoves);
        //     if (bookLookup.first) {
        //         cout << "Move found in opening database." << endl;
        //         return bookLookup.second;
        //     } else {
        //         cout << "Opening lookup failed, resort to search." << endl;
        //     }
        // }

        pair<int, list<int>> tmpmove;

        int d;
        for (d = 1; d < 60 - board.nMoves + 1; d++) {
        // for (d = 7; d < 8; d++) {        
            int bestVal = -bigNo;        
            // bool fullSearch = false;    
            // if (60 - board.nMoves < 12) {
            //     d = 60 - board.nMoves + 1;
            //     fullSearch = true;
            // }
            // cout << "Spaces remaining on the board: " << 60 - board.nMoves << endl;
            cout << "Searching at depth " << d << endl;
            int val;
            int nodesVisitedTmp = nodesVisited;
            for (auto kv : validMoves) {
                othelloBoard scratchBoard = board;
                scratchBoard.updatePositions(kv,symbol);
                nodesVisited++;
                val = alphaBeta(scratchBoard, d, -bigNo, bigNo, false, nodesVisitedTmp, start);
                cout << kv.first << ":" << val << " ";
                if (val > bestVal && val != (numeric_limits<int>::max() -1) && val != (numeric_limits<int>::min() -1)) {
                    bestVal = val;
                    tmpmove = kv;
                } else if (val == bestVal && val != (numeric_limits<int>::max() -1) && val != (numeric_limits<int>::min() -1)) {
                    if ((rand() % 100)  > 50) {
                        bestVal = val;
                        tmpmove = kv;
                    }
                } 
                else if (val == (numeric_limits<int>::max() -1) || val == (numeric_limits<int>::min() +1)) {
                    break;
                }
            }
            cout << endl;
            if (val != (numeric_limits<int>::max() -1) && val != (numeric_limits<int>::min() +1)) {
                    move = tmpmove;
                    nodesVisited += nodesVisitedTmp;
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

        bool validSelection = false;

        do {
            cout << "Pick Move: ";

            std::string str;
            cin >> str;
            std::istringstream iss(str);
            iss >> ind;

            if (iss.eof() == false) {
                cout << "Non-integer input, please try again." << endl;
            } else if(ind > validMoves.size() || ind < 0) {
                cout << "Integer selection out of range, please try again" << endl;
            } else {
                validSelection = true;
            }
        } while (!validSelection);

        int i = 0;
        for (auto kv : validMoves) {
            move = kv;
            i++;
            if (i == ind) {
                break;
            }
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