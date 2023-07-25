#include "board.h"
#include "piece/bishop.h"
#include "piece/king.h"
#include "piece/knight.h"
#include "piece/pawn.h"
#include "piece/queen.h"
#include "piece/rook.h"

#include <algorithm>

Board::Board() {
    // Pawns for both sides
    for (int j = 0; j < 8; ++j) {
        grid[1][j] = std::make_unique<Pawn>(Team::White); // White pawns
        grid[6][j] = std::make_unique<Pawn>(Team::Black); // Black pawns
    }

    // White pieces
    grid[0][0] = std::make_unique<Rook>(Team::White);
    grid[0][1] = std::make_unique<Knight>(Team::White);
    grid[0][2] = std::make_unique<Bishop>(Team::White);
    grid[0][3] = std::make_unique<Queen>(Team::White);
    grid[0][4] = std::make_unique<King>(Team::White);
    grid[0][5] = std::make_unique<Bishop>(Team::White);
    grid[0][6] = std::make_unique<Knight>(Team::White);
    grid[0][7] = std::make_unique<Rook>(Team::White);

    // Black pieces
    grid[7][0] = std::make_unique<Rook>(Team::Black);
    grid[7][1] = std::make_unique<Knight>(Team::Black);
    grid[7][2] = std::make_unique<Bishop>(Team::Black);
    grid[7][3] = std::make_unique<Queen>(Team::Black);
    grid[7][4] = std::make_unique<King>(Team::Black);
    grid[7][5] = std::make_unique<Bishop>(Team::Black);
    grid[7][6] = std::make_unique<Knight>(Team::Black);
    grid[7][7] = std::make_unique<Rook>(Team::Black);
}

bool Board::coordsInRange(Coordinate p) const noexcept {
    return (
        p.x() >= 0 && p.x() < 8 &&
        p.y() >= 0 && p.y() < 8
    );
}

void Board::clearSquare(Coordinate p) {
    if (!coordsInRange(p)) throw std::out_of_range("Board::clearSquare: coords out of range");
    grid[p.y()][p.x()] = std::unique_ptr<Piece>{};
}

bool Board::isValidMove(Coordinate s, Coordinate d) const {
    if (!coordsInRange(s)) throw std::out_of_range("Board::isValidMove: start position out of range");
    if (!coordsInRange(d)) throw std::out_of_range("Board::isValidMove: end position out of range");

    Piece* piece = grid[s.y()][s.x()].get();
    std::vector<Coordinate> validMoves = piece->getValidMoves(s, getOccupiedSquares());

    // Check if destination coords are in validMoves
    if (std::find(validMoves.begin(), validMoves.end(), d) != validMoves.end()) {
        return true;
    } else {
        return false;
    }
}

std::vector<Coordinate> Board::getOccupiedSquares() const noexcept {
    std::vector<Coordinate> occupiedSquares;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            // i is y
            // j is x
            if (grid[i][j]) occupiedSquares.push_back(Coordinate(j, i));
        }
    }
    return occupiedSquares;
}
