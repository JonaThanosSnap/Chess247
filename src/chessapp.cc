#include "chessapp.h"

ChessApp::ChessApp(): chess{}, render{chess.getBoard(), std::cout}, renderWindow{chess.getBoard()}, inputManager{&chess, &render, &renderWindow} {};
//ChessApp::ChessApp(): chess{}, render{chess.getBoard(), std::cout}, inputManager{&chess, &render} {};
void ChessApp::playGame(){
    for(;;) { 
        // ask input manager to take input
        // render
        int end;
        while (true) {
            try {
                end = inputManager.handleInput();
                break;
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                std::cout << "HTTP ERROR 500: INTERNAL SERVER ERROR. TRY AGAIN" << std::endl;
                exit(1);
            }
        }

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

