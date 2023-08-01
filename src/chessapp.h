#ifndef CHESS_APP_H_
#define CHESS_APP_H_

#include <iostream>
#include "render/renderwindow.h"
#include "render/renderostream.h"
#include "chess.h"
#include "exception.h"
#include "inputmanager.h"

/////////////////////////////////////
//                                 //
//         ChessApp Header         //
//                                 //
/////////////////////////////////////

class ChessApp {

    // private data members
    Chess chess;
    RenderOStream render;
    RenderWindow renderWindow;
    InputManager inputManager;

    public:
        // constructor
        ChessApp();

        // main game loop
        void playGame();

};

#endif
