#include <iostream>
#include <vector>
#include <unordered_map>
#include <assert.h>
#include "player.h"
#include "board.h"
#include "game.h"

using namespace std;

othelloGame::othelloGame(othelloBoard* a, bool b, bool c) {
	board = a; 
	humanPlayer = b;
	humanPlayerFirst = c;
	assert(!(!humanPlayer && humanPlayerFirst)); 
        // make sure humanPlayerFirst isn't true, when there
        // isn't a human player.
}

void othelloGame::firstMove() {
	vector<int> pos(board->n,0);


	pos[27] = 1;
	pos[28] = -1;
	pos[35] = -1;
	pos[36] = 1;
	board->positions.swap(pos);
}

void othelloGame::move(player p) {
	unordered_map<int, list<int>> moves = board->validMoves(p);
	if (moves.empty()) {
		passes[p.playerId] = 1;
	} else {
		passes[p.playerId] = 0;
		board->draw(moves);
		pair<int, list<int>> move = p.selectMove(moves);

		board->updatePositions(move,p);
	}
}

void othelloGame::statusUpdate() {
		if (passes[0] + passes[1] == 2) {
	        complete = true;
	        unordered_map<int, list<int>> moves;
	        board->draw(moves);
    	    cout << "Game is complete.\n";
    	} else {
			complete = false;
    	}
    }