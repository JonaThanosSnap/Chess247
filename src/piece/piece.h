#ifndef PIECE_H_
#define PIECE_H_
#include <map>
#include <vector>
#include "../player/player.h"
#include "../coordinate.h"

class Piece {
    Team team;
    int value;
    char pieceChar;

    public:
        Piece(Team team, int value, char pieceChar);

        Team getTeam() const noexcept;
        int getValue() const noexcept;
        char getChar() const noexcept;

        virtual std::vector<Coordinate> getValidMoves(Coordinate p, std::vector<Coordinate> occupied) const noexcept = 0;
        virtual ~Piece() = 0;
};

#endif
