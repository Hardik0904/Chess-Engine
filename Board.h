#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "Move.h"

class Board {
public:
    char board[8][8];

    void initialize();
    void print();
    void makeMove(Move m);
    int evaluate();
    int minimax(int depth, bool isMaximizing);
    Move findBestMove(int depth);

    std::vector<Move> getPawnMoves(int r, int c);
    std::vector<Move> getKnightMoves(int r, int c);
    std::vector<Move> getAllMoves(bool whiteTurn);
    std::vector<Move> getRookMoves(int r, int c);
    std::vector<Move> getBishopMoves(int r, int c);
    std::vector<Move> getQueenMoves(int r, int c);
};

#endif