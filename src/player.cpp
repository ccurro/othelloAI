#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include "player.h"

using namespace std;

pair<int, list<int>> player::computerMove(unordered_map<int, list<int>> validMoves) {
        // vector<int> move;
        //all of the alphabeta work.

        unordered_map<int, list<int>>::iterator kv = validMoves.begin();

        if (validMoves.begin() == validMoves.end())
            cout << "O FUCK!";

        pair<int, list<int>> move = *kv;

        return move;
    }

vector<int> player::interactiveMove(unordered_map<int, list<int>> validMoves) {
        vector<int> move;
        //interactive selection from list.
        return move;
    }

player::player(bool a, bool b, int c, int d) {
        humanPlayer = a;
        playerId = b; // implicit conversion from bool to int
        n = c; // number of entries on board
        symbol = d;
    }

pair<int, list<int>> player::selectMove(unordered_map<int, list<int>> validMoves) { 
        // vector<int> move;
        pair<int, list<int>> kv;
        // if (humanPlayer == true) {
            // cout << "Human Selects Move\n";
            // move = interactiveMove(validMoves);
        // }
        // else {
            cout << "Computer Selects Move\n";
            kv = computerMove(validMoves);
        // }
        return kv;
    }