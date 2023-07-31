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
        std::cin >> start >> dest;
        try {
            // if coordinates are malformed, we need to catch this
            Coordinate s{start};
            Coordinate e{dest};

            game->makeMove(s, e);

            if(game->winner() != "") {
                std::cout << "Checkmate! " << game->winner() << " wins!" << std::endl;
                game->endGame();
                return;
            }

        } catch (...) {
            std::cout << "Your move could not be made. Try again." << std::endl;
        }

        // TODO: Coordinate constructor needs to fail

    } else if (cmd == "setup") {
        if(!game->getIsGameStarted()){
            enterSetupMode();
        }
        else{
            std::cout << "Cannot enter setup mode while game is in progress." << std::endl;
        }

    } else {
        std::cout << "Invalid command: " << cmd << std::endl;
    }
}

void InputManager::enterSetupMode(){

    game->setupEnter();

    std::string cmd;

    while(std::cin >> cmd) {
        if (cmd == "+") {
            char p;
            std::string coord;

            std::cin >> p >> coord;

            Team team = p >= 'a' ? Team::Black : Team::White;

            Coordinate location = Coordinate{coord};

            Piece newPiece;

            if(p == 'k' || p == 'K'){
                newPiece = Piece::King(team);
            }
            else if(p == 'b' || p == 'B'){
                newPiece = Piece::Bishop(team);
            }
            else if(p == 'p' || p == 'P'){
                newPiece = Piece::Pawn(team);
            }
            else if(p == 'r' || p == 'R'){
                newPiece = Piece::Rook(team);
            }
            else if(p == 'n' || p == 'N'){
                newPiece = Piece::Knight(team);
            }
            else if(p == 'q' || p == 'Q'){
                newPiece = Piece::Queen(team);
            }
            else{
                std::cout << "Invalid piece type" << std::endl;
                continue;
            }
            game->setupPlacePiece(location, newPiece);

            //TODO: Rerender the board
        }
        else if(cmd == "-"){
            std::string coord;

            std::cin >> coord;

            Coordinate location = Coordinate{coord};

            game->setupRemovePiece(location);

            //TODO: rerender the baord
        }

        else if(cmd == "="){
            std::string colour;

            std::cin >> colour;

            if(colour == "white"){
                game->setupSetCurrentTeam(Team::White);
            }
            else if(colour == "black"){
                game->setupSetCurrentTeam(Team::Black);
            }
            else{
                std::cout << "Invalid colour" << std::endl;
                continue;
            }
        }

        else if(cmd == "done"){
            Board* board = game->getBoard();

            if(board->isInCheck(Team::White) || board->isInCheck(Team::Black)) {
                std::cout << "Cannot exit setup mode: a king is in check" << std::endl;
                continue;
            }

            if(board->pawnOnLastRow()) {
                std::cout << "Cannot exit setup mode: a pawn is on the last row" << std::endl;
                continue;
            }

            if(!board->correctNumberOfKings()){
                std::cout << "Cannot exit setup mode: each player must have one king" << std::endl;
                continue;
            }

            game->setupExit();
            break;
        }

        else{
            std::cout << "Invalid command" << std::endl;
        }
    }
};




