#ifndef QUEEN_H_
#define QUEEN_H_
#include "piece.h"

class Queen : public Piece {
    char teamToChar(Team team) const noexcept;

    public:
        Queen(Team team);
        std::vector<Coordinate> getValidMoves(Coordinate p, std::vector<Coordinate> occupied) const noexcept override;

        virtual ~Queen();
};

#endif
