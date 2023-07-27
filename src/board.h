#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <memory>
#include <stdexcept>
#include "piece.h"
#include "team.h"
#include "coordinate.h"

const int BOARD_WIDTH = 8;

class Board {
    Piece grid[BOARD_WIDTH][BOARD_WIDTH];

    bool coordsInRange(Coordinate p) const noexcept;

    std::vector<Coordinate> getValidMoves(Coordinate p) const;
    std::vector<Coordinate> getValidMovesPawn(Coordinate p) const;
    std::vector<Coordinate> getValidMovesRook(Coordinate p) const;
    std::vector<Coordinate> getValidMovesKnight(Coordinate p) const;
    std::vector<Coordinate> getValidMovesBishop(Coordinate p) const;
    std::vector<Coordinate> getValidMovesQueen(Coordinate p) const;
    std::vector<Coordinate> getValidMovesKing(Coordinate p) const;

    public:
        Board();
        void setSquare(Coordinate p, Piece piece);
        void clearSquare(Coordinate p);
        Piece getSquare(Coordinate p) const noexcept;
        bool isValidMove(Coordinate s, Coordinate d) const;
};

#endif
