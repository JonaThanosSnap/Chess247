#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <memory>
#include <stdexcept>
#include "piece/piece.h"
#include "coordinate.h"

class Board {
    std::unique_ptr<Piece> grid[8][8];

    bool coordsInRange(Coordinate p);

    public:
        Board();

        template<typename P> void setSquare(Coordinate p);
        void clearSquare(Coordinate p);
        bool isValidMove(Coordinate s, Coordinate d);
};

template <typename P> void Board::setSquare(Coordinate p) {
    if (coordsInRange(p)) throw std::out_of_range();
}

#endif
