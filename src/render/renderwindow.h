#ifndef RENDER_WINDOW_H_
#define RENDER_WINDOW_H_

#include "../board.h"
#include "../coordinate.h"
#include "../piece.h"
#include "window.h"
#include "chessrender.h"

const unsigned int WINDOW_W = 600;
const unsigned int BOARD_W = 512;
const unsigned int SQUARE_W = BOARD_W/BOARD_WIDTH;
const unsigned int PIECE_W = 48;
const unsigned int BOARD_MARGIN = (WINDOW_W - BOARD_W)/2;
const Coordinate BOARD_TOP_LEFT = Coordinate{BOARD_MARGIN, BOARD_MARGIN};

enum Color {
    White = 0,
    Black,
    ChessDotComWhite,
    ChessDotComBlack,
    ChessDotComBg
};

struct BoardTheme {
    Color blackSquareColor;
    Color whiteSquareColor;
    Color bgColor;
    Color textColor;
};

class RenderWindow : public ChessRender {
    Xwindow window{WINDOW_W, WINDOW_W};

    BoardTheme currentTheme = BoardTheme{
        Color::ChessDotComBlack,
        Color::ChessDotComWhite,
        Color::ChessDotComBg,
        Color::ChessDotComWhite
    };

    void addPieceSet(std::string folder_path);

    public:
        RenderWindow(Board* board);
        void render() override;
};

#endif
