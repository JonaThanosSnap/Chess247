#ifndef AI_PLAYER_LEVEL3_H_
#define AI_PLAYER_LEVEL3_H_
#include "aiplayer.h"

class AIPlayerLevel3 : public AIPlayer {
public:
    AIPlayerLevel3(Board*, Team);
    std::pair<Coordinate, Coordinate> getMove() override;
};

#endif
