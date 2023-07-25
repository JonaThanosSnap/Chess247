#include "knight.h"

Knight::Knight(Team team): Piece{team, 3, teamToChar(team)} {}

char Knight::teamToChar(Team team) const noexcept {
    switch (team) {
        case Team::White:
            return 'K';
            break;
        case Team::Black:
            return 'k';
            break;
    }
}

std::vector<Coordinate> Knight::getValidMoves(Coordinate p, std::vector<Coordinate> occupied) const noexcept {
    // TODO
}

Knight::~Knight() {}
