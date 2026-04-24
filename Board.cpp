#include "Board.h"
#include <iostream>
using namespace std;

void Board::initialize() {

    // black pieces
    board[0][0]='r'; board[0][1]='n'; board[0][2]='b'; board[0][3]='q';
    board[0][4]='k'; board[0][5]='b'; board[0][6]='n'; board[0][7]='r';
    for(int i=0; i<8; i++) board[1][i]='p';

    // empty
    for(int i=2; i<6; i++){
        for(int j=0; j<8; j++){
            board[i][j]='.';
        }
    }

    // white pieces
    board[7][0]='R'; board[7][1]='N'; board[7][2]='B'; board[7][3]='Q';
    board[7][4]='K'; board[7][5]='B'; board[7][6]='N'; board[7][7]='R';
    for(int i=0; i<8; i++) board[6][i]='P';
}

void Board::print() {
    cout<<"\n  a b c d e f g h\n";
    for(int i=0; i<8; i++){
        cout<<8-i<<" ";
        for(int j=0; j<8; j++){
            cout<<board[i][j]<<" ";
        }
        cout<<8-i<<endl;
    }
    cout<<"  a b c d e f g h\n";
}

void Board::makeMove(Move m) {
    board[m.endRow][m.endCol] = board[m.startRow][m.startCol];
    board[m.startRow][m.startCol] = '.';
}

vector<Move> Board::getPawnMoves(int r, int c) {
    vector<Move> moves;

    // White pawn
    if (board[r][c] == 'P') {
        // forward
        if (board[r-1][c] == '.')
            moves.push_back({r, c, r-1, c});

        // capture left
        if (c > 0 && islower(board[r-1][c-1]))
            moves.push_back({r, c, r-1, c-1});

        // capture right
        if (c < 7 && islower(board[r-1][c+1]))
            moves.push_back({r, c, r-1, c+1});
    }

    // Black pawn
    if (board[r][c] == 'p') {
        if (board[r+1][c] == '.')
            moves.push_back({r, c, r+1, c});

        if (c > 0 && isupper(board[r+1][c-1]))
            moves.push_back({r, c, r+1, c-1});

        if (c < 7 && isupper(board[r+1][c+1]))
            moves.push_back({r, c, r+1, c+1});
    }

    return moves;
}

vector<Move> Board::getKnightMoves(int r, int c) {
    vector<Move> moves;

    int dr[] = {-2,-2,-1,-1,1,1,2,2};
    int dc[] = {-1,1,-2,2,-2,2,-1,1};

    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) {
            char target = board[nr][nc];

            if (board[r][c] == 'N' && !isupper(target))
                moves.push_back({r,c,nr,nc});

            if (board[r][c] == 'n' && !islower(target))
                moves.push_back({r,c,nr,nc});
        }
    }

    return moves;
}

vector<Move> Board::getAllMoves(bool whiteTurn) {
    vector<Move> allMoves;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            char piece = board[i][j];

            // =========================
            // WHITE MOVES
            // =========================
            if (whiteTurn && isupper(piece)) {

                if (piece == 'P') {
                    auto m = getPawnMoves(i, j);
                    allMoves.insert(allMoves.end(), m.begin(), m.end());
                }

                else if (piece == 'N') {
                    auto m = getKnightMoves(i, j);
                    allMoves.insert(allMoves.end(), m.begin(), m.end());
                }

                else if (piece == 'R') {
                    auto m = getRookMoves(i, j);
                    allMoves.insert(allMoves.end(), m.begin(), m.end());
                }

                else if (piece == 'B') {
                    auto m = getBishopMoves(i, j);
                    allMoves.insert(allMoves.end(), m.begin(), m.end());
                }

                else if (piece == 'Q') {
                    auto m = getQueenMoves(i, j);
                    allMoves.insert(allMoves.end(), m.begin(), m.end());
                }
            }

            // =========================
            // BLACK MOVES
            // =========================
            else if (!whiteTurn && islower(piece)) {

                if (piece == 'p') {
                    auto m = getPawnMoves(i, j);
                    allMoves.insert(allMoves.end(), m.begin(), m.end());
                }

                else if (piece == 'n') {
                    auto m = getKnightMoves(i, j);
                    allMoves.insert(allMoves.end(), m.begin(), m.end());
                }

                else if (piece == 'r') {
                    auto m = getRookMoves(i, j);
                    allMoves.insert(allMoves.end(), m.begin(), m.end());
                }

                else if (piece == 'b') {
                    auto m = getBishopMoves(i, j);
                    allMoves.insert(allMoves.end(), m.begin(), m.end());
                }

                else if (piece == 'q') {
                    auto m = getQueenMoves(i, j);
                    allMoves.insert(allMoves.end(), m.begin(), m.end());
                }
            }
        }
    }

    return allMoves;
}

vector<Move> Board::getRookMoves(int r, int c) {
    vector<Move> moves;

    int directions[4][2] = {
        {-1,0}, {1,0}, {0,-1}, {0,1}
    };

    for (auto& d : directions) {
        int nr = r + d[0];
        int nc = c + d[1];

        while (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) {
            char target = board[nr][nc];

            if (board[r][c] == 'R') {
                if (target == '.') {
                    moves.push_back({r,c,nr,nc});
                } else {
                    if (islower(target)) moves.push_back({r,c,nr,nc});
                    break;
                }
            }

            if (board[r][c] == 'r') {
                if (target == '.') {
                    moves.push_back({r,c,nr,nc});
                } else {
                    if (isupper(target)) moves.push_back({r,c,nr,nc});
                    break;
                }
            }

            nr += d[0];
            nc += d[1];
        }
    }

    return moves;
}

vector<Move> Board::getBishopMoves(int r, int c) {
    vector<Move> moves;

    int directions[4][2] = {
        {-1,-1}, {-1,1}, {1,-1}, {1,1}
    };

    for (auto& d : directions) {
        int nr = r + d[0];
        int nc = c + d[1];

        while (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) {
            char target = board[nr][nc];

            if (board[r][c] == 'B') {
                if (target == '.') {
                    moves.push_back({r,c,nr,nc});
                } else {
                    if (islower(target)) moves.push_back({r,c,nr,nc});
                    break;
                }
            }

            if (board[r][c] == 'b') {
                if (target == '.') {
                    moves.push_back({r,c,nr,nc});
                } else {
                    if (isupper(target)) moves.push_back({r,c,nr,nc});
                    break;
                }
            }

            nr += d[0];
            nc += d[1];
        }
    }

    return moves;
}

vector<Move> Board::getQueenMoves(int r, int c) {
    vector<Move> moves;

    auto rookMoves = getRookMoves(r,c);
    auto bishopMoves = getBishopMoves(r,c);

    moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());
    moves.insert(moves.end(), bishopMoves.begin(), bishopMoves.end());

    return moves;
}

int Board::evaluate() {
    int score = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            char piece = board[i][j];

            switch(piece) {

                // White pieces → +score
                case 'P': score += 1; break;
                case 'N': score += 3; break;
                case 'B': score += 3; break;
                case 'R': score += 5; break;
                case 'Q': score += 9; break;
                case 'K': score += 1000; break;

                // Black pieces → -score
                case 'p': score -= 1; break;
                case 'n': score -= 3; break;
                case 'b': score -= 3; break;
                case 'r': score -= 5; break;
                case 'q': score -= 9; break;
                case 'k': score -= 1000; break;
            }
        }
    }

    return score;
}