#include "renderwindow.h"

RenderWindow::RenderWindow(Board* board): ChessRender{board} {
    // Set up colors
    window.addColor(Color::Black, "00", "00", "00");
    window.addColor(Color::White, "ff", "ff", "ff");
    window.addColor(Color::ChessDotComBlack, "76", "96", "56");
    window.addColor(Color::ChessDotComWhite, "ee", "ee", "d2");
    window.addColor(Color::ChessDotComBg, "36", "46", "52");

    // Set up images
    addPieceSet("assets/chess_dot_com");
    addPieceSet("assets/irl");
    setPieceSet("assets/irl");
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
}

void RenderWindow::setPieceSet(const std::string& folder_path) {
    // White pieces
    currentPieceSetWhite.pawn = folder_path + "/WPawn.png";
    currentPieceSetWhite.rook = folder_path + "/WRook.png";
    currentPieceSetWhite.bishop = folder_path + "/WBishop.png";
    currentPieceSetWhite.knight = folder_path + "/WKnight.png";
    currentPieceSetWhite.queen = folder_path + "/WQueen.png";
    currentPieceSetWhite.king = folder_path + "/WKing.png";

    // Black pieces
    currentPieceSetBlack.pawn = folder_path + "/BPawn.png";
    currentPieceSetBlack.rook = folder_path + "/BRook.png";
    currentPieceSetBlack.bishop = folder_path + "/BBishop.png";
    currentPieceSetBlack.knight = folder_path + "/BKnight.png";
    currentPieceSetBlack.queen = folder_path + "/BQueen.png";
    currentPieceSetBlack.king = folder_path + "/BKing.png";
}

std::string RenderWindow::getPieceImage(Piece piece) const {
    Team pieceTeam = piece.getTeam();
    Piece::Type pieceType = piece.getType();
    PieceSet pieceSet = (pieceTeam == Team::White) ? currentPieceSetWhite : currentPieceSetBlack;

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

void RenderWindow::render() {
    // Draw bg
    window.fillRectangle(0, 0, WINDOW_W, WINDOW_W, currentTheme.bgColor);

    // Draw board
    for (int i = 0; i < 8; i++) {
        // Draw rank
        std::string rank = std::to_string(8 - i);
        window.drawString(BOARD_MARGIN/2, BOARD_TOP_LEFT.y() + SQUARE_W/2 + SQUARE_W*i, rank, currentTheme.textColor);

        for (int j = 0; j < 8; j++) {
            Coordinate c{j, i};
            Coordinate renderc{j, 7-i};
            Piece piece = board->getSquare(c);
            
            unsigned long squareColor = isWhite(c) ? currentTheme.whiteSquareColor : currentTheme.blackSquareColor;
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
        window.drawString(BOARD_MARGIN + SQUARE_W/2 + SQUARE_W*j, BOARD_TOP_LEFT.y() + BOARD_W + BOARD_MARGIN/2, file, currentTheme.textColor);
    }
}
