#ifndef PIECE_H_
#define PIECE_H_

#include "team.h"

//////////////////////////////////
//                              //
//      Piece Class Header      //
//                              //
//////////////////////////////////

class Piece {
    public:
        // enum class for piece types
        enum class Type {
            None,
            Pawn,
            Rook,
            Knight,
            Bishop,
            Queen,
            King
        };

        // constructors
        Piece();
        Piece(const Piece& other);
        Piece(Piece&& other);

        // getters and setters
        Type getType() const noexcept;
        Team getTeam() const noexcept;
        void setHasMoved(bool value) noexcept;
        bool getHasMoved() const noexcept;

        // static factory methods
        static Piece Empty();
        static Piece Pawn(Team team);
        static Piece Rook(Team team);
        static Piece Knight(Team team);
        static Piece Bishop(Team team);
        static Piece Queen(Team team);
        static Piece King(Team team);

        // operator overloads
        void operator=(const Piece& other);
        void operator=(Piece&& other);
        bool operator==(const Piece& other);
        bool operator!=(const Piece& other);

    private:
        // private data members
        Type type;
        Team team;

        bool hasMoved = false;

        // private constructor
        Piece(Type type, Team team);
};

#endif
