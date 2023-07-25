#include "board.h"

Board::Board() {}

bool Board::coordsInRange(Coordinate p) {}

void Board::clearSquare(Coordinate p) {
    grid[p.y()][p.x()] = std::unique_ptr<Piece>{};
}

bool Board::isValidMove(Coordinate s, Coordinate d) {}