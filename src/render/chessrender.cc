#include "chessrender.h"
#include "../board.h"

ChessRender::ChessRender(Board* board): board{board} {};

ChessRender::~ChessRender() {}

bool ChessRender::isWhite(const Coordinate& c) const {
    // define black and white split as follows:
    //  - set a1 to be black
    //  - every square adjacent to a given square is the opposite colour
    
    // we find that if the parities are equal, render as black
    //  otherwise, white

    if (c.x() % 2 == c.y() % 2) {
        // black square
        return false;
    } else {
        // white square
        return true;
    }
}
