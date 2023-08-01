#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "render/chessrender.h"
#include "render/renderwindow.h"

//////////////////////////////////
//                              //
//     Input Manager Header     //
//                              //
//////////////////////////////////

// forward declaration of Chess class
class Chess;

// translates inputs into commands for chess game
class InputManager {
private:
    // private data members
    Chess* game;
    ChessRender* render;
    RenderWindow* windowRender;
    bool justSetup = false;
    void enterSetupMode();
public:
    // constructors
    InputManager(Chess*, ChessRender*, RenderWindow*);
    // handle input
    int handleInput();
};

#endif
