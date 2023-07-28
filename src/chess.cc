#include "chess.h"
#include "exception.h"

void Chess::startGame() noexcept {
    isGameStarted = true;
}

void Chess::makeMove(Coordinate s, Coordinate d) {
    if (!isGameStarted) throw GameNotStartedException{};
    if (!board.isValidMove(s, d)) throw InvalidMoveException{};

    Piece piece = board.getSquare(s);
    piece.setHasMoved(true);

    // Handle pawn double move (for en passant purposes)
    if (piece.getType() == Piece::Type::Pawn && s.manhattanDistance(d) == 2) {
        piece.setCanBeEnPassented(true);
    }
    
    // Move piece
    board.clearSquare(s);
    board.setSquare(d, piece);

    // Handle move rook on castle
    if (piece.getType() == Piece::Type::King && s.manhattanDistance(d) == 2) {
        Coordinate delta = d - s;
        delta.normalizeComponents();  // sets component values to 1

        // Find rook
        // We assume that there are no pieces in between the king
        // and friendly unmoved rook in the direction of delta and that
        // candidate will always be in range before finding rook.
        Coordinate rookCoords = s;
        Piece rookPiece;
        while (piece.getType() != Piece::Type::Rook) {
            rookCoords = rookCoords + delta;
            rookPiece = board.getSquare(rookCoords);
        }

        // Move rook to opposite side of king
        board.clearSquare(rookCoords);
        board.setSquare(d - delta, rookPiece);
        rookPiece.setHasMoved(true);
    }

    // TODO Handle pawn promotion
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
