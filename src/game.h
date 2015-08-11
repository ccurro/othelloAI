using namespace std;

class othelloGame {

othelloBoard* board;

public:
    bool complete = false; // boolean if game is complete or not.
    bool newGame = true;
    bool humanPlayer, humanPlayerFirst;

    othelloGame(othelloBoard* a, bool b, bool c);

    void firstMove();

    void move(player p);

    void statusUpdate();
};