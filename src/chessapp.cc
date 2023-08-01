#include "chessapp.h"

ChessApp::ChessApp(): chess{}, render{chess.getBoard(), std::cout}, renderWindow{chess.getBoard()}, inputManager{&chess, &render, &renderWindow} {};
//ChessApp::ChessApp(): chess{}, render{chess.getBoard(), std::cout}, inputManager{&chess, &render} {};
void ChessApp::playGame(){
    for(;;) { 
        // ask input manager to take input
        // render
        int end = inputManager.handleInput();

        if(end == 1) {
            chess.finalScores();
            break;
        }
        if (chess.getIsGameStarted() || chess.getIsSetupMode()) {
            render.render();
            renderWindow.render();
        }
    }
}

