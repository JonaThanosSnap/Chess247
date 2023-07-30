#include "setupmode.h"

SetupMode::SetupMode(Chess* chess): game{chess} {};

void SetupMode::enterSetupMode(){

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