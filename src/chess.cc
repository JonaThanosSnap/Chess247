#include "chess.h"
#include "exception.h"

void Chess::startGame() noexcept {
    isGameStarted = true;
}

void Chess::endGame() noexcept {
    isGameStarted = false;
}

void Chess::makeMove(Coordinate s, Coordinate d, char promotion) {
    if (!board.isValidMove(s, d)) throw InvalidMoveException{};
    if (!isGameStarted) throw GameNotStartedException{};
    //std::cout << "(" << s.x() << ", " << s.y() << ")" << std::endl;
    Piece piece = board.getSquare(s);
    if (piece.getTeam() != currentTeam) throw InvalidMoveException{};

    board.makeMove(s, d, promotion);

    currentTeam = (currentTeam == Team::White) ? Team::Black : Team::White;

}

void Chess::setupEnter() noexcept {
    isSetupMode = true;
    justSetup = true;
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

void Chess::setPlayer(Team team, Player* player) noexcept {
    players[team] = std::unique_ptr<Player>(player);
}

Player* Chess::getPlayer(Team team) noexcept {
    auto playerItr = players.find(team);
    if (playerItr == players.end()) {
        return nullptr;
    } else {
        return playerItr->second.get();
    }
}


Player* Chess::getCurrentPlayer() noexcept {
    return getPlayer(currentTeam);
}

Board* Chess::getBoard() noexcept {
    return &board;
}

bool Chess::getIsGameStarted() const noexcept {
    return isGameStarted;
}

bool Chess::getIsSetupMode() const noexcept {
    return isSetupMode;
}

std::string Chess::winner() {
    if(board.isCheckMate(currentTeam)){
        Team loser = currentTeam;
        scores[loser == Team::White ? 1 : 0] += 1;
        return (loser == Team::White) ? "Black" : "White";
    };
    return "";
}


Team Chess::resign() {
    Team loser = currentTeam;
    scores[loser == Team::White ? 1 : 0] += 1;
    endGame();
    return (loser == Team::White) ? Team::Black : Team::White;
}

void Chess::boardReset() {
    board = Board();
}

void Chess::finalScores() const noexcept {
    std::cout << "Final Score:" << std::endl;
    std::cout << "White: " << scores[0] << std::endl;
    std::cout << "Black: " << scores[1] << std::endl;
}

bool Chess::isJustSetup() const noexcept {
    return justSetup;
}

void Chess::finishedSetup() noexcept {
    justSetup = false;
}