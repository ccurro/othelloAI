#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <assert.h>
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

void othelloGame::loadGame(string gameFileName) {
	vector<int> pos(board->n,0);
	ifstream gameFile;
	string line;
	gameFile.open(gameFileName);
	int ind = 0;
	while (getline(gameFile,line)) {
		for (int i = 0; i < 16; i+=2) {
			cout << line[i] << endl;
			char c = line[i];
			if (c == 'B')
				pos[ind] = -1;
			if (c == 'W')
				pos[ind] = 1;
			if (c == '0')
				pos[ind] = 0;
			cout << ind << endl;
			ind++;
		}
	}
	board->positions.swap(pos);
	gameFile.close();
}


void othelloGame::move(player p) {
	unordered_map<int, list<int>> moves = board->validMoves(p.symbol);
	if (moves.empty()) {
		passes[p.playerId] = 1;
	} else {
		passes[p.playerId] = 0;
		board->draw(moves);
		pair<int, list<int>> move = p.selectMove(*board,moves);

		board->updatePositions(move,p.symbol);
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