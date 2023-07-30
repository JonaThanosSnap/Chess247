#include "aiplayerlevel1.h"
#include "../../coordinate.h"
#include <utility>

AIPlayerLevel1::AIPlayerLevel1(Board* board): AIPlayer{board} {};

std::pair<Coordinate, Coordinate> getMove() {
    // return a random legal move

    // to do this, we:
    //  1. call board.getValidMoves(p) for each p on this team
    //  2. call board.isValidMove(m) for each move from (1)
    //  3. randomly choose a move from (2) and return the pairl
    return std::make_pair(Coordinate{-1, -1}, Coordinate{-1, -1});
}

