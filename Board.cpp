#include "Board.h"
#include <climits>
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

    int dirs[4][2] = {
        {-1,0}, {1,0}, {0,-1}, {0,1}
    };

    char piece = board[r][c];
    bool white = isupper(piece);

    for (auto &d : dirs) {
        int nr = r + d[0];
        int nc = c + d[1];

        while (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) {
            char target = board[nr][nc];

            if (target == '.') {
                moves.push_back({r,c,nr,nc});
            } 
            else {
                if (white && islower(target))
                    moves.push_back({r,c,nr,nc});
                else if (!white && isupper(target))
                    moves.push_back({r,c,nr,nc});

                break; // always stop
            }

            nr += d[0];
            nc += d[1];
        }
    }

    return moves;
}

vector<Move> Board::getBishopMoves(int r, int c) {
    vector<Move> moves;

    int dirs[4][2] = {
        {-1,-1}, {-1,1}, {1,-1}, {1,1}
    };

    char piece = board[r][c];
    bool white = isupper(piece);

    for (auto &d : dirs) {
        int nr = r + d[0];
        int nc = c + d[1];

        while (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) {
            char target = board[nr][nc];

            if (target == '.') {
                moves.push_back({r,c,nr,nc});
            } 
            else {
                if (white && islower(target))
                    moves.push_back({r,c,nr,nc});
                else if (!white && isupper(target))
                    moves.push_back({r,c,nr,nc});

                break;
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


int Board::minimax(int depth, bool isMaximizing) {
    if (depth == 0) {
        return evaluate();
    }

    vector<Move> moves = getAllMoves(isMaximizing);

    if (moves.empty()) {
        return evaluate();
    }

    if (isMaximizing) {
        int best = INT_MIN;

        for (auto move : moves) {
            char captured = board[move.endRow][move.endCol];

            makeMove(move);

            int score = minimax(depth - 1, false);

            // undo move
            board[move.startRow][move.startCol] = board[move.endRow][move.endCol];
            board[move.endRow][move.endCol] = captured;

            best = max(best, score);
        }

        return best;
    } else {
        int best = INT_MAX;

        for (auto move : moves) {
            char captured = board[move.endRow][move.endCol];

            makeMove(move);

            int score = minimax(depth - 1, true);

            // undo move
            board[move.startRow][move.startCol] = board[move.endRow][move.endCol];
            board[move.endRow][move.endCol] = captured;

            best = min(best, score);
        }

        return best;
    }
}

Move Board::findBestMove(int depth) {
    vector<Move> moves = getAllMoves(false); // AI = black

    int bestScore = INT_MAX;
    Move bestMove;

    for (auto move : moves) {
        char captured = board[move.endRow][move.endCol];

        makeMove(move);

        int score = minimax(depth - 1, true);

        // undo
        board[move.startRow][move.startCol] = board[move.endRow][move.endCol];
        board[move.endRow][move.endCol] = captured;

        if (score < bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
}