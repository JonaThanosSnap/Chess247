#ifndef CHESS_H_
#define CHESS_H_

#include <map>
#include <memory>

#include "player/player.h"
#include "board.h"
#include "team.h"

class Chess {
    bool isSetupMode = false;
    bool isGameStarted = false;

    Board board;
    Team currentTeam;

    std::map<Team, std::unique_ptr<Player>> players;

    public:
        void startGame() noexcept;
        void makeMove(Coordinate s, Coordinate d);
        void setupEnter() noexcept;
        void setupExit() noexcept;
        void setupPlacePiece(Coordinate p, Piece piece);
        void setupRemovePiece(Coordinate p);
        void setupSetCurrentTeam(Team team) noexcept;
        Player* getPlayer(Team team) noexcept;
        Board* getBoard() noexcept;
};

#endif
