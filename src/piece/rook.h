#ifndef ROOK_H_
#define ROOK_H_
#include "piece.h"

class Rook : public Piece {
    char teamToChar(Team team) const noexcept;

    public:
        Rook(Team team);
        std::vector<Coordinate> getValidMoves(Coordinate p, std::vector<Coordinate> occupied) const noexcept override;

        virtual ~Rook();
};

#endif
