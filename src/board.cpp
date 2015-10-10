#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include "player.h"
#include "board.h"

using namespace std;

othelloBoard::othelloBoard() {
    positions.assign(64,0);
    positions[1] = 1;
}

void othelloBoard::draw(unordered_map<int, list<int>> moves) {
    if (&positions) {
        fprintf(stderr,"%x\n",&positions);
    }
    cout << "  A B C D E F G H\n";
    int r = 0;
    for (int i = 0; i < n; i+=height ) {
        cout << ++r << "\e[48;5;34m\e[38;5;232m \033[0m";
        for (int j = i; j < i+width; j++) {
            if (positions[j] == 1) {
                cout << "\e[48;5;34m\e[38;5;256m\u25CF" << " \033[0m";
            } else if (positions[j] == -1) {
                cout << "\e[48;5;34m\e[38;5;232m\u25CF" << " \033[0m";
            } else if (moves.find(j) != moves.end()) {
                cout << "\e[48;5;34m\e[38;5;232m\u2613" << " \033[0m";
            } 
            else {
                cout << "\e[48;5;34m\e[38;5;232m\u00B7 \033[0m";
            }
        }
        cout << endl;
    }

    char alpha[9] = "ABCDEFGH";
    char nums[9]  = "01234567";
    int row, col;
    int i = 1;

    for (auto kv : moves) {
        ind2sub(kv.first, width, height, &row, &col);
        cout << "Possible Move " << i << ": " << alpha[col] << nums[row] << ", ";
        list<int>::const_iterator k;
        list<int> l = kv.second;
        cout << "Pieces to be flipped:";
        for (k = l.begin(); k != l.end(); k++) {
            ind2sub(*k, width, height, &row, &col);
            cout << " "<< alpha[col] << nums[row] << ",";
        }

        cout << endl;
        i++;
    }
}

void othelloBoard::ind2sub(const int sub,const int cols,const int rows,int *row,int *col) {
   *row=sub/cols;
   *col=sub%cols;
}

void othelloBoard::validMovesHelper(int clr, int i, int inc, unordered_map<int, list<int>> & pieces) {
    list<int> candidates;
    for (int j = inc; (i + j < n) && (i + j > -1); j+=inc) {
        // printf("%d\n",i+j);
        int pos = positions[i+j];
        if (pos == clr)
            break;
        if (pos == -clr) {
            candidates.push_front(i+j);
            continue;
        }
        if (pos == 0 && positions[i+j-inc] == clr)
            break;
        if (pos == 0 && positions[i+j-inc] == -clr) { 
            if (pieces.find(i+j) != pieces.end()) {
                list <int> oldcandidates = pieces[i+j];
                oldcandidates.splice(oldcandidates.begin(),candidates);
                pieces.erase(i+j);
                pieces.insert(pair<int,list<int>> (i+j,oldcandidates));
            } else {
                pieces.insert(pair<int,list<int>> (i+j,candidates));
            }
            break;
        }
        int row, col;
        ind2sub(i+j, width, height, &row, &col);
        if ((row == 0) || (row == 7) || (col == 0) || (col == 7))
            break;
    }
}

// unordered_map<int, vector<intothelloBoard::validMoves () {
 unordered_map<int, list<int>> othelloBoard::validMoves (player p) {
    unordered_map<int, list<int>> moves;
    // moves.clear();
    // go through board positions 
    int prevPiece;
    for (int i = 0; i < n; i+=1) {
            if (positions[i] == 0)
                continue;
            if (positions[i] == p.symbol) {
                // go through columns
                // printf("For 1 piece at i = %d\n",i);
                validMovesHelper(p.symbol, i,  8, moves);
                validMovesHelper(p.symbol, i, -8, moves);
                // go through rows
                validMovesHelper(p.symbol, i,  1, moves);
                validMovesHelper(p.symbol, i, -1, moves);
                // printf("Diagonals:\n");
                validMovesHelper(p.symbol, i, -7, moves);
                validMovesHelper(p.symbol, i,  7, moves);
                validMovesHelper(p.symbol, i, -9, moves);
                validMovesHelper(p.symbol, i,  9, moves);
            }
            if (positions[i] == -p.symbol)
                continue;
        }
    return moves;
}

void othelloBoard::printValidMoves () {

}

void othelloBoard::updatePositions (pair<int, list<int>> move, player p) {

    int piece = move.first;
    // cout << piece;
    list<int>::const_iterator k;

    positions[piece] = p.symbol;

    list<int> l = move.second;

    for (k = l.begin(); k != l.end(); k++) {
        // cout << *k;
        positions[*k] = p.symbol;
    }
}