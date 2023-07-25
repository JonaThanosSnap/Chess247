#include "pawn.h"

Pawn::Pawn(Team team): Piece{team, 1, teamToChar(team)} {}

char Pawn::teamToChar(Team team) const noexcept {
    switch (team) {
        case Team::White:
            return 'P';
            break;
        case Team::Black:
            return 'p';
            break;
    }
}

std::vector<Coordinate> Pawn::getValidMoves(Coordinate p, std::vector<Coordinate> occupied) const noexcept {
    // TODO
}

Pawn::~Pawn() {}
