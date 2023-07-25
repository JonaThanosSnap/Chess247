#include "piece.h"

Piece::Piece(Team team, int value, char pieceChar): team{team}, value{value}, pieceChar{pieceChar} {}

Piece::~Piece() {}

Team Piece::getTeam() const noexcept {
    return team;
}

int Piece::getValue() const noexcept {
    return value;
}

char Piece::getChar() const noexcept {
    return pieceChar;
}
