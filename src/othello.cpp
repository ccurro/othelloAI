#include <iostream>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <assert.h>
#include "player.h"
#include "board.h"
#include "game.h"

int main () {
    othelloBoard board; 
    othelloGame game (&board, false, false);
    player playerOne (true, true, board.n,1);
    player playerTwo (false, false, board.n,-1);

    if (game.newGame) {
        cout << "New Game\n";
        game.firstMove();
    }

    while (!game.complete) {
        game.move(playerOne); // player one moves
        game.move(playerTwo);
        game.statusUpdate(); // updates value of game.complete 
    };  
}
