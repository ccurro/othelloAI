#include <iostream>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <limits.h>
#include <assert.h>
#include "game.h"

int main () {
    othelloBoard board;

    int choice;
    cout << "Load a game or start a new one?\n";
    cout << "1 -> Load a saved board state\n";
    cout << "2 -> Start a new game\n";
    cout << "Selection: ";
    cin >> choice;

    othelloGame game (&board, false, false);

    if (choice == 1)
        game.newGame = false;

    vector<int> w;
    heuristicEvaluation f;

    // humanPlayer, playerId, n, symbol 
    player playerOne (false, 1, board.n,-1, f); // black
    player playerTwo (false, 0, board.n,1, f);  // white


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
