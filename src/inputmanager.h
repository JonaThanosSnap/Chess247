#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

class Chess;

// translates inputs into commands for chess game
class InputManager {
private:
    Chess* game;
public:
    InputManager(Chess*);
    void handleInput();
};

#endif
