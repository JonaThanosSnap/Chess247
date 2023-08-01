#include "chessrender.h"
#include "../board.h"

/////////////////////////////////////
//                                 //
//   Chess Render Implementation   //
//                                 //
/////////////////////////////////////

// constructor
ChessRender::ChessRender(Board* board): board{board} {};

// destructor
ChessRender::~ChessRender() {}

// check if a square is white or black
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
