#include "bishop.h"

Bishop::Bishop(Team team): Piece{team, 3, teamToChar(team)} {}

char Bishop::teamToChar(Team team) const noexcept {
    switch (team) {
        case Team::White:
            return 'B';
            break;
        case Team::Black:
            return 'b';
            break;
    }
}

std::vector<Coordinate> Bishop::getValidMoves(Coordinate p, std::vector<Coordinate> occupied) const noexcept {
    // TODO
}

Bishop::~Bishop() {}
