#include <iostream>
#include <unordered_map>
#include <cmath>
#include "board.h"
#include "game.h"

int main () {
	othelloBoard board; 
	othelloGame game (board);

	for (int i=0; i < 10; i++) {
		game.computerMove();
		game.playerMove();
	};	
}
