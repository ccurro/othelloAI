#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include "player.h"

using namespace std;

pair<int, list<int>> player::computerMove(unordered_map<int, list<int>> validMoves) {
        // vector<int> move;
        //all of the alphabeta work.

        // Pick Random move
        // unordered_map<int, list<int>>::iterator kv = validMoves.begin();
        // pair<int, list<int>> move = *kv;

        // Pick move that maximizes discs flipped
        int nDiscs = 0;
        pair<int, list<int>> move;
        for (auto kv : validMoves) {
            list<int> flips = kv.second;
            if (flips.size() > nDiscs) {
                move = kv;
                nDiscs = flips.size();
            }
        }

        return move;
    }
pair<int, list<int>> player::interactiveMove(unordered_map<int, list<int>> validMoves) {
        pair<int, list<int>> move;
        int ind;
        //interactive selection from list.

        cout << "Pick Move: ";
        cin >> ind;

        int i;
        for (auto kv : validMoves) {
            move = kv;
            i++;
            if (i == ind)
                break;
        }

        return move;
    }

player::player(bool a, bool b, int c, int d) {
        humanPlayer = a;
        playerId = b; // implicit conversion from bool to int
        n = c; // number of entries on board
        symbol = d;
    }

pair<int, list<int>> player::selectMove(othelloBoard board, unordered_map<int, list<int>> validMoves) { 
        // vector<int> move;
        pair<int, list<int>> kv;
        if (humanPlayer == true) {
            cout << "Human Selects Move\n";
            kv = interactiveMove(validMoves);
        }
        else {
            cout << "Computer Selects Move\n";
            kv = computerMove(validMoves);
        }
        return kv;
    }