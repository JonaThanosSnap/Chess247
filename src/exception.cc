#include "exception.h"

//////////////////////////////////
//                              //
//   Exception Implementation   //
//                              //
//////////////////////////////////

// invalid move exception
const char* InvalidMoveException::what() const throw() {
    return "Invalid move.";
}

//  the game has not started exception
const char* GameNotStartedException::what() const throw() {
    return "Game not started.";
}

// not in setup mode exception
const char* NotInSetupModeException::what() const throw() {
    return "Not in setup mode";
}

// invalid promotion exception
const char* InvalidPromotionException::what() const throw() {
    return "Invalid promotion.";
}
