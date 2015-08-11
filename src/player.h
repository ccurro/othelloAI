using namespace std;

class player {
    bool humanPlayer;
    int playerId;
    int n;

    vector<int> computerMove(unordered_map<int, vector<int>> validMoves);

    vector<int> interactiveMove(unordered_map<int, vector<int>> validMoves);

public:
    player(bool a, bool b, int c);

    vector<int> selectMove(unordered_map<int, vector<int>> validMoves);
};