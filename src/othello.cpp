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
    player playerOne (false, true, board.n);
    player playerTwo (true, false, board.n);

    if (game.newGame) {
        cout << "New Game\n";
        game.firstMove();
    }

    // while (!game.complete) {
        board.draw();
        game.move(playerOne); // player one moves
        // board.draw();
        // game.move(playerTwo); // player two moves
        // game.statusUpdate(); // updates value of game.complete 
    // };  
}
