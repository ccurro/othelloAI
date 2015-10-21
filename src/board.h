#include <list>

using namespace std;

class othelloBoard {
private:
    const static int width  = 8;
    const static int height = 8;

    void validMovesHelper(int clr, int i, int inc, unordered_map<int, list<int>> & pieces);
    void ind2sub(const int sub,const int cols,const int rows,int *row,int *col);

public: 
    const static int n = width*height;
    vector<int> positions;

    int nMoves = 0;

    othelloBoard();

    void draw(unordered_map<int, list<int>> moves, int symbol);
    unordered_map<int, list<int>> validMoves (int symbol);

    void updatePositions(pair<int, list<int>> move, int symbol);
};