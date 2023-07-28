#include "piece.h"

Piece::Piece(Type type, Team team): type{type}, team{team} {};

Piece::Piece(): type{Type::None}, team{Team::White} {};

Piece::Piece(const Piece& other): type{other.type}, team{other.team} {};

Piece::Piece(Piece&& other): type{other.type}, team{other.team} {};

Piece::Type Piece::getType() const noexcept {
    return type;
};

Team Piece::getTeam() const noexcept {
    return team;
};

void Piece::setHasMoved(bool value) noexcept {
    hasMoved = true;
}

void Piece::setCanBeEnPassented(bool value) noexcept {
    canBeEnPassanted = true;
}

bool Piece::getHasMoved() const noexcept {
    return hasMoved;
}

Piece Piece::Empty() {
    return Piece{};
}

Piece Piece::Pawn(Team team) {
    return Piece{Type::Pawn, team};
}

Piece Piece::Rook(Team team) {
    return Piece{Type::Rook, team};
}

Piece Piece::Knight(Team team) {
    return Piece{Type::Knight, team};
}

Piece Piece::Bishop(Team team) {
    return Piece{Type::Bishop, team};
}

Piece Piece::Queen(Team team) {
    return Piece{Type::Queen, team};
}

Piece Piece::King(Team team) {
    return Piece{Type::King, team};
}

void Piece::operator=(const Piece& other) {
    type = other.type;
    team = other.team;
}

void Piece::operator=(Piece&& other) {
    type = other.type;
    team = other.team;
}

bool Piece::operator==(const Piece& other) {
    return type == other.type && team == other.team;
}

bool Piece::operator!=(const Piece& other) {
    return type != other.type || team != other.team;
}