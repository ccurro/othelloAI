using namespace std;

class othelloBoard {
	const static int width = 8;
	const static int height = 8;
	const static int n = width*height;
	array<int, n> positions = {};

public:	

	// void firstMove() {
	// 	// positions[0] = 1;
	// 	positions[27] = 1;
	// 	positions[28] = -1;
	// 	positions[35] = -1;
	// 	positions[36] = 1;
	// }

	void draw() {
		// for (int i = 0; i < n; i++)
			// cout << positions[i];
		for (int i = 0; i < n; i+=8 ) {
			for (int j = i; j < i+8; j++) {
				// cout << j << " ";
				if (positions[j] == 1)
					cout << "\u2572\u2571" ;
				if (positions[j] == -1)
					cout << "\u259F\u2599";
				if (positions[j] == 0)
					cout << "\u2518\u2514";
			}
			cout << endl;
			for (int j = i; j < i+8; j++) {
				if (positions[j] == 1)
					cout << "\u2571\u2572" ;
				if (positions[j] == -1)
					cout << "\u259C\u259B";
				if (positions[j] == 0)
					cout << "\u2510\u250C";
			}
			cout << endl;
		}
	}

	void validMoves () {

	}

	void printValidMoves () {

	}

	void updatePositions () {
		
	}

};