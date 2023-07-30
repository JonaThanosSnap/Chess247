#ifndef AI_PLAYER_LEVEL1_H_
#define AI_PLAYER_LEVEL1_H_
#include "aiplayer.h"
#include "../../coordinate.h"
#include <utility>

class AIPlayerLevel1 : public AIPlayer {
public:
    AIPlayerLevel1(Board&);
    // std::pair<Coordinate, Coordinate> getMove() override;
};

#endif
