#ifndef AI_PLAYER_H_
#define AI_PLAYER_H_
#include "../player.h"
#include "../../board.h"

// abstract aiplayer class which
// includes reference to a board
class AIPlayer : public Player {
protected:
    Board* board;
public:
    AIPlayer(Board* board): board{board} {
        isHuman = false;
    };
};

#endif
