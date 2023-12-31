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

//////////////////////////////////
//                              //
// Input Manager Implementation //
//                              //
//////////////////////////////////

InputManager::InputManager(Chess* chess, ChessRender* chessRender, RenderWindow* windowRender): game{chess}, render{chessRender}, windowRender{windowRender} {};

int InputManager::handleInput() {
    // read in one command at a time and handle it
    std::string cmd;
    std::cin >> cmd;

    // start a new game
    if (cmd == "game") {

        // if we just finished setup, start the game but don't reset the board
        if (game->isJustSetup()) {
            game->finishedSetup();
        } else {
            game->boardReset();
        }
        
        std::string white, black;
        std::cin >> white >> black;

        // take in both inputs at once and ensure they are both wellformed
        if (white == "human") {
            game->setPlayer(Team::White, new HumanPlayer{});
        } else if (white == "computer1") {
            game->setPlayer(Team::White, new AIPlayerLevel1{game->getBoard(), Team::White});
        } else if (white == "computer2") {
            game->setPlayer(Team::White, new AIPlayerLevel2{game->getBoard(), Team::White});
        } else if (white == "computer3") {
            game->setPlayer(Team::White, new AIPlayerLevel3{game->getBoard(), Team::White});
        } else if (white == "computer4") {
            game->setPlayer(Team::White, new AIPlayerLevel4{game->getBoard(), Team::White});
        } else {
            std::cout << "This is not a valid option for white. Valid options: human, computer<1-4>." << std::endl;
            return 0;
        }

        if (black == "human") {
            game->setPlayer(Team::Black, new HumanPlayer{});
        } else if (black == "computer1") {
            game->setPlayer(Team::Black, new AIPlayerLevel1{game->getBoard(), Team::Black});
        } else if (black == "computer2") {
            game->setPlayer(Team::Black, new AIPlayerLevel2{game->getBoard(), Team::Black});
        } else if (black == "computer3") {
            game->setPlayer(Team::Black, new AIPlayerLevel3{game->getBoard(), Team::Black});
        } else if (black == "computer4") {
            game->setPlayer(Team::Black, new AIPlayerLevel4{game->getBoard(), Team::Black});
        } else {
            std::cout << "This is not a valid option for black. Valid options: human, computer<1-4>." << std::endl;
            return 0;
        }

        // start game if inputs are wellformed
        game->startGame();
    } else if (cmd == "changeboard") {
        windowRender->cycleTheme();
        windowRender->render();
    } else if (cmd == "changepieces") {
        windowRender->cyclePieceSet();
        windowRender->render();
    } else if (cmd == "random") {
        windowRender->setRandomTheme();
        windowRender->setRandomPieceSet();
        windowRender->render();
    } else if (cmd == "resign") {
        // make sure the game has started
        if (!game->getIsGameStarted()) {
            std::cout << "Cannot resign, game has not been started." << std::endl;
            return 0;
        }
        // resign the current player
        Team loser = game->resign();
        std::cout << (loser == Team::White ? "White" : "Black") << " wins!" << std::endl;
        
        return 0;

    } else if (cmd == "move") {
        // move pieces depending on the current player's turn.
        // if human player, they need to enter start/dest coords.
        // if ai player, the move command is enough
        
        // make sure the game has started
        if (!game->getIsGameStarted()) {
            std::cout << "Cannot move, game has not been started." << std::endl;
            return 0;
        }

        Player* currentPlayer = game->getCurrentPlayer();
        bool isHuman = currentPlayer->isHumanPlayer();

        if (isHuman) {
            std::string start, dest;

            std::cin >> start >> dest;

            char promotion;

            if (std::cin.peek() != '\n') {
                std::cin >> promotion;
            }

            try {
                // if coordinates are malformed, we need to catch this
                Coordinate s{start};
                Coordinate e{dest};

                game->makeMove(s, e, promotion);
            } catch (std::exception& e) {
                std::cout << "Your move could not be made. Try again." << std::endl;
            }
        } else {
            std::pair<Coordinate, Coordinate> move = currentPlayer->getMove();
            game->makeMove(move.first, move.second, 'q');
        }

        // if there is a winner
        std::string winner = game->winner();
        if(winner != "") {
            if (winner == "Stalemate") {
                std::cout << "Stalemate!" << std::endl;
            } else {
                std::cout << "Checkmate! " << game->winner() << " wins!" << std::endl;
            }
            // render the board one last time
            render->render();
            windowRender->render();
            game->endGame();
            return 0;
        }

        // if there is a check
        std::string teamInCheck = game->teamInCheck();
        if (teamInCheck != "") {
            std::cout << teamInCheck << " is in check." << std::endl;
        }

    // enter setup mode
    } else if (cmd == "setup") {
        // only enter setup mode if the game has not started
        if(!game->getIsGameStarted()){
            enterSetupMode();
        }
        else{
            std::cout << "Cannot enter setup mode while game is in progress." << std::endl;
        }
    } else {
        // if we reach the eof, i.e. ctrl D, then exit the program
        if (std::cin.eof()) {
            return 1;
        } 
        std::cout << "Invalid command: " << cmd << std::endl;
    }
    return 0;
}

// method for setup mode

void InputManager::enterSetupMode(){

    game->setupEnter();

    std::string cmd;

    while(std::cin >> cmd) {
        // insert a piece at some coordinate
        if (cmd == "+") {
            char p;
            std::string coord;

            std::cin >> p >> coord;

            // determine the team (lower case is black, upper case is white)
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
            newPiece.setHasMoved(true);

            try {
                game->setupPlacePiece(location, newPiece);
            } catch (...) {
                std::cout << "Could not add piece: coords out of range." << std::endl;
                continue;
            }

            // rerender the board
            render->render();
            windowRender->render();

        }
        // remove a piece at some coordinate
        else if(cmd == "-"){
            std::string coord;

            std::cin >> coord;

            Coordinate location = Coordinate{coord};

            try {
                game->setupRemovePiece(location);
            } catch (...) {
                std::cout << "Could not remove piece: coords out of range." << std::endl;
                continue;
            }

            render->render();
            windowRender->render();
        }

        // set the current team
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

        // exit setup mode
        else if(cmd == "done"){
            Board* board = game->getBoard();

            // cannot exit setup mode if a king is in check
            if(board->isInCheck(Team::White) || board->isInCheck(Team::Black)) {
                std::cout << "Cannot exit setup mode: a king is in check" << std::endl;
                continue;
            }

            // cannot exit setup mode if a pawn is on the last row
            if(board->pawnOnLastRow()) {
                std::cout << "Cannot exit setup mode: a pawn is on the last row" << std::endl;
                continue;
            }

            // cannot exit setup mode if there are not enough kings
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
