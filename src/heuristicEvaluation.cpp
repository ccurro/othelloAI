#include "heuristicEvaluation.h"

int ESAC(int moveNumber) {
    return 312 + 6.24*moveNumber;
}

int CMAC(int moveNumber) {
    if (moveNumber < 25) 
        return 50 + 2*moveNumber;
    if (moveNumber > 25)
        return 75 + moveNumber;
}

int heuristicEvaluation::heuristic(othelloBoard board, int nSpacesRemaining,int symbol) {
    // do heuristic from perspective of player with p.symbol = 1
    int val = 0;
    vector <int> positions = board.positions;

        //check if game is over
        unordered_map<int, list<int>> validMoves = board.validMoves(symbol);
        unordered_map<int, list<int>> otherValidMoves = board.validMoves(-symbol);
        if (validMoves.begin() == validMoves.end()) {   
            if (otherValidMoves.begin() == otherValidMoves.end()) {
                int s = accumulate(board.positions.begin(), board.positions.end(), 0);
                if (s > 0)
                    return 4567890;
                if (s < 0)
                    return -4567890;
            }
        }

        int p = validMoves.size();
        int o = otherValidMoves.size();
        int currentMobility = trunc(10 * (p - o) /(p +o + 2));

        int corners = (positions[0] + positions[7] + positions[56] + positions[63]);

        int stability = 0;
        for (auto kv : validMoves) {
            list<int> flippedDiscs = kv.second;
            stability -= flippedDiscs.size();
        }

        // go through interior positions
        int interior[] = {9,10,11,12,13,15,17,18,19,20,21,22,25,26,27,28,29,30,33,34,35,36,37,38,41,42,43,44,45,46,49,50,51,52,53,54};
        int cur, top, bot, lef, rig, tr, tl, bl, br;
        int potMobilility;
        for (int i : interior) {
            cur = positions[i];
            lef = positions[i-1];
            rig = positions[i+1];
            top = positions[i-8];
            bot = positions[i+8];
            tr  = positions[i-7];
            tl  = positions[i-9];
            bl  = positions[i+7];
            br  = positions[i+9];
            // Potential Mobility 
            // # of discs that the oppenent has adjacent to empty squares
            potMobilility = 0;
            if (cur == -1 && (lef == 0 || rig == 0 || top == 0 || bot == 0 || tr == 0 || tl == 0 || bl == 0 || br == 0))
                potMobilility++;
            // # of empty squares adjacent ot the opponents discs
            if (cur = -1 && lef == 0)
                potMobilility++;
            if (cur = -1 && rig == 0)
                potMobilility++;
            if (cur = -1 && top == 0)
                potMobilility++;
            if (cur = -1 && bot == 0)
                potMobilility++;
            if (cur = -1 && tr  == 0)
                potMobilility++;
            if (cur = -1 && tl  == 0)
                potMobilility++;
            if (cur = -1 && bl  == 0)
                potMobilility++;
            if (cur = -1 && br  == 0)
                potMobilility++;
        }

        // go through exterior positions 
        // go through top positions
        int topa[] = {1,2,3,4,5,6};
        for (int i : topa) {
            cur = positions[i];
            lef = positions[i-1];
            rig = positions[i+1];
            if (cur == -1 && (lef == 0 || rig == 0))
                potMobilility++;
            // # of empty squares adjacent ot the opponents discs
            if (cur = -1 && lef == 0)
                potMobilility++;
            if (cur = -1 && rig == 0)
                potMobilility++;
        }

        // go through bottom positions
        int bota[] = {57,58,59,60,61,62};
        for (int i : bota) {
            cur = positions[i];
            lef = positions[i-1];
            rig = positions[i+1];
             if (cur == -1 && (lef == 0 || rig == 0))
                potMobilility++;
            // # of empty squares adjacent ot the opponents discs
            if (cur = -1 && lef == 0)
                potMobilility++;
            if (cur = -1 && rig == 0)
                potMobilility++;
        }

        // go through left positions
        int lefa[] = {8,16,24,32,40,48};
        for (int i : lefa) {
            cur = positions[i];
            bot = positions[i-8];
            top = positions[i+8];
             if (cur == -1 && (top == 0 || bot == 0 ))
                potMobilility++;
            // # of empty squares adjacent ot the opponents discs
            if (cur = -1 && top == 0)
                potMobilility++;
            if (cur = -1 && bot  == 0)
                potMobilility++;
        }

        // go through right positions
        int riga[] = {15,23,31,39,47,55};
        for (int i : riga) {
            cur = positions[i];
            bot = positions[i-8];
            top = positions[i+8];
             if (cur == -1 && (top == 0 || bot == 0 ))
                potMobilility++;
            // # of empty squares adjacent ot the opponents discs
            if (cur = -1 && top == 0)
                potMobilility++;
            if (cur = -1 && bot  == 0)
                potMobilility++;
        }

        // val = CMAC(nSpacesRemaining + 60)*currentMobility + 99*potMobilility + 30*corners + 36*stability;
        // cout << weights[0] << endl;
        val = weights[0]*currentMobility + weights[1]*potMobilility + weights[2]*corners + weights[3]*stability;

        // cout << "Score breakdown" << endl;
        // cout << CMAC(nSpacesRemaining + 60)*currentMobility << endl;
        // cout << 99*potMobilility << endl;
        // cout << corners << endl;
        // cout << 36*stability << endl;

    return val;
}


heuristicEvaluation::heuristicEvaluation() {

}

// int main() {
// 	cout << "Hello World";
// }