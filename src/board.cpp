#include <iostream>
#include <vector>
#include <unordered_map>
#include "board.h"

using namespace std;

othelloBoard::othelloBoard() {
    positions.assign(64,0);
    positions[1] = 1;
}

void othelloBoard::draw() {
    for (int i = 0; i < n; i+=height ) {
        for (int j = i; j < i+width; j++) {
            cout << positions[j] << " ";
                // if (positions[j] == 1)
                //     cout << "\u2572\u2571" ;
                // if (positions[j] == -1)
                //     cout << "\u259F\u2599";
                // if (positions[j] == 0)
                //     cout << "\u2518\u2514";
        }
        cout << endl;
            // for (int j = i; j < i+width; j++) {
            //     if (positions[j] == 1)
            //         cout << "\u2571\u2572" ;
            //     if (positions[j] == -1)
            //         cout << "\u259C\u259B";
            //     if (positions[j] == 0)
            //         cout << "\u2510\u250C";
            // }
            // cout << endl;
    }
}

unordered_map<int, vector<int>> othelloBoard::validMoves () {
    unordered_map<int, vector<int>> moves;
    return moves;
}

void othelloBoard::printValidMoves () {

}

void othelloBoard::updatePositions (vector<int> newPositions) {
        // cout << positions[1] << endl;
    positions.swap(newPositions);
}