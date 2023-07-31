#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "render/chessrender.h"

class Chess;

// translates inputs into commands for chess game
class InputManager {
private:
    Chess* game;
    ChessRender* render;
    void enterSetupMode();
public:
    InputManager(Chess*, ChessRender*);
    void handleInput();
};

#endif
