#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <memory>
#include <stdexcept>
#include "piece/piece.h"
#include "coordinate.h"

class Board {
    std::unique_ptr<Piece> grid[8][8];

    bool coordsInRange(Coordinate p) const noexcept;

    public:
        Board();
        template<typename P> void setSquare(Coordinate p, Player* player);
        void clearSquare(Coordinate p);
        bool isValidMove(Coordinate s, Coordinate d) const;
        std::vector<Coordinate> getOccupiedSquares() const noexcept;
        const Piece* getSquare(Coordinate p) const noexcept;
};

template <typename P> void Board::setSquare(Coordinate p, Player* player) {
    // Allocate new Piece and place it into a grid square
    if (!coordsInRange(p)) throw std::out_of_range("Board::setSquare: coords out of range");
    grid[p.y()][p.x()] = std::make_unique<P>(player);
}

#endif
