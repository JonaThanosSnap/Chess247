#ifndef PIECE_H_
#define PIECE_H_

#include "team.h"

class Piece {
    enum class Type {
        None,
        Pawn,
        Rook,
        Knight,
        Bishop,
        Queen,
        King
    };

    Type type;
    Team team;

    bool hasMoved = false;
    bool canBeEnPassanted = false;

    // This is private to prevent FORGERY
    Piece(Type type, Team team);

    public:
        Piece();
        Piece(const Piece& other);
        Piece(Piece&& other);

        Type getType() const noexcept;
        Team getTeam() const noexcept;
        void setHasMoved(bool value) noexcept;
        void setCanBeEnPassented(bool value) noexcept;

        static Piece Empty();
        static Piece Pawn(Team team);
        static Piece Rook(Team team);
        static Piece Knight(Team team);
        static Piece Bishop(Team team);
        static Piece Queen(Team team);
        static Piece King(Team team);

        void operator=(const Piece& other);
        void operator=(Piece&& other);
        bool operator==(const Piece& other);
        bool operator!=(const Piece& other);
};

#endif
