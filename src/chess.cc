#include "chess.h"
#include "exception.h"

void Chess::startGame() noexcept {
    isGameStarted = true;
}

void Chess::makeMove(Coordinate s, Coordinate d) {
    if (!board.isValidMove(s, d)) throw InvalidMoveException{};
    if (!isGameStarted) throw GameNotStartedException{};

    Piece piece = board.getSquare(s);
    if (piece.getTeam() != currentTeam) throw InvalidMoveException{};

    board.makeMove(s, d);

    currentTeam = (currentTeam == Team::White) ? Team::Black : Team::White;
}

void Chess::setupEnter() noexcept {
    isSetupMode = true;
}

void Chess::setupExit() noexcept {
    isSetupMode = false;
}

void Chess::setupPlacePiece(Coordinate p, Piece piece) {
    if (!isSetupMode) throw NotInSetupModeException{};
    board.setSquare(p, piece);
}

void Chess::setupRemovePiece(Coordinate p) {
    if (!isSetupMode) throw NotInSetupModeException{};
    board.clearSquare(p);
}

void Chess::setupSetCurrentTeam(Team team) noexcept {
    if (!isSetupMode) throw NotInSetupModeException{};
    currentTeam = team;
}

Player* Chess::getPlayer(Team team) noexcept {
    auto playerItr = players.find(team);
    if (playerItr == players.end()) {
        return nullptr;
    } else {
        return playerItr->second.get();
    }
}

Board* Chess::getBoard() noexcept {
    return &board;
}

bool Chess::getIsGameStarted() const noexcept {
    return isGameStarted;
}
