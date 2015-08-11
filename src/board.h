using namespace std;

class othelloBoard {
private:
    const static int width  = 8;
    const static int height = 8;

public: 
    const static int n = width*height;
    vector<int> positions;

    othelloBoard();

    void draw();

    unordered_map<int, vector<int>> validMoves ();

    void printValidMoves();

    void updatePositions(vector<int> newPositions);
};