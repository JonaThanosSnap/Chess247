#include "board.h"
#include "exception.h"

#include <algorithm>

Board::Board() {
    // Create pawns
    for (int i = 0; i < BOARD_WIDTH; i++) {
        grid[1][i] = Piece::Pawn(Team::White);
        grid[6][i] = Piece::Pawn(Team::Black);
    }

    // White back-rank pieces
    grid[0][0] = Piece::Rook(Team::White);
    grid[0][1] = Piece::Bishop(Team::White);
    grid[0][2] = Piece::Knight(Team::White);
    grid[0][3] = Piece::Queen(Team::White);
    grid[0][4] = Piece::King(Team::White);
    grid[0][5] = Piece::Knight(Team::White);
    grid[0][6] = Piece::Bishop(Team::White);
    grid[0][7] = Piece::Rook(Team::White);

    // Black back-rank pieces
    grid[7][0] = Piece::Rook(Team::Black);
    grid[7][1] = Piece::Bishop(Team::Black);
    grid[7][2] = Piece::Knight(Team::Black);
    grid[7][3] = Piece::Queen(Team::Black);
    grid[7][4] = Piece::King(Team::Black);
    grid[7][5] = Piece::Knight(Team::Black);
    grid[7][6] = Piece::Bishop(Team::Black);
    grid[7][7] = Piece::Rook(Team::Black);

    // history.push_back(*this);
}

void Board::makeMove(Coordinate s, Coordinate d) {
    // Precondition: isValidMove(s, d) is true
    Piece piece = getSquare(s);
    piece.setHasMoved(true);

    // Move piece
    clearSquare(s);
    setSquare(d, piece);

    // Handle move rook on castle
    if (piece.getType() == Piece::Type::King && abs((d - s).x()) == 2) {
        Coordinate delta = d - s;
        delta.normalizeComponents();  // sets component values to 1

        // Find rook
        // We assume that there are no pieces in between the king
        // and friendly unmoved rook in the direction of delta and that
        // candidate will always be in range before finding rook.
        Coordinate rookCoords = s;
        Piece rookPiece;
        while (rookPiece.getType() != Piece::Type::Rook) {
            rookCoords = rookCoords + delta;
            rookPiece = getSquare(rookCoords);
        }

        // Move rook to opposite side of king
        clearSquare(rookCoords);
        setSquare(d - delta, rookPiece);
        rookPiece.setHasMoved(true);
    }

    // TODO Handle pawn promotion

    // Kill piece if en passant has occurred

    // Pawn logic
    if (piece.getType() == Piece::Type::Pawn) {
        Coordinate pawnDelta = d - s;

        if (abs(pawnDelta.y()) == 2) {
            // piece is a pawn that double moved
            enPassantVictim = d;
        } else { // if we dont move 2 squares
            if (pawnDelta.x() != 0) { //if we move diagonally
                Coordinate victimPosition = d+Coordinate{0, piece.getTeam() == Team::White ? -1 : 1};
                if (victimPosition == enPassantVictim) {
                    clearSquare(victimPosition);
                }
            }
            enPassantVictim = EMPTY_COORDS;
        }

        if((piece.getTeam() == Team::White && d.y() == 7) || (piece.getTeam() == Team::Black && d.y() == 0)){
            char promotion;

            std::cin >> promotion;

            switch(promotion) {

                case('q'):
                    setSquare(d, Piece::Queen(piece.getTeam()));
                    break;
                case('r'):
                    setSquare(d, Piece::Rook(piece.getTeam()));
                    break;
                case('b'):
                    setSquare(d, Piece::Bishop(piece.getTeam()));
                    break;
                case('n'):
                    setSquare(d, Piece::Knight(piece.getTeam()));
                    break;
                default:
                    throw InvalidPromotionException();
                    break;
            }
        }
    }

    if(piece.getType() != Piece::Type::Pawn) {
        // no pawns double moved this turn
        enPassantVictim = EMPTY_COORDS;
    }
}

void Board::setSquare(Coordinate p, Piece piece) {
   // Construct new Piece and place it into a grid square
   if (!coordsInRange(p)) throw std::out_of_range("Board::setSquare: coords out of range");
   grid[p.y()][p.x()] = piece;
}

// checks whether or not a specific coordinate is in range
bool Board::coordsInRange(Coordinate p) const noexcept {
    return (
        p.x() >= 0 && p.x() < BOARD_WIDTH &&
        p.y() >= 0 && p.y() < BOARD_WIDTH
    );
}

// removes a piece at coordinate p
void Board::clearSquare(Coordinate p) {
    if (!coordsInRange(p)) throw std::out_of_range("Board::clearSquare: coords out of range");
    grid[p.y()][p.x()] = Piece::Empty();
}

// retrieves the piece at coordiante p
Piece Board::getSquare(Coordinate p) const noexcept {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getSquare: coords out of range");
    return grid[p.y()][p.x()];
}

// determines whether or not a move is valid
bool Board::isValidMove(Coordinate s, Coordinate d) const {
    // the game plan:
    //  - check that the start and end coordinates are inside the board
    //  - check that the move is valid without considering checks
    //  - check if we end the turn with the king in check
    
    if (!coordsInRange(s)) throw std::out_of_range("Board::isValidMove: start position out of range");
    if (!coordsInRange(d)) throw std::out_of_range("Board::isValidMove: end position out of range");

    Piece piece = getSquare(s);
    Piece::Type pieceType = piece.getType();
    Team pieceTeam = piece.getTeam();

    // Starting square is empty
    if (pieceType == Piece::Type::None) {
        return false;
    }

    // Check if move is in the piece's valid moves
    std::vector<Coordinate> validMoves = getValidMoves(s);
    if (std::find(validMoves.begin(), validMoves.end(), d) == validMoves.end()) {
        return false;
    }

    // Check if move will put the king in check by simulating the move then rolling back
    Board mockBoard{*this};
    mockBoard.clearSquare(s);
    mockBoard.setSquare(d, piece);
    if (mockBoard.isInCheck(pieceTeam)) {
        return false;
    } else {
        return true;
    }
}

std::vector<Coordinate> Board::getValidMoves(Coordinate p) const {
    // getValidMoves => first finds all 'possible' moves without considering check.         

    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMoves: position out of range");

    Piece piece = getSquare(p);
    Piece::Type pieceType = piece.getType();
    Team pieceTeam = piece.getTeam();

    // return a vector of squares where the piece can move
    //  according to its rules. it does NOT take checks into account.
    std::vector<Coordinate> validMoves;
    switch (pieceType) {
        case (Piece::Type::None):
            return validMoves;
        case (Piece::Type::Pawn):
            validMoves = getValidMovesPawn(p);
            break;
        case (Piece::Type::Rook):
            validMoves = getValidMovesRook(p);
            break;
        case (Piece::Type::Knight):
            validMoves = getValidMovesKnight(p);
            break;
        case (Piece::Type::Bishop):
            validMoves = getValidMovesBishop(p);
            break;
        case (Piece::Type::Queen):
            validMoves = getValidMovesQueen(p);
            break;
        case (Piece::Type::King):
            validMoves = getValidMovesKing(p);
            break;
    }

    return validMoves;
}

std::vector<Coordinate> Board::getValidMovesPawn(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMovePawn: position out of range");
    
    Team team = getSquare(p).getTeam();

    std::vector<Coordinate> validMoves;

    std::vector<Coordinate> deltas = {Coordinate{0, team == Team::White ? 1 : -1}};

    if(!getSquare(p).getHasMoved()){
        deltas.push_back(Coordinate{0, team == Team::White ? 2 : -2});
    }

    for(Coordinate delta : deltas){
        Coordinate candidate = p + delta;
        if (coordsInRange(candidate)){
            Piece otherPiece = getSquare(candidate);
            // can only move to location if it is empty
            if (otherPiece == Piece::Empty()) {
                validMoves.push_back(candidate);
            }
        }   
    }
    
    // check captures
    int direction = (team == Team::White ? 1 : -1);
    std::vector<Coordinate> capture = {Coordinate{1,direction}, Coordinate{-1,direction}};
    for(Coordinate delta : capture){
        Coordinate candidate = p + delta;
        if (coordsInRange(candidate)){
            Piece otherPiece = getSquare(candidate);
            // can take a piece if it is an ememy and not empty
            if(otherPiece.getTeam() != team && otherPiece != Piece::Empty()){
                validMoves.push_back(candidate);
            }
        }
    }
    // check en passante
    if(p+Coordinate{1,0} == enPassantVictim){
        validMoves.push_back(p+Coordinate{1,direction});
    }
    
    if(p+Coordinate{-1,0} == enPassantVictim){
        validMoves.push_back(p+Coordinate{-1,direction});
    }

    return validMoves;
}

std::vector<Coordinate> Board::getValidMovesRook(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMovesRook: position out of range");

    Team team = getSquare(p).getTeam();

    std::vector<Coordinate> validMoves;

    // a delta is a direction that a piece can slide
    std::vector<Coordinate> deltas = {Coordinate{0, -1}, Coordinate{0, 1}, Coordinate{-1, 0}, Coordinate{1, 0}};
    for (Coordinate delta : deltas) {
        Coordinate candidate = p + delta;
        // while the candidate is in range
        while (coordsInRange(candidate)) {
            Piece otherPiece = getSquare(candidate);
            // if the current candidate location has a piece on it
            if (otherPiece != Piece::Empty()) {
                // stop iteration when another piece is encountered
                if (otherPiece.getTeam() != team) {
                    // other piece is on other team
                    validMoves.push_back(candidate);
                }
                break;
            }

            validMoves.push_back(candidate);
            candidate = candidate + delta;
        }
    }
    return validMoves;
}

std::vector<Coordinate> Board::getValidMovesKnight(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMoveKnight: position out of range");
    Team team = getSquare(p).getTeam();

    std::vector<Coordinate> validMoves;
    std::vector<Coordinate> deltas = {
        Coordinate{-1, -2},
        Coordinate{-1, 2},
        Coordinate{1, -2},
        Coordinate{1, 2},
        Coordinate{-2, -1},
        Coordinate{-2, 1},
        Coordinate{2, -1},
        Coordinate{2, 1}
    };
    for (Coordinate delta : deltas) {
        Coordinate candidate = p + delta;
        if (coordsInRange(candidate)){
            Piece otherPiece = getSquare(candidate);
            // can only move to location if it is empty or occupied by an enemy
            if (otherPiece == Piece::Empty() || otherPiece.getTeam() != team) {
                validMoves.push_back(candidate);
            }
        }
    }
    return validMoves;
}

std::vector<Coordinate> Board::getValidMovesBishop(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMoveBishop: position out of range");
    Team team = getSquare(p).getTeam();

    std::vector<Coordinate> validMoves;
    std::vector<Coordinate> deltas = {Coordinate{1, 1}, Coordinate{1, -1}, Coordinate{-1, 1}, Coordinate{-1, -1}};
    for (Coordinate delta : deltas) {
        Coordinate candidate = p + delta;
        // while the candidate is in range
        while (coordsInRange(candidate)) {
            Piece otherPiece = getSquare(candidate);
            // if the current candidate location has a piece on it
            if (otherPiece != Piece::Empty()) {
                // if the piece is an enemy, we can move there then break
                if (otherPiece.getTeam() != team) {
                    validMoves.push_back(candidate);
                }
                break;
            }

            validMoves.push_back(candidate);
            candidate = candidate + delta;
        }
    }
    return validMoves;
}

std::vector<Coordinate> Board::getValidMovesQueen(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMoveQueen: position out of range");
    Team team = getSquare(p).getTeam();

    std::vector<Coordinate> validMoves;
    std::vector<Coordinate> deltas = {Coordinate{1, 1}, Coordinate{1, -1}, Coordinate{-1, 1}, Coordinate{-1, -1}, Coordinate{0, -1}, Coordinate{0, 1}, Coordinate{-1, 0}, Coordinate{1, 0}};
    for (Coordinate delta : deltas) {
        Coordinate candidate = p + delta;
        // while the candidate is in range
        while (coordsInRange(candidate)) {
            Piece otherPiece = getSquare(candidate);
            // if the current candidate location has a piece on it
            if (otherPiece != Piece::Empty()) {
                // if the piece is an enemy, we can move there then break
                if (otherPiece.getTeam() != team) {
                    validMoves.push_back(candidate);
                }
                break;
            }

            validMoves.push_back(candidate);
            candidate = candidate + delta;
        }
    }
    return validMoves;
}

std::vector<Coordinate> Board::getValidMovesKing(Coordinate p) const {
    if (!coordsInRange(p)) throw std::out_of_range("Board::getValidMoveKing: position out of range");
    // do the same as rook and bishop but only one square
    // consider castle by checking the following items
    // 1. king has not moved
    // 2. rook has not moved
    // 3. no pieces between king and rook
    // 4. king is not in check
    Team team = getSquare(p).getTeam();

    std::vector<Coordinate> validMoves;
    std::vector<Coordinate> deltas = {
        Coordinate{1, -1},
        Coordinate{1, 1},
        Coordinate{1, 0},
        Coordinate{0, -1},
        Coordinate{0, 1},
        Coordinate{-1, -1},
        Coordinate{-1, 0},
        Coordinate{-1, 1}
    };
    for (Coordinate delta : deltas) {
        Coordinate candidate = p + delta;
        if (coordsInRange(candidate)){
            Piece otherPiece = getSquare(candidate);
            // can only move to location if it is empty or occupied by an enemy
            if (otherPiece == Piece::Empty() || otherPiece.getTeam() != team) {
                validMoves.push_back(candidate);
            }
        }
    }

    // check for castle
    if(!getSquare(p).getHasMoved()){

        int rowNum = team == Team::White ? 0 : 7;

        Coordinate kingSideRookLocation = Coordinate{7, rowNum};
        Coordinate queenSideRookLocation = Coordinate{0, rowNum};

        Piece kingSideRook = getSquare(kingSideRookLocation);
        Piece queenSideRook = getSquare(queenSideRookLocation);
        bool canCastle = true;

        if(!kingSideRook.getHasMoved()) {
            // check if there are any pieces between the king and the king side rook
            for(int x = p.x() + 1; x < kingSideRookLocation.x(); x++) {
                if(getSquare(Coordinate(x, rowNum)) != Piece::Empty()){
                    canCastle = false;
                    break;
                }
            }
            if(canCastle) {
                validMoves.push_back(Coordinate(p.x() + 2, rowNum));
            }
        }

        canCastle = true;

        if(!queenSideRook.getHasMoved()){
            // check if there are any pieces between the king and the queen side rook
            for(int x = p.x() - 1; x > 0; x--) {
                if(getSquare(Coordinate(x, rowNum)) != Piece::Empty()){
                    canCastle = false;
                    break;
                }
            }
            if(canCastle) {
                validMoves.push_back(Coordinate(p.x() - 2, rowNum));
            }
        }
    }
    return validMoves;
}

Team Board::getEnemyTeam(Team team) const noexcept {
    return team == Team::White ? Team::Black : Team::White;
}

Coordinate Board::getKingCoords(Team team) const noexcept {
    for(int y = 0; y < BOARD_WIDTH; y++){
        for(int x = 0; x < BOARD_WIDTH; x++){
            if(grid[y][x].getTeam() == team && grid[y][x].getType() == Piece::Type::King){
                return Coordinate(x,y);
            }
        }
    }
}

std::vector<Coordinate> Board::getPieceCoords(Team team) const noexcept {
    std::vector<Coordinate> pieceCoords;
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_WIDTH; y++) {
            Coordinate coords = Coordinate{x, y};
            Piece piece = getSquare(coords);
            if (piece.getTeam() == team) {
                pieceCoords.push_back(coords);
            }
        }
    }
    return pieceCoords;
}

bool Board::isSquareThreatened(Team threatenedTeam, Coordinate p) const noexcept {
    std::vector<Coordinate> enemyMoves;
    std::vector<Coordinate> enemyPieceCoords = getPieceCoords(getEnemyTeam(threatenedTeam));
    for (Coordinate coords : enemyPieceCoords) {
        std::vector<Coordinate> enemyPieceValidMoves = getValidMoves(coords);
        if (std::find(enemyPieceValidMoves.begin(), enemyPieceValidMoves.end(), p) != enemyPieceValidMoves.end()) {
            return true;
        }
    }
    return false;
}

bool Board::isInCheck(Team threatenedTeam) const noexcept {
    Coordinate kingCoords = getKingCoords(threatenedTeam);
    return isSquareThreatened(threatenedTeam, kingCoords);
}

bool Board::pawnOnLastRow(){
    for(int i = 0; i < BOARD_WIDTH; i++) {
        if(grid[0][i] == Piece::Pawn(Team::Black) || grid[7][i] == Piece::Pawn(Team::White)){
            return true;
        }
    }
    return false;
}
bool Board::correctNumberOfKings(){
    int whiteKingCount = 0;
    int blackKingCount = 0;
    for(int i = 0; i < BOARD_WIDTH; i++) {
        for(int j = 0; j < BOARD_WIDTH; j++) {
            if(grid[i][j] == Piece::King(Team::White)){
                whiteKingCount++;
            }
            if(grid[i][j] == Piece::King(Team::Black)){
                blackKingCount++;
            }
        }
    }
    return whiteKingCount == 1 && blackKingCount == 1;
}