#ifndef RENDER_WINDOW_H_
#define RENDER_WINDOW_H_

#include "../coordinate.h"
#include "../piece.h"
#include "chessrender.h"

class RenderWindow : public ChessRender {
    // you may only construct a RenderWindow
    // given a board to reference
    RenderWindow(Board* board);
    void render() const override;
};

#endif
