#ifndef KNIGHT_H_
#define KNIGHT_H_
#include "piece.h"

class Knight : public Piece {
    char teamToChar(Team team) const noexcept;
    
    public:
        Knight(Team team);
        std::vector<Coordinate> getValidMoves(Coordinate p, std::vector<Coordinate> occupied) const noexcept override;

        virtual ~Knight();
};

#endif
