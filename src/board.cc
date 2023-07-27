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
   //Allocate new Piece and place it into a grid square
   if (!coordsInRange(p)) throw std::out_of_range("Board::setSquare: coords out of range");
   grid[p.y()][p.x()] = piece;
}

bool Board::coordsInRange(Coordinate p) const noexcept {
    return (
        p.x() >= 0 && p.x() < 8 &&
        p.y() >= 0 && p.y() < 8
    );
}

void Board::clearSquare(Coordinate p) {
    if (!coordsInRange(p)) throw std::out_of_range("Board::clearSquare: coords out of range");
    grid[p.y()][p.x()] = Piece::Empty();
}

Piece Board::getSquare(Coordinate p) const noexcept {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getSquare: coords out of range");
    return grid[p.y()][p.x()];
}

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
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMove: position out of range");
}

std::vector<Coordinate> Board::getValidMovesPawn(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMovePawn: position out of range");
}

std::vector<Coordinate> Board::getValidMovesRook(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMoveRook: position out of range");

    Team team = getSquare(p).getTeam();

    std::vector<Coordinate> validMoves;
    std::vector<Coordinate> deltas = {Coordinate{0, -1}, Coordinate{0, 1}, Coordinate{-1, 0}, Coordinate{1, 0}};
    for (Coordinate delta : deltas) {
        Coordinate candidate = p + delta;
        while (coordsInRange(candidate)) {
            Piece otherPiece = getSquare(candidate);
            if (otherPiece != Piece::Empty()) {
                if (otherPiece.getTeam() != team) {
                    validMoves.push_back(candidate);
                }
                break;
            }
            // TODO CONSIDER CHECK PLEASE

            validMoves.push_back(candidate);
            candidate = candidate + delta;
        }
    }
}

std::vector<Coordinate> Board::getValidMovesKnight(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMoveKnight: position out of range");
}

std::vector<Coordinate> Board::getValidMovesBishop(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMoveBishop: position out of range");
}

std::vector<Coordinate> Board::getValidMovesQueen(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMoveQueen: position out of range");
}

std::vector<Coordinate> Board::getValidMovesKing(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMoveKing: position out of range");
}
