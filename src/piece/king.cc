#include "king.h"

King::King(Team team): Piece{team, 0, teamToChar(team)} {}

char King::teamToChar(Team team) const noexcept {
    switch (team) {
        case Team::White:
            return 'K';
            break;
        case Team::Black:
            return 'k';
            break;
    }
}

std::vector<Coordinate> King::getValidMoves(Coordinate p, std::vector<Coordinate> occupied) const noexcept {
    // TODO
}

King::~King() {}
