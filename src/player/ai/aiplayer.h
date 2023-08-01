#ifndef AI_PLAYER_H_
#define AI_PLAYER_H_
#include "../player.h"
#include "../../board.h"

/////////////////////////////////////
//                                 //
//         AI Player Header        //
//                                 //
/////////////////////////////////////

// abstract aiplayer class which
// includes reference to a board
class AIPlayer : public Player {
protected:
    Board* board;
public:
    // constructor
    AIPlayer(Board* board);
};

#endif
