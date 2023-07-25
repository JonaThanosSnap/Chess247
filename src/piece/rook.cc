#include "rook.h"

Rook::Rook(Team team): Piece{team, 5, teamToChar(team)} {}

char Rook::teamToChar(Team team) const noexcept {
    switch (team) {
        case Team::White:
            return 'R';
            break;
        case Team::Black:
            return 'r';
            break;
    }
}

std::vector<Coordinate> Rook::getValidMoves(Coordinate p, std::vector<Coordinate> occupied) const noexcept {
    // TODO
}

Rook::~Rook() {}
