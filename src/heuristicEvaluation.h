#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include <numeric>
#include <limits>
#include <algorithm>  
#include <ratio>
#include "board.h"

using namespace std;

class heuristicEvaluation {
	private:

	public:
		vector<int> weights;
		int hIndex = 0;
    	int heuristic(othelloBoard board, int nSpacesRemaining, int symbol);
	    heuristicEvaluation();
};