#include "heuristicEvaluation.h"

void ind2sub(const int sub,const int cols,const int rows,int *row,int *col) {
   *row=sub/cols;
   *col=sub%cols;
}

void stableDiscsHelper(vector <int> positions, int i, int inc, bool & enemyPieceInline, bool & blankPieceInLine) {
    list<int> candidates;
    for (int j = inc; (i + j < 65) && (i + j > -1); j+=inc) {
        // first check to make sure don't wrap around board
        // check to see that diff in cols and rows doesn't exceed 1
        // only do after first loop
        if (j != i) {
            int crow, ccol, prow, pcol;
            ind2sub(i+j-inc, 8, 8, &prow, &pcol);
            ind2sub(i+j,     8, 8, &crow, &ccol);
            if (abs(crow - prow) > 1 || abs(ccol - pcol) > 1 )
                break;
        }
        int pos = positions[i+j];
        if (pos == 1)
            break;
        if (pos == -1) {
        	enemyPieceInline = true;
        	return;
        }
        if (pos == 0) {
        	blankPieceInLine = true;
        	return;
        }
    }
}

int stableDiscs (vector <int> positions) {
	int nStable = 0;
    for (int i = 0; i < 65; i+=1) {
    		bool stillStable = true;
            if (positions[i] == 0)
                continue;
            if (positions[i] == 1) {
                // go through columns
                bool enemyPieceInlineU = false;
			    bool blankPieceInLineU = false;
                stableDiscsHelper(positions, i,  8, enemyPieceInlineU, blankPieceInLineU);
                bool enemyPieceInlineD = false;
			    bool blankPieceInLineD = false;
                stableDiscsHelper(positions, i, -8, enemyPieceInlineD, blankPieceInLineD);
                if ((!enemyPieceInlineD && !blankPieceInLineU) && (!enemyPieceInlineU && !blankPieceInLineD) && (!blankPieceInLineU && !blankPieceInLineD)) {
                	// then still stable
                } else {
                	stillStable = false;
                	// def not stable
                }
                // go through rows
                enemyPieceInlineU = false;
			    blankPieceInLineU = false;
                stableDiscsHelper(positions, i,  1, enemyPieceInlineU, blankPieceInLineU);
                enemyPieceInlineD = false;
			    blankPieceInLineD = false;
                stableDiscsHelper(positions, i, -1, enemyPieceInlineD, blankPieceInLineD);
                if ((!enemyPieceInlineD && !blankPieceInLineU) && (!enemyPieceInlineU && !blankPieceInLineD) && (!blankPieceInLineU && !blankPieceInLineD)) {
                	// then still stable
                } else {
                	stillStable = false;
                	// def not stable
                }
                // go through diagnols
                enemyPieceInlineU = false;
			    blankPieceInLineU = false;
                stableDiscsHelper(positions, i, -7, enemyPieceInlineU, blankPieceInLineU);
                enemyPieceInlineD = false;
			    blankPieceInLineD = false;
                stableDiscsHelper(positions, i,  7, enemyPieceInlineD, blankPieceInLineD);
                if ((!enemyPieceInlineD && !blankPieceInLineU) && (!enemyPieceInlineU && !blankPieceInLineD) && (!blankPieceInLineU && !blankPieceInLineD)) {
                	// then still stable
                } else {
                	stillStable = false;
                	// def not stable
                }
                enemyPieceInlineU = false;
			    blankPieceInLineU = false;
                stableDiscsHelper(positions, i, -9, enemyPieceInlineU, blankPieceInLineU);
                enemyPieceInlineD = false;
			    blankPieceInLineD = false;
                stableDiscsHelper(positions, i,  9, enemyPieceInlineD, blankPieceInLineD);
                if ((!enemyPieceInlineD && !blankPieceInLineU) && (!enemyPieceInlineU && !blankPieceInLineD) && (!blankPieceInLineU && !blankPieceInLineD)) {
                	// then still stable
                } else {
                	stillStable = false;
                	// def not stable
                }
            }
            if (positions[i] == -1)
                continue;
            if (stillStable == true)
	        	nStable++;	
        }
        return nStable;
}


int ESAC(int moveNumber) {
    return 312 + 6.24*moveNumber;
}

int CMAC(int moveNumber) {
    if (moveNumber < 25) 
        return 50 + 2*moveNumber;
    if (moveNumber > 25)
        return 75 + moveNumber;
}

// int heuristicEvaluation::heuristic(othelloBoard board, int nSpacesRemaining,int symbol) {
//     // do heuristic from perspective of player with p.symbol = 1
// 	int val = 0;
// 	vector <int> positions = board.positions;

// 	unordered_map<int, list<int>> validMoves = board.validMoves(1);
// 	unordered_map<int, list<int>> otherValidMoves = board.validMoves(-1);

// 	// board.draw(validMoves,1);

// 	// cout << validMoves.size() << endl;
// 	// cout << (validMoves.begin() == validMoves.end()) << endl;

//     //check if game is over		
// 	if ((validMoves.begin() == validMoves.end()) || (nSpacesRemaining == 0)) {   
// 		if ((otherValidMoves.begin() == otherValidMoves.end()) || (nSpacesRemaining == 0)) {
// 			int s = accumulate(board.positions.begin(), board.positions.end(), 0);
// 			if (s > 0) {
//                 	// cout << "White wins!" << endl;
// 				return 45678900 + s;
// 			}
// 			if (s < 0) {
//                 	// cout << "Black wins!" << endl;
// 				return -45678900 + s;
// 			}
// 		}
// 	}

// 	// coin parity
// 	int d = accumulate(board.positions.begin(), board.positions.end(), 0);
// 	int t = inner_product(board.positions.begin(),board.positions.end(),board.positions.begin(),0);
// 	double parity = 100*d/t;

// 	//corners
// 	double corners;
// 	int cornerInds[4] = {0,7,56,63};
// 	int pCorners = 0;
// 	int oCorners = 0;

// 	for (auto i : cornerInds) {
// 		if (positions[i] == 1) {
// 			pCorners++;
// 		} else if (positions[i] == -1) {
// 			oCorners++;
// 		}
// 	} 


// 	if (positions[0] + positions[7] + positions[56] + positions[63] != 0) {
// 		corners = 100 * (pCorners - oCorners) / (pCorners + oCorners);
// 	} else {
// 		corners = 0;
// 	}

// 	// mobility
// 	int	p = validMoves.size();
// 	int	o = otherValidMoves.size();

// 	double mobility;
// 	if (p > o) {
// 		mobility = (100*p)/(p+o);
// 	} else if (p < o) {
// 		mobility = -(100*o)/(p+o);
// 	} else {
// 		mobility = 0;
// 	}

// 	// cout << "Scores" << endl;
// 	// cout << mobility << endl;
// 	// cout << corners << endl;
// 	// cout << parity << endl;
// 	// board.draw(validMoves,1);
// 	// exit(-1);

// 	return round(CMAC(60 - nSpacesRemaining)*(mobility) + (801.724 * corners) + (10 * parity)); // + 1000*stableDiscs(positions));
// }


int heuristicEvaluation::heuristic(othelloBoard board, int nSpacesRemaining,int symbol) {
    // do heuristic from perspective of player with p.symbol = 1
    int val = 0;
    vector <int> positions = board.positions;

        //check if game is over
        unordered_map<int, list<int>> validMoves = board.validMoves(1);
        unordered_map<int, list<int>> otherValidMoves = board.validMoves(-1);
        if (validMoves.begin() == validMoves.end() || nSpacesRemaining == 0) {   
            if (otherValidMoves.begin() == otherValidMoves.end() || nSpacesRemaining == 0) {
                int s = accumulate(board.positions.begin(), board.positions.end(), 0);
                if (s > 0) {
                	// cout << "White wins!" << endl;
                    return 45678900;
                }
                if (s < 0) {
                	// cout << "Black wins!" << endl;
                    return -45678900;
                }
            }
        }

        int p = validMoves.size();
        int o = otherValidMoves.size();
        // for (auto move : validMoves) {
        // 	othelloBoard scratchBoard = board;
        // 	scratchBoard.validMoves(-symbol)
        // }

        int currentMobility = trunc(1000 * (p - o) /(p +o + 2));

        // int corners = (positions[0] + positions[7] + positions[56] + positions[63]);


	//corners
        double corners;
        int cornerInds[4] = {0,7,56,63};
        int pCorners = 0;
        int oCorners = 0;

        for (auto i : cornerInds) {
        	if (positions[i] == 1) {
        		pCorners++;
        	} else if (positions[i] == -1) {
        		oCorners++;
        	}
        } 


        if (positions[0] + positions[7] + positions[56] + positions[63] != 0) {
        	corners = 100 * (pCorners - oCorners) / (pCorners + oCorners);
        } else {
        	corners = 0;
        }

        // int stability = 0;
        // for (auto kv : validMoves) {
        //     list<int> flippedDiscs = kv.second;
        //     stability -= flippedDiscs.size();
        // }

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
        // val = weights[0]*currentMobility + weights[1]*potMobilility + weights[2]*corners + weights[3]*stability;
        val = weights[0]*CMAC(nSpacesRemaining + 60)*currentMobility + weights[1]*99*potMobilility + weights[2]*30*corners; + 36*weights[3]*stableDiscs(positions);
        // val = rand() % 100;
        // val = stableDiscs(positions) + p - o;

        // cout << "Stable Discs " << stableDiscs(positions) << endl;
        // cout << "Score breakdown" << endl;
        // cout << CMAC(nSpacesRemaining + 60)*currentMobility << endl;
        // cout << 99*potMobilility << endl;
        // cout << 30*corners << endl;
        // cout << 36*stability << endl;

    return val;
}

// int heuristicEvaluation::heuristic(othelloBoard board, int nSpacesRemaining,int symbol) {
//     // do heuristic from perspective of player with p.symbol = 1
//     int val = 0;
//     vector <int> positions = board.positions;

//         //check if game is over
//         int s = accumulate(board.positions.begin(), board.positions.end(), 0);		
//         unordered_map<int, list<int>> validMoves = board.validMoves(1);
//         unordered_map<int, list<int>> otherValidMoves = board.validMoves(-1);
//         if (validMoves.begin() == validMoves.end() || nSpacesRemaining == 0) {   
//             if (otherValidMoves.begin() == otherValidMoves.end() || nSpacesRemaining == 0) {
//                 if (s > 0) {
//                 	// board.draw(validMoves,1);
//                 	// exit(-1);
//                 	cout << "White wins!" << endl;
//                     return 45678900;
//                 }
//                 if (s < 0) {
//                 	cout << "Black wins!" << endl;
//                     return -45678900;
//                 }
//             }
//         }

//         int p = validMoves.size();
//         int o = otherValidMoves.size();
//         // for (auto move : validMoves) {
//         // 	othelloBoard scratchBoard = board;
//         // 	scratchBoard.validMoves(-symbol)
//         // }

//         int currentMobility = trunc(1000 * (p - o) /(p +o + 2));

//        //  // int corners = (positions[0] + positions[7] + positions[56] + positions[63]);
//        //  int corners[4] = {positions[0], positions[7], positions[56], positions[63];
//       	// int cornerScore = 0;
//        //  if (positions[0] == 1 && positions[7] == 1) {
//        //  	cornerScore += 100;
//        //  }
//        //  if (positions[0] == 1 && positions[56] == 1) {
//        //  	cornerScore += 100;
//        //  }
//        //  if (positions[7] == 1 && positions[56] == 1) {
//        //  	cornerScore += 100;
//        //  }
//        //  if (positions[0] == 1 && positions[7] == 1 && (positions[56] == 1 || positions[63] == 1) {
//        //  	cornerScore += 1000;
//        //  } else if (positions[0] == 1 && positions[7] == 1 && (positions[56] == 1 || positions[63] == 1) {

//        //  }



//     return weights[0]*currentMobility + weights[1]*stableDiscs(positions) ;
// }

// int heuristicEvaluation::heuristic(othelloBoard board, int nSpacesRemaining,int symbol) {
//     // do heuristic from perspective of player with p.symbol = 1
//     int val = 0;
//     vector <int> positions = board.positions;

//         //check if game is over
//         int s = accumulate(board.positions.begin(), board.positions.end(), 0);		
//         unordered_map<int, list<int>> validMoves = board.validMoves(1);
//         unordered_map<int, list<int>> otherValidMoves = board.validMoves(-1);
//         if (validMoves.begin() == validMoves.end() || nSpacesRemaining == 0) {   
//             if (otherValidMoves.begin() == otherValidMoves.end() || nSpacesRemaining == 0) {
//                 if (s > 0) {
//                 	// board.draw(validMoves,1);
//                 	// exit(-1);
//                 	cout << "White wins!" << endl;
//                     return 45678900;
//                 }
//                 if (s < 0) {
//                 	cout << "Black wins!" << endl;
//                     return -45678900;
//                 }
//             }
//         }

//         vector <int> w = {
//         	 100,-100,  50,  50,  50,  50,-100, 100,
//         	-100,-100, -50, -50, -50, -50,-100,-100,
//         	  50, -50,  20,  20,  20,  20, -50,  50,
//         	  50, -50,  20,  20,  20,  20, -50,  50,
//         	  50, -50,  20,  20,  20,  20, -50,  50,
//         	  50, -50,  20,  20,  20,  20, -50,  50,
// 	       	-100,-100, -50, -50, -50, -50,-100,-100, 
// 	       	 100,-100,  50,  50,  50,  50,-100, 100
//         };

//         return inner_product(w.begin(), w.end(), positions.begin(), 0);
// }


heuristicEvaluation::heuristicEvaluation() {

}

// int main() {
// 	cout << "Hello World";
// }