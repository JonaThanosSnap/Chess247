#ifndef AI_PLAYER_LEVEL2_H_
#define AI_PLAYER_LEVEL2_H_
#include "aiplayer.h"

/////////////////////////////////////
//                                 //
//    AI Player Level 2 Header     //
//                                 //
/////////////////////////////////////

class AIPlayerLevel2 : public AIPlayer {
public:
    AIPlayerLevel2(Board*, Team);
    std::pair<Coordinate, Coordinate> getMove() override;
};

#endif
