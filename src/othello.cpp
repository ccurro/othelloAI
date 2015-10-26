#include <iostream>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <limits.h>
#include <assert.h>
#include "game.h"

pair<vector<int>,vector<int>> getWeightVector(int argc, char *argv[]) {
    pair<vector <int>,vector<int>> w;

    for (int i = 1; i < 3; i++) {
        char * wStr = argv[i];
        char c = wStr[0];
        while (c != 0) {
            if (c != ',') {
                if (i == 1)
                    w.first.push_back(c - '0');
                if (i == 2)
                    w.second.push_back(c - '0');
            }
            c = *wStr++;
        }
    }
    return w;
}

int main (int argc, char *argv[]) {
    othelloBoard board;

    pair<vector <int>,vector<int>>  w = getWeightVector(argc, argv);

    int choice;
    cout << "Load a game or start a new one?\n";
    cout << "1 -> Load a saved board state\n";
    cout << "2 -> Start a new game\n";
    cout << "Selection: ";
    // cin >> choice;
    choice = 2;

    othelloGame game (&board, false, false);

    if (choice == 1)
        game.newGame = false;

    heuristicEvaluation h1;
    h1.weights = w.first;

    heuristicEvaluation h2;
    h2.weights = w.second;

    // humanPlayer, playerId, n, symbol 
    player playerOne (false, 1, board.n,-1, h1); // black
    player playerTwo (true, 0, board.n,1, h2);  // white


    if (game.newGame) {
        cout << "New Game\n";
        game.firstMove();
    } else {
        string filename;
        cout << "Give filename of savefile: ";
        cin >> filename;
        game.loadGame(filename);
    }

    while (!game.complete) {
        game.move(playerOne); // player one moves
        game.move(playerTwo);
        game.statusUpdate(); // updates value of game.complete 
    };  
}
