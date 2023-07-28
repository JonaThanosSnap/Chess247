#ifndef RENDER_OSTREAM_H_
#define RENDER_OSTREAM_H_
#include "chessrender.h"
#include "../coordinate.h"
#include <iostream>

// forward declaration for Board,Piece ptr
class Board;
class Piece;

class RenderOStream : public ChessRender{
private:
    std::ostream& out;
public:
    // you may only construct a RenderOStream given a
    // board to reference and ostream to print to
    RenderOStream(Board* board, std::ostream&);
    void render() const override;
    // determine if a given square should be rendered as 
    //  blank vs underscore(_)
    bool isWhite(const Coordinate&) const;
    char getPieceChar(const Piece&) const;
};

#endif
