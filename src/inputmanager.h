#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "render/chessrender.h"

class Chess;

// translates inputs into commands for chess game
class InputManager {
private:
    Chess* game;
    ChessRender* render;
    ChessRender* backupRenderer;
    bool justSetup = false;
    void enterSetupMode();
public:
    InputManager(Chess*, ChessRender*, ChessRender*);
    int handleInput();
};

#endif
