#include "openings.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

openings::openings() {
	sequences = generateData();
}

list<list<int>> openings::generateData() {
	ifstream database ("openings.csv",ifstream::in);
	char line[1024];
	list<list<int>> seq;

	for (int j = 1; j < 397; j++) {
		database.getline(line, 1024);
		string str(line);
		std::stringstream ss(str);
		int i;

		list<int> moves;

		while (ss >> i) {
			moves.push_back(i);

			if (ss.peek() == ',')
				ss.ignore();
		}
		seq.push_back(moves);
	}

	return seq;
}

pair<bool, pair<int,list<int>>> openings::getMove(unordered_map<int, list<int>> validMoves) {
	pair<int,list<int>> move;	
	bool found = false;
	pair<bool, pair<int,list<int>>> moveStatus;
	unordered_map<int, list<int>>::const_iterator candPtr;
	pair<int, list<int>> candidate;
	for (auto sequence : sequences ) {
		for (candPtr = validMoves.begin(); candPtr != validMoves.end(); candPtr++) {
			candidate = *candPtr;
			if (candidate.first == sequence.front()) {
				move = candidate;
				found = true;
				break;
			}
		}
		sequence.pop_front();
		if (found)
			break;
	}

	moveStatus.first = found;
	moveStatus.second = move;

	return moveStatus;
}