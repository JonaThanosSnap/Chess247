#include "board.h"

#include <algorithm>

Board::Board() {
    // Create pawns
    for (int i = 0; i < BOARD_WIDTH; i++) {
        grid[1][i] = Piece::Pawn(Team::White);
        grid[6][i] = Piece::Pawn(Team::Black);
    }

    // White back-rank pieces
    grid[0][0] = Piece::Rook(Team::White);
    grid[0][1] = Piece::Bishop(Team::White);
    grid[0][2] = Piece::Knight(Team::White);
    grid[0][3] = Piece::Queen(Team::White);
    grid[0][4] = Piece::King(Team::White);
    grid[0][5] = Piece::Knight(Team::White);
    grid[0][6] = Piece::Bishop(Team::White);
    grid[0][7] = Piece::Rook(Team::White);

    // Black back-rank pieces
    grid[7][0] = Piece::Rook(Team::Black);
    grid[7][1] = Piece::Bishop(Team::Black);
    grid[7][2] = Piece::Knight(Team::Black);
    grid[7][3] = Piece::Queen(Team::Black);
    grid[7][4] = Piece::King(Team::Black);
    grid[7][5] = Piece::Knight(Team::Black);
    grid[7][6] = Piece::Bishop(Team::Black);
    grid[7][7] = Piece::Rook(Team::Black);
}

void Board::setSquare(Coordinate p, Piece piece) {
   // Construct new Piece and place it into a grid square
   if (!coordsInRange(p)) throw std::out_of_range("Board::setSquare: coords out of range");
   grid[p.y()][p.x()] = piece;
}

// checks whether or not a specific coordinate is in range
bool Board::coordsInRange(Coordinate p) const noexcept {
    return (
        p.x() >= 0 && p.x() < BOARD_WIDTH &&
        p.y() >= 0 && p.y() < BOARD_WIDTH
    );
}

// removes a piece at coordinate p
void Board::clearSquare(Coordinate p) {
    if (!coordsInRange(p)) throw std::out_of_range("Board::clearSquare: coords out of range");
    grid[p.y()][p.x()] = Piece::Empty();
}

// retrieves the piece at coordiante p
Piece Board::getSquare(Coordinate p) const noexcept {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getSquare: coords out of range");
    return grid[p.y()][p.x()];
}

// determines whether or not a move is valid
bool Board::isValidMove(Coordinate s, Coordinate d) const {
    if (!coordsInRange(s)) throw std::out_of_range("Board::isValidMove: start position out of range");
    if (!coordsInRange(d)) throw std::out_of_range("Board::isValidMove: end position out of range");
    if (getSquare(s) == Piece::Empty()) return false;

    std::vector<Coordinate> validMoves = getValidMoves(s);
    if (std::find(validMoves.begin(), validMoves.end(), d) != validMoves.end()) {
        return true;
    } else {
        return false;
    }
}

std::vector<Coordinate> Board::getValidMoves(Coordinate p) const {
    // isValidMove => if the move is in getValidMoves()
    //                then check if we end the turn with king in check
    // getValidMoves => first finds all 'possible' moves without considering check.         


    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMoves: position out of range");

    Piece piece = getSquare(p);
    Piece::Type pieceType = piece.getType();
    Team pieceTeam = piece.getTeam();

    // return a vector of squares where the piece can move
    //  according to its rules. it does NOT take checks into account.
    std::vector<Coordinate> validMoves;
    switch (pieceType) {
        case (Piece::Type::None):
            return validMoves;
        case (Piece::Type::Pawn):
            validMoves = getValidMovesPawn(p);
            break;
        case (Piece::Type::Rook):
            validMoves = getValidMovesRook(p);
            break;
        case (Piece::Type::Knight):
            validMoves = getValidMovesKnight(p);
            break;
        case (Piece::Type::Bishop):
            validMoves = getValidMovesBishop(p);
            break;
        case (Piece::Type::Queen):
            validMoves = getValidMovesQueen(p);
            break;
        case (Piece::Type::King):
            validMoves = getValidMovesKing(p);
            break;
    }

    return validMoves;
}

std::vector<Coordinate> Board::getValidMovesPawn(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMovesPawn: position out of range");
}

std::vector<Coordinate> Board::getValidMovesRook(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMovesRook: position out of range");

    Team team = getSquare(p).getTeam();

    std::vector<Coordinate> validMoves;

    // a delta is a direction that a piece can slide
    std::vector<Coordinate> deltas = {Coordinate{0, -1}, Coordinate{0, 1}, Coordinate{-1, 0}, Coordinate{1, 0}};
    for (Coordinate delta : deltas) {
        Coordinate candidate = p + delta;
        while (coordsInRange(candidate)) {
            Piece otherPiece = getSquare(candidate);
            if (otherPiece != Piece::Empty()) {
                // stop iteration when another piece is encountered
                if (otherPiece.getTeam() != team) {
                    // other piece is on other team
                    validMoves.push_back(candidate);
                }
                break;
            }

            validMoves.push_back(candidate);
            candidate = candidate + delta;
        }
    }
    return validMoves;
}

std::vector<Coordinate> Board::getValidMovesKnight(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMovesKnight: position out of range");

    Team team = getSquare(p).getTeam();

    std::vector<Coordinate> validMoves;

    std::vector<Coordinate> deltas = {Coordinate{1, -2}, Coordinate{2, -1}, Coordinate{2, 1}, Coordinate{1, 2}, Coordinate{-1, 2}, Coordinate{-2, 1}, Coordinate{-2, -1}, Coordinate{-1, -2}};

    for(Coordinate delta : deltas){
        Coordinate candidate = p + delta;
        if(coordsInRange(candidate)){
            Piece otherPiece = getSquare(candidate);
            // if destination is an ally, we cannot move there
            if (otherPiece != Piece::Empty() && otherPiece.getTeam() == team) {
                continue;
            }
            // destination is either empty or an enemy; we can move there
            else{
                validMoves.push_back(candidate);
            }
        }
    }
    return validMoves;
}

std::vector<Coordinate> Board::getValidMovesBishop(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMovesBishop: position out of range");
}

std::vector<Coordinate> Board::getValidMovesQueen(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMovesQueen: position out of range");
    // a combination of rook and bishop behaviour

}

std::vector<Coordinate> Board::getValidMovesKing(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMovesKing: position out of range");
    // do similar thing to othe valid moves functions with deltas and such
    // check whether or not moving to that position puts the king into check
    // handle castling by checking the following items
    //      whether the king has moved
    //      whether the path to the king/queen side rook is clear
    //      whether the king/queen side rook has moved before

}

Team Board::getEnemyTeam(Team team) const noexcept {
    return team == Team::White ? Team::Black : Team::White;
}

Coordinate Board::getKingCoords(Team team) const noexcept {
    for(int y = 0; y < BOARD_WIDTH; y++){
        for(int x = 0; x < BOARD_WIDTH; x++){
            if(grid[y][x].getTeam() == team && grid[y][x].getType() == Piece::Type::King){
                return Coordinate(x,y);
            }
        }
    }
}

std::vector<Coordinate> Board::getPieceCoords(Team team) const noexcept {
    std::vector<Coordinate> pieceCoords;
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_WIDTH; y++) {
            Coordinate coords = Coordinate{x, y};
            Piece piece = getSquare(coords);
            if (piece.getTeam() == team) {
                pieceCoords.push_back(coords);
            }
        }
    }
    return pieceCoords;
}

bool Board::isSquareThreatened(Team threatenedTeam, Coordinate p) const noexcept {
    std::vector<Coordinate> enemyMoves;
    std::vector<Coordinate> enemyPieceCoords = getPieceCoords(getEnemyTeam(threatenedTeam));
    for (Coordinate coords : enemyPieceCoords) {
        std::vector<Coordinate> enemyPieceValidMoves = getValidMoves(coords);
        if (std::find(enemyPieceValidMoves.begin(), enemyPieceValidMoves.end(), p) != enemyPieceValidMoves.end()) {
            return true;
        }
    }
    return false;
}

bool Board::isInCheck(Team threatenedTeam) const noexcept {
    Coordinate kingCoords = getKingCoords(threatenedTeam);
    return isSquareThreatened(threatenedTeam, kingCoords);
}
