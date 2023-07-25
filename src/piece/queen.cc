#include "queen.h"

Queen::Queen(Team team): Piece{team, 9, teamToChar(team)} {}

char Queen::teamToChar(Team team) const noexcept {
    switch (team) {
        case Team::White:
            return 'Q';
            break;
        case Team::Black:
            return 'q';
            break;
    }
}

std::vector<Coordinate> Queen::getValidMoves(Coordinate p, std::vector<Coordinate> occupied) const noexcept {
    // TODO
}

Queen::~Queen() {}
