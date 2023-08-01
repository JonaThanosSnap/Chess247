#ifndef AI_PLAYER_LEVEL4_H_
#define AI_PLAYER_LEVEL4_H_
#include "aiplayer.h"

class AIPlayerLevel4 : public AIPlayer {
public:
    AIPlayerLevel4(Board*, Team);
    int getPieceValue(Piece::Type); 
    std::pair<Coordinate, Coordinate> getMove() override;
};

#endif
