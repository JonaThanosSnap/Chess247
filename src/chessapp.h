#ifndef CHESS_APP_H_
#define CHESS_APP_H_

#include <iostream>
#include "render/renderwindow.h"
#include "render/renderostream.h"
#include "chess.h"
#include "exception.h"
#include "inputmanager.h"

class ChessApp {

    Chess chess;
    RenderOStream render;
    //RenderWindow renderWindow;
    InputManager inputManager;

    public:
        ChessApp();
        void playGame();

};

#endif