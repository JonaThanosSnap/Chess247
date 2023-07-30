#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <stdexcept>
#include "coordinate.h"

class InvalidMoveException : public std::exception {
    virtual const char* what() const throw();
};

class GameNotStartedException : public std::exception {
    virtual const char* what() const throw();
};

class NotInSetupModeException : public std::exception {
    virtual const char* what() const throw();
};

class InvalidPromotionException : public std::exception {
    virtual const char* what() const throw();
};

#endif