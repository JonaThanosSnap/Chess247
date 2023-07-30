#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

class Chess;

// translates inputs into commands for chess game
class InputManager {
private:
    const Chess* game;
public:
    void handleInput();
};

#endif