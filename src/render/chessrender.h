#ifndef CHESS_RENDER_H_
#define CHESS_RENDER_H_

// forward declaration for board ptr
class Board;

class ChessRender {
protected:
    // protect both memory address and changes to board
    const Board* const board;
    // check if a square is white or black
    bool isWhite(const Coordinate&) const;
public:
    ChessRender(Board*);
    virtual ~ChessRender();
    virtual void render() const = 0;
};

#endif
