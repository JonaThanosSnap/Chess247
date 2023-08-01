#include "chessapp.h"

/////////////////////////////////////
//                                 //
//     ChessApp  Implementation    //
//                                 //
/////////////////////////////////////

// constructor
ChessApp::ChessApp(): chess{}, render{chess.getBoard(), std::cout}, renderWindow{chess.getBoard()}, inputManager{&chess, &render, &renderWindow} {};

// main game loop
void ChessApp::playGame(){
    for(;;) { 
        // ask input manager to take input
        int end = inputManager.handleInput();

        // if the game is over, break out of the loop and print final scores
        if(end == 1) {
            chess.finalScores();
            break;
        }
        // if the game is started or is in setup mode, render the board
        if (chess.getIsGameStarted() || chess.getIsSetupMode()) {
            render.render();
            renderWindow.render();
        }
    }
}

