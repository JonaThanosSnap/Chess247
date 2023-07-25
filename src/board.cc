#include "board.h"

Board::Board() {}

bool Board::coordsInRange(Coordinate p) {}

void Board::clearSquare(Coordinate p) {
    if (!coordsInRange(p)) throw std::out_of_range("Board::clearSquare: coords out of range");
    grid[p.y()][p.x()] = std::unique_ptr<Piece>{};
}

bool Board::isValidMove(Coordinate s, Coordinate d) {}