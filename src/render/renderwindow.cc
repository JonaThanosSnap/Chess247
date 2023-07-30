#include "renderwindow.h"

RenderWindow::RenderWindow(Board* board): ChessRender{board} {
    // set up colors
    window.addColor(Color::Black, "00", "00", "00");
    window.addColor(Color::White, "ff", "ff", "ff");
    window.addColor(Color::ChessDotComBlack, "76", "96", "56");
    window.addColor(Color::ChessDotComWhite, "ee", "ee", "d2");
    window.addColor(Color::ChessDotComBg, "36", "46", "52");
}

void RenderWindow::render() {
    // Draw bg
    window.fillRectangle(0, 0, WINDOW_W, WINDOW_W, getBgColor());

    // Draw board
    for (int i = 0; i < 8; i++) {
        // TODO draw rank

        for (int j=0; j < 8; j++) {
            Coordinate c{j, 7-i};
            Piece piece = board->getSquare(c);
            
            unsigned long squareColor = isWhite(c) ? getWhiteSquareColor() : getBlackSquareColor();
            Coordinate squareTopLeft = BOARD_TOP_LEFT + c*SQUARE_W;
            window.fillRectangle(squareTopLeft.x(), squareTopLeft.y(), SQUARE_W, SQUARE_W, squareColor);
        }
    }
    
    // TODO draw file
}

unsigned long RenderWindow::getColor(Color color) const {
    return window.getColor(color);
}

unsigned long RenderWindow::getBlackSquareColor() const {
    return getColor(currentTheme.blackSquareColor);
}

unsigned long RenderWindow::getWhiteSquareColor() const {
    return getColor(currentTheme.whiteSquareColor);
}

unsigned long RenderWindow::getBgColor() const {
    return getColor(currentTheme.bgColor);
}
