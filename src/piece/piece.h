#ifndef PIECE_H_
#define PIECE_H_
#include <vector>
#include "../player/player.h"
#include "../coordinate.h"

class Piece {

    public:
        const int value;
        const Player* player;
    
        Piece(int value, Player* player);
        virtual std::vector<Coordinate> getValidMoves(Coordinate p, std::vector<Coordinate> occupied) const noexcept = 0;
        virtual ~Piece() = 0;
};

#endif
