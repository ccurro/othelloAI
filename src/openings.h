#include <list>
#include <unordered_map>

using namespace std;

class openings {
	// private:
	public:	
		list<list<int>> generateData(void);
		list<list<int>> sequences;

	// public: 
    	openings();

    	pair<bool,pair<int,list<int>>> getMove(unordered_map<int, list<int>> validMoves);
};