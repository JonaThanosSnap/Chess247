#ifndef AI_PLAYER_LEVEL1_H_
#define AI_PLAYER_LEVEL1_H_
#include "aiplayer.h"
#include "../../coordinate.h"
#include <utility>

/////////////////////////////////////
//                                 //
//    AI Player Level 1 Header     //
//                                 //
/////////////////////////////////////

class AIPlayerLevel1 : public AIPlayer {
public:
    // constructor
    AIPlayerLevel1(Board*, Team);

    // getMove returns a pair of coordinates representing the move
    std::pair<Coordinate, Coordinate> getMove() override;
};

#endif
