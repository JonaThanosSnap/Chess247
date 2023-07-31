#include "exception.h"

const char* InvalidMoveException::what() const throw() {
    return "Invalid move.";
}

const char* GameNotStartedException::what() const throw() {
    return "Game not started.";
}

const char* NotInSetupModeException::what() const throw() {
    return "Not in setup mode";
}

const char* InvalidPromotionException::what() const throw() {
    return "Invalid promotion.";
}
