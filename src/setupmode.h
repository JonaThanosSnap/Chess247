#ifndef SETUP_MODE_H_
#define SETUP_MODE_H_

#include <map>
#include <memory>

#include "player/player.h"
#include "board.h"
#include "team.h"
#include "chess.h"

class SetupMode {
        Chess* game;
    public:
        SetupMode(Chess*);
        void enterSetupMode();
};

#endif
