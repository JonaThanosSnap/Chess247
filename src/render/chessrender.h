#ifndef CHESS_RENDER_H_
#define CHESS_RENDER_H_

// forward declaration for board ptr
class Board;

class ChessRender {
protected:
    // protect both memory address and changes to board
    const Board* const board;
public:
    ChessRender(Board*);
    virtual void render() const = 0;
};

#endif
