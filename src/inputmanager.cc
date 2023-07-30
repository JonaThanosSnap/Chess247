#include "inputmanager.h"
#include "chess.h"
#include "player/human/humanplayer.h"
#include "player/ai/aiplayerlevel1.h"
#include "player/ai/aiplayerlevel2.h"
#include "player/ai/aiplayerlevel3.h"
#include "player/ai/aiplayerlevel4.h"
#include "coordinate.h"
#include <string>
#include <iostream>

InputManager::InputManager(Chess* chess): game{chess} {};

void InputManager::handleInput() {
    // read in one command at a time and handle it
    std::string cmd;
    std::cin >> cmd;

    if (cmd == "game") {
        // start a new game
        // std::string white, black;
        // std::cout << "Enter a player type for white: ";

        // while (std::cin >> white) {
        //     // ensure player type input is wellformed
        //     if (white == "human") {
        //         game->setPlayer1(new HumanPlayer{});
        //         break;
        //     } else if (white == "computer1") {
        //         game->setPlayer1(new AIPlayerLevel1{});
        //         break;
        //     } else if (white == "computer2") {
        //         game->setPlayer1(new AIPlayerLevel2{});
        //         break;
        //     } else if (white == "computer3") {
        //         game->setPlayer1(new AIPlayerLevel3{});
        //         break;
        //     } else if (white == "computer4") {
        //         game->setPlayer1(new AIPlayerLevel4{});
        //         break;
        //     } else {
        //         std::cout << "This is not a valid option for white. Valid options: human, computer<1-4>." << std::endl;
        //     }
        // }

        // std::cout << "Enter a player type for black: ";
        // while (std::cin >> black) {
        //     if (black == "human") {
        //         game->setPlayer2(new HumanPlayer{});
        //         break;
        //     } else if (black == "computer1") {
        //         game->setPlayer2(new AIPlayerLevel1{});
        //         break;
        //     } else if (black == "computer2") {
        //         game->setPlayer2(new AIPlayerLevel2{});
        //         break;
        //     } else if (black == "computer3") {
        //         game->setPlayer2(new AIPlayerLevel3{});
        //         break;
        //     } else if (black == "computer4") {
        //         game->setPlayer2(new AIPlayerLevel4{});
        //         break;
        //     } else {
        //         std::cout << "This is not a valid option for black. Valid options: human, computer<1-4>." << std::endl;
        //     }
        // }
        game->startGame();

    } else if (cmd == "resign") {
        // concede game to opponent
        // game->resign???

    } else if (cmd == "move") {
        // make a move
        std::string start, dest;

        while (std::cin >> start >> dest) {
            try {
                // if coordinates are malformed, we need to catch this
                Coordinate s{start};
                Coordinate e{dest};

                game->makeMove(s, e);
                break;
            } catch (...) {
                std::cout << "Your move could not be made. Try again." << std::endl;
            }
        }

        // TODO: Coordinate constructor needs to fail

    } else if (cmd == "setup") {
        // enter setup mode
        

    } else {
        std::cout << "Invalid command: " << cmd << std::endl;
    }
}
