#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "render/chessrender.h"
#include "render/renderwindow.h"

class Chess;

// translates inputs into commands for chess game
class InputManager {
private:
    Chess* game;
    ChessRender* render;
    RenderWindow* windowRender;
    bool justSetup = false;
    void enterSetupMode();
public:
    InputManager(Chess*, ChessRender*, RenderWindow*);
    int handleInput();
};

#endif
