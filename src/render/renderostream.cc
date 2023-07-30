#include "renderostream.h"
#include "../board.h"
#include "../piece.h"
#include "../coordinate.h"
#include "../team.h"
#include <iostream>

RenderOStream::RenderOStream(Board* board, std::ostream& out): 
    ChessRender{board}, out{out} {};

char RenderOStream::getPieceChar(const Piece& piece) const {
    // determine what char to use to display a given piece
    // use switch case for expandability + factor in team

    switch (piece.getTeam()) {
        case Team::White:
            // char displays for white team pieces
            switch(piece.getType()) {
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
                default:
                    return ' ';
            }
            break;

        case Team::Black:
            // char displays for black team pieces
            switch(piece.getType()) {
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
                default:
                    return ' ';
            }
            break;
    }

    // if not match, assume empty
    return ' ';
}

void RenderOStream::render() {
    for (int i=0; i < 8; i++) {
        // rank
        out << 8-i << " ";

        for (int j=0; j < 8; j++) {
            Coordinate c{j, 7-i};
            Piece piece = board->getSquare(c);
            
            if (piece.getType() != Piece::Type::None) {
                // there is a piece on this square
                out << getPieceChar(piece);
            } else {
                // this square is empty
                out << (isWhite(c) ? "□" : "■");
            }
        }
        out << std::endl;
    }
    out << std::endl;
    
    // file
    out << "  ";
    for (char i='a'; i <= 'h'; i++) {
        out << i;
    }
    
    out << std::endl;
}
