using namespace std;

class othelloGame {
	othelloBoard board;

public:
	othelloGame(othelloBoard a) {
		board = a;
	}

	void computerMove() {
		board.validMoves();
		// alphabeta(); // return scores for each move 
		board.updatePositions(); // argument is new positions array
		cout << "Computer Move Completed \n";
	}

	void playerMove() {
		board.validMoves();
		board.printValidMoves(); // prints valid moves on screen for player
		// selectMove() // player selects moves 
		board.updatePositions();
		cout << "Player Move Completed \n";
	}
};