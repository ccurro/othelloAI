#include <iostream>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <limits.h>
#include <assert.h>
#include <sstream>
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
    // choice = 2;

    bool validSelection = false;

    do {
        cout << "Selection: ";

        std::string str;
        cin >> str;
        std::istringstream iss(str);
        iss >> choice;

        if (iss.eof() == false) {
            cout << "Non-integer input, please try again." << endl;
        } else if(choice > 2 || choice < 0) {
            cout << "Integer selection out of range, please try again" << endl;
        } else {
            validSelection = true;
        }
    } while (!validSelection);


    othelloGame game (&board, false, false);

    if (choice == 1)
        game.newGame = false;

    heuristicEvaluation h1;
    // h1.hIndex = (*argv[1] - '0');
    h1.w = w.first;
    h1.hIndex = 5;

    heuristicEvaluation h2;
    // h2.hIndex = (*argv[2] - '0');
    h2.w = w.second;
    h2.hIndex = 5;

    // humanPlayer, playerId, n, symbol 
    player playerOne (false, 1, board.n,-1, h2); // black
    player playerTwo (true, 0, board.n,1, h1);  // white


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
