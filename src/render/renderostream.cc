#include "renderostream.h"
#include "board.h"
#include "piece.h"
#include "coordinate.h"
#include <iostream>

class Piece;

RenderOStream::RenderOStream(Board* board, std::ostream& out): 
    ChessRender{board}, out{out} {};

void RenderOStream::render() const {
    for (int i=0; i < 8; i++) {
        // rank
        out << 8-i << " ";

        for (int j=0; j < 8; j++) {
            Coordinate c{i, j};
            Piece* piece = board->getPiece(c);
            
            if (piece != nullptr) {
                // there is a piece on this square
                out << piece->getChar();
            } else {
                // this square is empty
                out << c.isWhite() ? ' ' : '_';
            }
        }
        out << std::endl;
    }
    out << std::endl;
    
    // file
    out << "  ";
    for (int i='a'; i <= 'h'; i++) {
        out << i;
    }
    
    out << std::endl;
}
