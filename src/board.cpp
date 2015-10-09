#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include "board.h"

using namespace std;

othelloBoard::othelloBoard() {
    positions.assign(64,0);
    positions[1] = 1;
}

void othelloBoard::draw() {
    if (&positions) {
        fprintf(stderr,"%x\n",&positions);
    }
    for (int i = 0; i < n; i+=height ) {
        for (int j = i; j < i+width; j++) {
            if (positions[j] == 1) {
                cout << "\e[48;5;40m\e[38;5;256m\u25CF" << " \033[0m";
            } else if (positions[j] == -1) {
                cout << "\e[48;5;40m\e[38;5;232m\u25CF" << " \033[0m";
            } else if (positions[j] == 4) {
                cout << "\e[48;5;40m\e[38;5;256m\u25AB" << " \033[0m";
            } 
            else {
                cout << "\e[48;5;40m\e[38;5;232m\u00B7 \033[0m";
            }
        }
        cout << endl;
    }
}

void othelloBoard::ind2sub(const int sub,const int cols,const int rows,int *row,int *col) {
   *row=sub/cols;
   *col=sub%cols;
}

void othelloBoard::validMovesHelper(int clr, int i, int inc, unordered_map<int, list<int>> & pieces) {
    for (int j = inc; (i + j < n) && (i + j > -1); j+=inc) {
        printf("%d\n",i+j);
        list<int> candidates;
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
            if (pieces.find(i) != pieces.end()) {
                list <int> oldcandidates = pieces[i];
                oldcandidates.splice(oldcandidates.begin(),candidates);
                pieces[i] = oldcandidates;
            } else {
                pieces.insert(pair<int,list<int>> (i,candidates));
            }
            positions[i+j] = 4;
            break;
        }
        int row, col;
        ind2sub(i+j, width, height, &row, &col);
        if ((row == 0) || (row == 7) || (col == 0) || (col == 7))
            break;
    }
}

unordered_map<int, vector<int>> othelloBoard::validMoves () {
    unordered_map<int, vector<int>> moves;
    unordered_map<int, list<int>> pieces;
    // go through board positions 
    int prevPiece;
    for (int i = 0; i < n; i+=1) {
        switch (positions[i]) {
            case  0:
                continue;
            case 1:
                // go through columns
                printf("For 1 piece at i = %d\n",i);
                validMovesHelper(1, i,  8, pieces);
                validMovesHelper(1, i, -8, pieces);
                // go through rows
                printf("Rows:\n");
                validMovesHelper(1, i,  1, pieces);
                validMovesHelper(1, i, -1, pieces);
                printf("Diagonals:\n");
                validMovesHelper(1, i, -7, pieces);
                validMovesHelper(1, i,  7, pieces);
                validMovesHelper(1, i, -9, pieces);
                validMovesHelper(1, i,  9, pieces);
            // case 1:
        }
    }
    list <int> test = pieces[21]; 

    return moves;
}

void othelloBoard::printValidMoves () {

}

void othelloBoard::updatePositions (vector<int> newPositions) {
        // cout << positions[1] << endl;
    positions.swap(newPositions);
}