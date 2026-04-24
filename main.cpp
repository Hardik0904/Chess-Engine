#include <iostream>
#include "Board.h"
using namespace std;

Move parseMove(string from, string to) {
    Move m;
    m.startCol = from[0] - 'a';
    m.startRow = 8 - (from[1] - '0');
    m.endCol = to[0] - 'a';
    m.endRow = 8 - (to[1] - '0');
    return m;
}

bool isValidMove(Move m, vector<Move>& moves) {
    for (auto& mv : moves) {
        if (mv.startRow == m.startRow &&
            mv.startCol == m.startCol &&
            mv.endRow == m.endRow &&
            mv.endCol == m.endCol)
            return true;
    }
    return false;
}

int main() {
    Board b;
    b.initialize();

    bool whiteTurn = true;

    while (true) {
        b.print();

        vector<Move> moves = b.getAllMoves(whiteTurn);

        string from, to;
        cin >> from >> to;

        Move m = parseMove(from, to);

        if (isValidMove(m, moves)) {
            b.makeMove(m);
            whiteTurn = !whiteTurn;
        } else {
            cout << "Invalid move!\n";
        }
    }
}