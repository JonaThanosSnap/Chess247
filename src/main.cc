#include <iostream>
#include "render/renderostream.h"
#include "chess.h"
#include "exception.h"
#include "inputmanager.h"

int main() {
    Chess chess;
    RenderOStream render{chess.getBoard(), std::cout};
    InputManager inputManager{&chess};

    // chess.startGame();
    // render.render();

    // std::string sStr, dStr;
    // std::cout << "Please input move (eg. e2 e4): " << std::flush;
    // while (std::cin >> sStr >> dStr) {
    //     try {
    //         if (sStr.size() < 2 || dStr.size() < 2) throw InvalidMoveException{};
    //         if (
    //             'a' > sStr[0] || 'h' < sStr[0] || '1' > sStr[1] || '8' < sStr[1] ||
    //             'a' > dStr[0] || 'h' < dStr[0] || '1' > dStr[1] || '8' < dStr[1]
    //         ) throw InvalidMoveException{};
    //         chess.makeMove(Coordinate{sStr}, Coordinate{dStr});
    //     } catch (InvalidMoveException& e) {
    //         std::cout << "Invalid move!" << std::endl;
    //     }
    //     render.render();
    //     std::cout << "Please input move: " << std::flush;
    // }

    while(1) { 
        // ask input manager to take input
        // render()

        inputManager.handleInput();
        render.render();
    }

    return 0;
}