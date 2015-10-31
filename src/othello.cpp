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

float getTimeLimit() {
    float limit;
    bool validSelection = false;
    do {
        cout << "Pick time limit for computer: (seconds) ";        

        std::string str;
        cin >> str;
        std::istringstream iss(str);
        iss >> limit;

        if (iss.eof() == false) {
            cout << "Non-numeric input, please try again." << endl;
        } else if(limit < 0) {
            cout << "Negative numeric input, please try a positive number" << endl;
        } else {
            validSelection = true;
        }
    } while (!validSelection);

    return limit;
}

bool checkCPU(int id) {
    bool cpu;
    char c;
    bool validSelection = false;
    do {
        cout << "Is Player " << id << " a computer? y/n ";      

        std::string str;
        cin >> str;
        std::istringstream iss(str);
        iss >> c;

        cout << c << endl;

        iss.ignore(numeric_limits <streamsize> ::max(), '\n' );

        if (iss.eof() == false) {
            cout << "Non-single character input, please try again." << endl;
        } else 
        if(c != 'y' && c != 'n') {
            cout << "Did not enter 'y' or 'n'. Please try again." << endl;
        } else {
            validSelection = true;
        }
    } while (!validSelection);

    if (c == 'y') {
        cpu = true;
    } else {
        cpu = false;
    }

    return cpu;
}

int main (int argc, char *argv[]) {
    othelloBoard board;

    pair<vector <int>,vector<int>>  w; //= getWeightVector(argc, argv);

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

    bool cpu1 = checkCPU(1);
    bool cpu2 = checkCPU(2);

    float limit;
    if (cpu1 || cpu2) {
        limit = getTimeLimit();
    }


    othelloGame game (&board, false, false);

    if (choice == 1)
        game.newGame = false;

    heuristicEvaluation h1;
    h1.w = w.first;
    h1.hIndex = 5;

    heuristicEvaluation h2;
    h2.w = w.second;
    h2.hIndex = 5; // 4 -> random

    // humanPlayer, playerId, n, symbol 
    player playerOne (!cpu1, 1, board.n,-1, h1); // black
    player playerTwo (!cpu2, 0, board.n,1,  h2);  // white

    if (cpu1 || cpu2) {
        playerOne.limit = limit;
        playerTwo.limit = limit;
    }


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
