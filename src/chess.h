#ifndef CHESS_H_
#define CHESS_H_

#include <map>
#include <memory>

#include "player/player.h"
#include "board.h"
#include "team.h"

/////////////////////////////////////
//                                 //
//           Chess Header          //
//                                 //
/////////////////////////////////////

class Chess {
    // private data members
    bool isSetupMode = false;
    bool isGameStarted = false;
    bool justSetup = false;

    Board board;
    Team currentTeam = Team::White;

    std::map<Team, std::unique_ptr<Player>> players;
    std::vector<int> scores = {0,0}; // white, black

    public:
        // start and end game
        void startGame() noexcept;
        void endGame() noexcept;

        // make a move
        void makeMove(Coordinate s, Coordinate d, char promotion);

        // setup mode commands
        void setupEnter() noexcept;
        void setupExit() noexcept;
        void setupPlacePiece(Coordinate p, Piece piece);
        void setupRemovePiece(Coordinate p);
        void setupSetCurrentTeam(Team team) noexcept;
        void setPlayer(Team team, Player*) noexcept;

        // get private data members
        Player* getPlayer(Team team) noexcept;
        Player* getCurrentPlayer() noexcept;
        Board* getBoard() noexcept;
        bool getIsGameStarted() const noexcept;
        bool getIsSetupMode() const noexcept;

        // retrieve information about game
        std::string winner();
        std::string teamInCheck();
        Team resign();
        void boardReset();
        void finalScores() const noexcept;
        bool isJustSetup() const noexcept;
        void finishedSetup() noexcept;
};

#endif
