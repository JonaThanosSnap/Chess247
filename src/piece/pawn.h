#ifndef PAWN_H_
#define PAWN_H_
#include "piece.h"

class Pawn : public Piece {
    char teamToChar(Team team) const noexcept;
    
    public:
        Pawn(Team team);
        std::vector<Coordinate> getValidMoves(Coordinate p, std::vector<Coordinate> occupied) const noexcept override;

        virtual ~Pawn();
};

#endif
