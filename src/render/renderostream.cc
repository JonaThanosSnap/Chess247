#include "renderostream.h"
#include "board.h"
#include "piece.h"
#include "coordinate.h"
#include "team.h"
#include <iostream>

class Piece;

RenderOStream::RenderOStream(Board* board, std::ostream& out): 
    ChessRender{board}, out{out} {};

bool RenderOStream::isWhite(Coordinate& c) const {
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

char RenderOStream::getPieceChar(Piece* piece) const {
    // determine what char to use to display a given piece
    // use switch case for expandability + factor in team

    switch (piece->getTeam()) {
        case Team::White:
            // char displays for white team pieces
            switch(piece->getPieceType()) {
                case Piece::Type::Pawn:
                    return 'P';
                    break;
                case Piece::Type::Rook:
                    return 'R';
                    break;
                case Piece::Type::Knight:
                    return 'N';
                    break;
                case Piece::Type::Bishop:
                    return 'B';
                    break;
                case Piece::Type::Queen:
                    return 'Q';
                    break;
                case Piece::Type::King:
                    return 'K';
                    break;
            }
            break;

        case Team::Black:
            // char displays for black team pieces
            switch(piece->getPieceType()) {
                case Piece::Type::Pawn:
                    return 'p';
                    break;
                case Piece::Type::Rook:
                    return 'r';
                    break;
                case Piece::Type::Knight:
                    return 'n';
                    break;
                case Piece::Type::Bishop:
                    return 'b';
                    break;
                case Piece::Type::Queen:
                    return 'q';
                    break;
                case Piece::Type::King:
                    return 'k';
                    break;
            }
            break;
    }

    // if not match, assume empty
    return ' ';
}

void RenderOStream::render() const {
    for (int i=0; i < 8; i++) {
        // rank
        out << 8-i << " ";

        for (int j=0; j < 8; j++) {
            Coordinate c{i, j};
            Piece* piece = board->getSquare(c);
            
            if (piece != nullptr) {
                // there is a piece on this square
                out << getPieceChar(piece);
            } else {
                // this square is empty
                out << isWhite(c) ? ' ' : '_';
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
