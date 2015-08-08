using namespace std;

class othelloBoard {
private:
    const static int width  = 8;
    const static int height = 8;

public: 
    const static int n = width*height;
    vector<int> positions;

    othelloBoard() {
        positions.assign(64,0);
        positions[1] = 1;
    }

    void draw() {
        for (int i = 0; i < n; i+=height ) {
            for (int j = i; j < i+width; j++) {
                cout << positions[j] << " ";
                // if (positions[j] == 1)
                //     cout << "\u2572\u2571" ;
                // if (positions[j] == -1)
                //     cout << "\u259F\u2599";
                // if (positions[j] == 0)
                //     cout << "\u2518\u2514";
            }
            cout << endl;
            // for (int j = i; j < i+width; j++) {
            //     if (positions[j] == 1)
            //         cout << "\u2571\u2572" ;
            //     if (positions[j] == -1)
            //         cout << "\u259C\u259B";
            //     if (positions[j] == 0)
            //         cout << "\u2510\u250C";
            // }
            // cout << endl;
        }
    }

    unordered_map<int, vector<int>> validMoves () {
        unordered_map<int, vector<int>> moves;
        return moves;
    }

    void printValidMoves () {

    }

    void updatePositions (vector<int> newPositions) {
        positions = newPositions;
    }

};