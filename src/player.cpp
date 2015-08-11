#include <iostream>
#include <vector>
#include <unordered_map>
#include "player.h"

using namespace std;

vector<int> player::computerMove(unordered_map<int, vector<int>> validMoves) {
        vector<int> move;
        //all of the alphabeta work.
        return move;
    }

vector<int> player::interactiveMove(unordered_map<int, vector<int>> validMoves) {
        vector<int> move;
        //interactive selection from list.
        return move;
    }

player::player(bool a, bool b, int c) {
        humanPlayer = a;
        playerId = b; // implicit conversion from bool to int
        n = c; // number of entries on board
    }

vector<int> player::selectMove(unordered_map<int, vector<int>> validMoves) { 
        vector<int> move;
        if (humanPlayer == true) {
            cout << "Human Selects Move\n";
            move = interactiveMove(validMoves);
        }
        else {
            cout << "Computer Selects Move\n";
            move = computerMove(validMoves);
        }
        return move;
    }