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
    // std::cout << "hi";
    // read in one command at a time and handle it
    std::string cmd;
    std::cin >> cmd;

    if (cmd == "game") {
        // start a new game
        std::string white, black;
        // std::cout << "Enter a player type for white: ";

        while (std::cin >> white) {
            // ensure player type input is wellformed
            if (white == "human") {
                game->setPlayer(Team::White, new HumanPlayer{});
                break;
            } else if (white == "computer1") {
                game->setPlayer(Team::White, new AIPlayerLevel1{game->getBoard()});
                break;
            // } else if (white == "computer2") {
            //     game->setPlayer(Team::White, new AIPlayerLevel2{game->getBoard()});
            //     break;
            // } else if (white == "computer3") {
            //     game->setPlayer(Team::White, new AIPlayerLevel3{game->getBoard()});
            //     break;
            // } else if (white == "computer4") {
            //     game->setPlayer(Team::White, new AIPlayerLevel4{game->getBoard()});
            //     break;
            } else {
                std::cout << "This is not a valid option for white. Valid options: human, computer<1-4>." << std::endl;
            }
        }

        // std::cout << "Enter a player type for black: ";
        while (std::cin >> black) {
            if (black == "human") {
                game->setPlayer(Team::Black, new HumanPlayer{});
                break;
            } else if (black == "computer1") {
                game->setPlayer(Team::Black, new AIPlayerLevel1{game->getBoard()});
                break;
            // } else if (black == "computer2") {
            //     game->setPlayer(Team::Black, new AIPlayerLevel2{game->getBoard()});
            //     break;
            // } else if (black == "computer3") {
            //     game->setPlayer(Team::Black, new AIPlayerLevel3{game->getBoard()});
            //     break;
            // } else if (black == "computer4") {
            //     game->setPlayer(Team::Black, new AIPlayerLevel4{game->getBoard()});
            //     break;
            } else {
                std::cout << "This is not a valid option for black. Valid options: human, computer<1-4>." << std::endl;
            }
        }
        game->startGame();

    } else if (cmd == "resign") {
        // concede game to opponent
        // game->resign???

    } else if (cmd == "move") {
        // move pieces depending on the current player's turn.
        // if human player, they need to enter start/dest coords.
        // if ai player, the move command is enough
        Player* currentPlayer = game->getCurrentPlayer();
        bool isHuman = currentPlayer->isHumanPlayer();

        if (isHuman) {
            std::string start, dest;

            while (std::cin >> start >> dest) {
                try {
                    // if coordinates are malformed, we need to catch this
                    Coordinate s{start};
                    Coordinate e{dest};

                    game->makeMove(s, e);
                    break;
                } catch (std::exception& e) {
                    std::cout << "Your move could not be made. Try again." << std::endl;
                    std::cout << e.what() << std::endl;
                }
            }
        } else {
            std::pair<Coordinate, Coordinate> move = currentPlayer->getMove();
            game->makeMove(move.first, move.second);
        }

        // TODO: Coordinate constructor needs to fail

    } else if (cmd == "setup") {
        // enter setup mode
        

    } else {
        std::cout << "Invalid command: " << cmd << std::endl;
    }
}
