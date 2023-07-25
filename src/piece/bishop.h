#ifndef BISHOP_H_
#define BISHOP_H_
#include "piece.h"

class Bishop : public Piece {
    char teamToChar(Team team) const noexcept;
    
    public:
        Bishop(Team team);
        std::vector<Coordinate> getValidMoves(Coordinate p, std::vector<Coordinate> occupied) const noexcept override;

        virtual ~Bishop();
};

#endif
