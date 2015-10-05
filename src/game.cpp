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
	pos[21]  = 1;
	// pos[27] = 1;
	// pos[28] = -1;
	// pos[35] = -1;
	// pos[36] = 1;
	board->updatePositions(pos);
}

void othelloGame::move(player p) {
	unordered_map<int, vector<int>> moves = board->validMoves();
	vector<int> pos = p.selectMove(moves);
	// board->updatePositions(pos);
	board->draw();
}

void othelloGame::statusUpdate() {
        complete = true; // for this will stop game after one move.
        cout << "Game is complete.\n";
    }