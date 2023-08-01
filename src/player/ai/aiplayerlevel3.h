#ifndef AI_PLAYER_LEVEL3_H_
#define AI_PLAYER_LEVEL3_H_
#include "aiplayer.h"

/////////////////////////////////////
//                                 //
//    AI Player Level 3 Header     //
//                                 //
/////////////////////////////////////

class AIPlayerLevel3 : public AIPlayer {
public:
    // constructor
    AIPlayerLevel3(Board*, Team);
    // getMove returns a pair of coordinates representing the move
    std::pair<Coordinate, Coordinate> getMove() override;
};

#endif
