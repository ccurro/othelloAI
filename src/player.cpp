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


// int player::heuristic(vector<int> positions, int nSpacesRemaining) {
//     return accumulate(positions.begin(), positions.end(), 0);
// }

int ESAC(int moveNumber) {
    return 312 + 6.24*moveNumber;
}

int CMAC(int moveNumber) {
    if (moveNumber < 25) 
        return 50 + 2*moveNumber;
    if (moveNumber > 25)
        return 75 + moveNumber;
}

int player::heuristic(othelloBoard board, int nSpacesRemaining) {
    // do heuristic from perspective of player with p.symbol = 1
    int val = 0;
    vector <int> positions = board.positions;

        //check if game is over
        unordered_map<int, list<int>> validMoves = board.validMoves(symbol);
        unordered_map<int, list<int>> otherValidMoves = board.validMoves(-symbol);
        if (validMoves.begin() == validMoves.end()) {   
            if (otherValidMoves.begin() == otherValidMoves.end()) {
                int s = accumulate(board.positions.begin(), board.positions.end(), 0);
                if (s > 0)
                    return 4567890;
                if (s < 0)
                    return -4567890;
            }
        }

        int p = validMoves.size();
        int o = otherValidMoves.size();
        int currentMobility = trunc(100 * (p - o) /(p +o + 2));

        int corners = 1000*(positions[0] + positions[7] + positions[56] + positions[63]);

        int stability = 0;
        for (auto kv : validMoves) {
            list<int> flippedDiscs = kv.second;
            stability -= flippedDiscs.size();
        }

        // go through interior positions
        int interior[] = {9,10,11,12,13,15,17,18,19,20,21,22,25,26,27,28,29,30,33,34,35,36,37,38,41,42,43,44,45,46,49,50,51,52,53,54};
        int cur, top, bot, lef, rig, tr, tl, bl, br;
        int potMobilility;
        for (int i : interior) {
            cur = positions[i];
            lef = positions[i-1];
            rig = positions[i+1];
            top = positions[i-8];
            bot = positions[i+8];
            tr  = positions[i-7];
            tl  = positions[i-9];
            bl  = positions[i+7];
            br  = positions[i+9];
            // Potential Mobility 
            // # of discs that the oppenent has adjacent to empty squares
            potMobilility = 0;
            if (cur == -1 && (lef == 0 || rig == 0 || top == 0 || bot == 0 || tr == 0 || tl == 0 || bl == 0 || br == 0))
                potMobilility++;
            // # of empty squares adjacent ot the opponents discs
            if (cur = -1 && lef == 0)
                potMobilility++;
            if (cur = -1 && rig == 0)
                potMobilility++;
            if (cur = -1 && top == 0)
                potMobilility++;
            if (cur = -1 && bot == 0)
                potMobilility++;
            if (cur = -1 && tr  == 0)
                potMobilility++;
            if (cur = -1 && tl  == 0)
                potMobilility++;
            if (cur = -1 && bl  == 0)
                potMobilility++;
            if (cur = -1 && br  == 0)
                potMobilility++;
        }

        // go through exterior positions 
        // go through top positions
        int topa[] = {1,2,3,4,5,6};
        for (int i : topa) {
            cur = positions[i];
            lef = positions[i-1];
            rig = positions[i+1];
            if (cur == -1 && (lef == 0 || rig == 0))
                potMobilility++;
            // # of empty squares adjacent ot the opponents discs
            if (cur = -1 && lef == 0)
                potMobilility++;
            if (cur = -1 && rig == 0)
                potMobilility++;
        }

        // go through bottom positions
        int bota[] = {57,58,59,60,61,62};
        for (int i : bota) {
            cur = positions[i];
            lef = positions[i-1];
            rig = positions[i+1];
             if (cur == -1 && (lef == 0 || rig == 0))
                potMobilility++;
            // # of empty squares adjacent ot the opponents discs
            if (cur = -1 && lef == 0)
                potMobilility++;
            if (cur = -1 && rig == 0)
                potMobilility++;
        }

        // go through left positions
        int lefa[] = {8,16,24,32,40,48};
        for (int i : lefa) {
            cur = positions[i];
            bot = positions[i-8];
            top = positions[i+8];
             if (cur == -1 && (top == 0 || bot == 0 ))
                potMobilility++;
            // # of empty squares adjacent ot the opponents discs
            if (cur = -1 && top == 0)
                potMobilility++;
            if (cur = -1 && bot  == 0)
                potMobilility++;
        }

        // go through right positions
        int riga[] = {15,23,31,39,47,55};
        for (int i : riga) {
            cur = positions[i];
            bot = positions[i-8];
            top = positions[i+8];
             if (cur == -1 && (top == 0 || bot == 0 ))
                potMobilility++;
            // # of empty squares adjacent ot the opponents discs
            if (cur = -1 && top == 0)
                potMobilility++;
            if (cur = -1 && bot  == 0)
                potMobilility++;
        }

        val = CMAC(nSpacesRemaining + 60)*currentMobility + 99*potMobilility + 30*corners + 36*stability;

        // cout << "Score breakdown" << endl;
        // cout << CMAC(nSpacesRemaining + 60)*currentMobility << endl;
        // cout << 99*potMobilility << endl;
        // cout << corners << endl;
        // cout << 36*stability << endl;

    return val;
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
        bestValue = heuristic(board,60 - board.nMoves);
        if (symbol == -1)
            bestValue = -1*bestValue;
        return bestValue;
    }

    // // check if there are no valid moves
    // int s = 0;
    // if (validMoves.begin() == validMoves.end()) {
    //     // need to handle no valid moves
    //     // othelloBoard scratchBoard = board;
    //     // int val = alphaBeta(scratchBoard, 0, alpha, beta, ~maximizingPlayer, nodesVisited, start);
    //     bestValue = heuristic(board,60 - board.nMoves);
    //     if (symbol == -1)
    //         bestValue = -1*bestValue;
    //     return bestValue;
    //     // // 
    //     // othelloBoard scratchBoard = board;
    //     // nodesVisited++;
    //     // if (maximizingPlayer) {
    //     //     int val = alphaBeta(scratchBoard, depth -1, alpha, beta, true, nodesVisited, start);
    //     //     // bestValue = max(val,bestValue);
    //     //     // alpha = max(alpha,bestValue);
    //     //     // if (beta <= alpha) {
    //     //         // break;
    //     //     // }
    //     //     return val;
    //     // } else {
    //     //     int val = alphaBeta(scratchBoard, depth -1, alpha, beta, false, nodesVisited, start);
    //     //     // bestValue = min(val,bestValue);
    //     //     // beta = min(beta,bestValue);
    //     //     // if (beta <= alpha) {
    //     //         // break;
    //     //     // }
    //     //     return val;
    //     // }
    // }

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
            pair<bool,pair<int,list<int>>> bookLookup = openingDatabase.getMove(validMoves);
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
        if (!humanPlayer) {
            openings db;
            db.sequences = db.generateData();
            openingDatabase = db;
        }
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