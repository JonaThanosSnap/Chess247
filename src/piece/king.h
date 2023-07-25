#ifndef KING_H_
#define KING_H_
#include "piece.h"

class King : public Piece {
    char teamToChar(Team team) const noexcept;
    
    public:
        King(Team team);
        std::vector<Coordinate> getValidMoves(Coordinate p, std::vector<Coordinate> occupied) const noexcept override;

        virtual ~King();
};

#endif
