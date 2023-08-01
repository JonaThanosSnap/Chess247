#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <stdexcept>
#include "coordinate.h"

//////////////////////////////////
//                              //
//       Exception Header       //
//                              //
//////////////////////////////////

// invalid move exception
class InvalidMoveException : public std::exception {
    virtual const char* what() const throw();
};

// the game has not started exception
class GameNotStartedException : public std::exception {
    virtual const char* what() const throw();
};

// not in setup mode exception
class NotInSetupModeException : public std::exception {
    virtual const char* what() const throw();
};

// invalid promotion exception
class InvalidPromotionException : public std::exception {
    virtual const char* what() const throw();
};

#endif