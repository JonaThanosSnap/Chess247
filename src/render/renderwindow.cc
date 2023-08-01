#include "renderwindow.h"

#include <algorithm>

RenderWindow::RenderWindow(Board* board): ChessRender{board} {
    // Set up colors
    window.addColor(Color::Black, "00", "00", "00");
    window.addColor(Color::White, "ff", "ff", "ff");
    window.addColor(Color::ChessDotComBlack, "76", "96", "56");
    window.addColor(Color::ChessDotComWhite, "ee", "ee", "d2");
    window.addColor(Color::ChessDotComBlackHighlight, "f0", "80", "3c");
    window.addColor(Color::ChessDotComWhiteHighlight, "ff", "93", "4f");
    window.addColor(Color::ChessDotComBg, "36", "46", "52");

    addTheme(BoardTheme{
        "chess_dot_com",
        Color::ChessDotComBlack,
        Color::ChessDotComWhite,
        Color::ChessDotComBlackHighlight,
        Color::ChessDotComWhiteHighlight,
        Color::ChessDotComBg,
        Color::ChessDotComWhite
    });
    setTheme("chess_dot_com");

    // Set up images
    addPieceSet("assets/chess_dot_com");
    addPieceSet("assets/irl");
    setPieceSet("assets/chess_dot_com");
}

void RenderWindow::addTheme(const BoardTheme& theme) {
    boardThemes.push_back(theme);
}

void RenderWindow::setTheme(const std::string& name) {
    for (int i = 0; i < boardThemes.size(); i++) {
        if (boardThemes[i].name == name) currentBoardTheme = i;
    }
}

void RenderWindow::addPieceSet(const std::string& folder_path) {
    const std::string teams[] = {
        "B", "W"
    };

    const std::string pieceNames[] = {
        "Bishop",
        "King",
        "Knight",
        "Pawn",
        "Queen",
        "Rook"
    };

    const std::string fileSuffix = ".png";

    for (std::string team : teams) {
        for (std::string pieceName : pieceNames) {
            std::string filePath = folder_path + "/" + team + pieceName + fileSuffix;
            window.addImage(filePath);
        }
    }

    PieceSet newPieceSet;

    newPieceSet.name = folder_path;

    // White pieces
    newPieceSet.white.pawn = folder_path + "/WPawn.png";
    newPieceSet.white.rook = folder_path + "/WRook.png";
    newPieceSet.white.bishop = folder_path + "/WBishop.png";
    newPieceSet.white.knight = folder_path + "/WKnight.png";
    newPieceSet.white.queen = folder_path + "/WQueen.png";
    newPieceSet.white.king = folder_path + "/WKing.png";

    // Black pieces
    newPieceSet.black.pawn = folder_path + "/BPawn.png";
    newPieceSet.black.rook = folder_path + "/BRook.png";
    newPieceSet.black.bishop = folder_path + "/BBishop.png";
    newPieceSet.black.knight = folder_path + "/BKnight.png";
    newPieceSet.black.queen = folder_path + "/BQueen.png";
    newPieceSet.black.king = folder_path + "/BKing.png";

    pieceSets.push_back(newPieceSet);
}

void RenderWindow::setPieceSet(const std::string& folder_path) {
    for (int i = 0; i < pieceSets.size(); i++) {
        if (pieceSets[i].name == folder_path) currentBoardTheme = i;
    }
}

std::string RenderWindow::getPieceImage(Piece piece) const {
    Team pieceTeam = piece.getTeam();
    Piece::Type pieceType = piece.getType();
    TeamPieceSet pieceSet = (pieceTeam == Team::White) ? pieceSets[currentPieceSet].white : pieceSets[currentPieceSet].black;

    std::string pieceImagePath;
    switch (pieceType) {
        case Piece::Type::Pawn:
            pieceImagePath = pieceSet.pawn;
            break;
        case Piece::Type::Rook:
            pieceImagePath = pieceSet.rook;
            break;
        case Piece::Type::Bishop:
            pieceImagePath = pieceSet.bishop;
            break;
        case Piece::Type::Knight:
            pieceImagePath = pieceSet.knight;
            break;
        case Piece::Type::Queen:
            pieceImagePath = pieceSet.queen;
            break;
        case Piece::Type::King:
            pieceImagePath = pieceSet.king;
            break;
        default:
            pieceImagePath = "";
            break;
    }

    return pieceImagePath;
}

void RenderWindow::cycleTheme() {
    currentBoardTheme = (currentBoardTheme + 1) % boardThemes.size();
}

void RenderWindow::cyclePieceSet() {
    currentPieceSet = (currentPieceSet + 1) % pieceSets.size();
}

void RenderWindow::setRandomTheme() {
    currentBoardTheme = std::rand() % boardThemes.size();
}

void RenderWindow::setRandomPieceSet() {
    currentPieceSet = std::rand() % pieceSets.size();
}

void RenderWindow::render() {
    // Draw bg
    window.fillRectangle(0, 0, WINDOW_W, WINDOW_W, boardThemes[currentBoardTheme].bgColor);

    // Draw board
    for (int i = 0; i < 8; i++) {
        // Draw rank
        std::string rank = std::to_string(8 - i);
        window.drawString(BOARD_MARGIN/2, BOARD_TOP_LEFT.y() + SQUARE_W/2 + SQUARE_W*i, rank, boardThemes[currentBoardTheme].textColor);

        for (int j = 0; j < 8; j++) {
            Coordinate c{j, i};
            Coordinate renderc{j, 7-i};
            Piece piece = board->getSquare(c);
            
            unsigned long squareColor;
            Coordinate lastMoveStart{EMPTY_COORDS}, lastMoveEnd{EMPTY_COORDS};
            std::tie(lastMoveStart, lastMoveEnd) = board->getLastMove();
            if (c == lastMoveStart || c == lastMoveEnd) {
                squareColor = isWhite(c) ? boardThemes[currentBoardTheme].whiteSquareHighlightColor : boardThemes[currentBoardTheme].blackSquareHighlightColor;
            } else {
                squareColor = isWhite(c) ? boardThemes[currentBoardTheme].whiteSquareColor : boardThemes[currentBoardTheme].blackSquareColor;
            }

            Coordinate squareTopLeft = BOARD_TOP_LEFT + renderc*SQUARE_W;
            window.fillRectangle(squareTopLeft.x(), squareTopLeft.y(), SQUARE_W, SQUARE_W, squareColor);

            if (piece != Piece::Empty()) {
                // Draw piece
                window.putImage(getPieceImage(piece), squareTopLeft.x() + SQUARE_W/2, squareTopLeft.y() + SQUARE_W/2, PIECE_W, PIECE_W);
            }
        }
    }
    
    // Draw file
    for (int j = 0; j < 8; j++) {
        std::string file{(char)('a' + j)};
        window.drawString(BOARD_MARGIN + SQUARE_W/2 + SQUARE_W*j, BOARD_TOP_LEFT.y() + BOARD_W + BOARD_MARGIN/2, file, boardThemes[currentBoardTheme].textColor);
    }
}
