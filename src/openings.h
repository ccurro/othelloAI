#include <list>
#include <unordered_map>

using namespace std;

class openings {
	// private:
	public:	
		list<list<int>> generateData(int symbol);
		list<list<int>> sequences;

	// public: 
    	openings();

    	// pair<bool,pair<int,list<int>>> getMove(unordered_map<int, list<int>> validMoves);
    	pair<bool,pair<int,list<int>>> getMove(unordered_map<int, list<int>> validMoves ,list<int> pastMoves);
};