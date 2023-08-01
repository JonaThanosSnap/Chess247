#include "piece.h"

//////////////////////////////////
//                              //
//  Piece Class Implementation  //
//                              //
//////////////////////////////////

// private constructor
Piece::Piece(Type type, Team team): type{type}, team{team} {};

// default constructor
Piece::Piece(): type{Type::None}, team{Team::White} {};

// copy constructor
Piece::Piece(const Piece& other): type{other.type}, team{other.team}, hasMoved{other.hasMoved} {};

// move constructor
Piece::Piece(Piece&& other): type{other.type}, team{other.team}, hasMoved{other.hasMoved} {};

// get the type of piece
Piece::Type Piece::getType() const noexcept {
    return type;
};

// get the team of piece
Team Piece::getTeam() const noexcept {
    return team;
};

// set whether the piece has moved
void Piece::setHasMoved(bool value) noexcept {
    hasMoved = value;
}

//  get whether the piece has moved
bool Piece::getHasMoved() const noexcept {
    return hasMoved;
}

// static factory methods
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

// assignment operator overloads
void Piece::operator=(const Piece& other) {
    type = other.type;
    team = other.team;
    hasMoved = other.hasMoved;
}

void Piece::operator=(Piece&& other) {
    type = other.type;
    team = other.team;
    hasMoved = other.hasMoved;
}

// comparison operator overloads
bool Piece::operator==(const Piece& other) {
    return type == other.type && team == other.team;
}

bool Piece::operator!=(const Piece& other) {
    return type != other.type || team != other.team;
}