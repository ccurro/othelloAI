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
    if (&positions) {
        fprintf(stderr,"%x\n",&positions);
    }
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
    // go through board positions 
    int prevPiece;
    for (int i = 0; i < n; i+=1) {
        switch (positions[i]) {
            case  0:
                continue;
            case 1:
                // go through columns
                printf("For 1 piece at i = %d\n",i);
                for (int j = 8; i + j < n; j+=8) {
                    printf("%d\n",i+j);
                    int pos = positions[i+j];
                    if (pos == 1)
                        break;
                    if (pos == -1)
                        continue;
                    if (pos == 0 && positions[i+j-8] == 1)
                        break;
                    if (pos == 0 && positions[i+j-8] == -1) {
                        positions[i+j] = 4;
                        break;
                    }
                }
                for (int j = -8; i + j > 0; j+=-8) {
                    printf("%d\n",i+j);
                    int pos = positions[i+j];
                    if (pos == 1)
                        break;
                    if (pos == -1)
                        continue;
                    if (pos == 0 && positions[i+j+8] == 1)
                        break;
                    if (pos == 0 && positions[i+j+8] == -1) {
                        positions[i+j] = 4;
                        break;
                    }
                }
                // go through rows
                printf("Rows:\n");
                for (int j = 1; ((i + j -1) % 8) < 7; j+=1) {
                    printf("%d\n",i+j);
                    int pos = positions[i+j];
                    if (pos == 1)
                        break;
                    if (pos == -1)
                        continue;
                    if (pos == 0 && positions[i+j-1] == 1)
                        break;
                    if (pos == 0 && positions[i+j-1] == -1) {
                        positions[i+j] = 4;
                        break;
                    }
                }
                for (int j = -1; ((i + j +1) % 8) > 0; j+=-1) {
                    printf("%d\n",i+j);
                    int pos = positions[i+j];
                    if (pos == 1)
                        break;
                    if (pos == -1)
                        continue;
                    if (pos == 0 && positions[i+j+1] == 1)
                        break;
                    if (pos == 0 && positions[i+j+1] == -1) {
                        positions[i+j] = 4;
                        break;
                    }
                }
                // go through diagonals 
                printf("Diagonals:\n");
                // up and right
                for (int j = -7; i+j > 0 && ((i + j -1) % 8) < 7 ; j+=-7) {
                    printf("%d\n",i+j);
                    int pos = positions[i+j];
                    if (pos == 1)
                        break;
                    if (pos == -1)
                        continue;
                    if (pos == 0 && positions[i+j+7] == 1)
                        break;
                    if (pos == 0 && positions[i+j+7] == -1) {
                        positions[i+j] = 4;
                        break;
                    }
                }
                // // down and left
                for (int j = 7; (i+j < n - 1); j+=7) {
                    printf("%d\n",i+j);
                    int pos = positions[i+j];
                    if (pos == 1)
                        break;
                    if (pos == -1)
                        continue;
                    if (pos == 0 && positions[i+j-7] == 1)
                        break;
                    if (pos == 0 && positions[i+j-7] == -1) {
                        positions[i+j] = 4;
                        break;
                    }
                    if ((i+j) % 8 == 0)
                        break;
                }
                // up and left
                for (int j = -9; i+j > -1; j+=-9) {
                    printf("%d\n",i+j);
                    int pos = positions[i+j];
                    if (pos == 1)
                        break;
                    if (pos == -1)
                        continue;
                    if (pos == 0 && positions[i+j+9] == 1)
                        break;
                    if (pos == 0 && positions[i+j+9] == -1) {
                        positions[i+j] = 4;
                        break;
                    }
                    if ((i+j) % 8 == 0)
                        break;
                }
                // down and right
                for (int j = 9; i+j < n && ((i + j -1) % 8) < 7; j+=9) {
                    printf("%d\n",i+j);
                    int pos = positions[i+j];
                    if (pos == 1)
                        break;
                    if (pos == -1)
                        continue;
                    if (pos == 0 && positions[i+j-9] == 1)
                        break;
                    if (pos == 0 && positions[i+j-9] == -1) {
                        positions[i+j] = 4;
                        break;
                    }
                }
            // case 1:
        }
    }

    return moves;
}

void othelloBoard::printValidMoves () {

}

void othelloBoard::updatePositions (vector<int> newPositions) {
        // cout << positions[1] << endl;
    positions.swap(newPositions);
}