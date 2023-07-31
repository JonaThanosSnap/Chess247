#ifndef BOARD_H_
#define BOARD_H_
#include <memory>
#include <stdexcept>
#include <vector>
#include "piece.h"
#include "team.h"
#include "coordinate.h"

const int BOARD_WIDTH = 8;
const Coordinate EMPTY_COORDS = Coordinate{-1, -1};

class Board {
    Piece grid[BOARD_WIDTH][BOARD_WIDTH];
    Coordinate enPassantVictim = EMPTY_COORDS;

    // TODO stack of each move taken so far

    bool coordsInRange(Coordinate p) const noexcept;
    Team getEnemyTeam(Team team) const noexcept;
    Coordinate getKingCoords(Team team) const noexcept;
    std::vector<Coordinate> getPieceCoords(Team team) const noexcept;
    bool isInCheck(Team threatenedTeam) const noexcept;

    std::vector<Coordinate> getValidMovesPawn(Coordinate p) const;
    std::vector<Coordinate> getValidMovesRook(Coordinate p) const;
    std::vector<Coordinate> getValidMovesKnight(Coordinate p) const;
    std::vector<Coordinate> getValidMovesBishop(Coordinate p) const;
    std::vector<Coordinate> getValidMovesQueen(Coordinate p) const;
    std::vector<Coordinate> getValidMovesKing(Coordinate p) const;

    void notifyPromotion() const noexcept;

    public:
        Board();
        void makeMove(Coordinate s, Coordinate d);
        void setSquare(Coordinate p, Piece piece);
        void clearSquare(Coordinate p);
        void promote(Coordinate p);
        Piece getSquare(Coordinate p) const;
        bool isSquareThreatened(Team threatenedTeam, Coordinate p) const noexcept;
        bool isValidMove(Coordinate s, Coordinate d) const;
        bool isCheckingMove(Coordinate s, Coordinate d) const;
        std::vector<Coordinate> getValidMoves(Coordinate p) const;
};

#endif
