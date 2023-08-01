#ifndef RENDER_WINDOW_H_
#define RENDER_WINDOW_H_

#include "../board.h"
#include "../coordinate.h"
#include "../piece.h"
#include "window.h"
#include "chessrender.h"

#include <vector>

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
    ChessDotComBlackHighlight,
    ChessDotComWhiteHighlight,
    ChessDotComBg,
    CherryWhite,
    CherryBlack,
    CherryBlackHighlight,
    CherryWhiteHighlight,
    CherryBg,
    RomaniaWhite,
    RomaniaBlack,
    RomaniaBlackHighlight,
    RomaniaWhiteHighlight,
    RomaniaBg,    
    WinterWhite,
    WinterBlack,
    WinterBlackHighlight,
    WinterWhiteHighlight,
    WinterBg,
    AutumnWhite,
    AutumnBlack,
    AutumnBlackHighlight,
    AutumnWhiteHighlight,
    AutumnBg,
};

struct BoardTheme {
    std::string name;
    Color blackSquareColor;
    Color whiteSquareColor;
    Color blackSquareHighlightColor;
    Color whiteSquareHighlightColor;
    Color bgColor;
    Color textColor;
};

struct TeamPieceSet {
    std::string pawn;
    std::string rook;
    std::string bishop;
    std::string knight;
    std::string queen;
    std::string king;
};

struct PieceSet {
    std::string name;
    TeamPieceSet white;
    TeamPieceSet black;
};

class RenderWindow : public ChessRender {
    Xwindow window{WINDOW_W, WINDOW_W};

    std::vector<BoardTheme> boardThemes;
    std::vector<PieceSet> pieceSets;

    unsigned int currentBoardTheme = 0;
    unsigned int currentPieceSet = 0;

    void addTheme(const BoardTheme& theme);
    void setTheme(const std::string& name);

    void addPieceSet(const std::string& folder_path);
    void setPieceSet(const std::string& folder_path);

    std::string getPieceImage(Piece piece) const;

    public:
        RenderWindow(Board* board);
        void render() override;
        void cycleTheme();
        void cyclePieceSet();
        void setRandomTheme();
        void setRandomPieceSet();
};

#endif
