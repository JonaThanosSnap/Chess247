#include "inputmanager.h"
#include <string>
#include <iostream>

void InputManager::handleInput() {
    // read in one command at a time and handle it
    std::string cmd;
    std::cin >> cmd;

    if (cmd == "game") {
        std::string white, black;
        std::cin >> white >> black;

    } else if (cmd == "resign") {
        // concede game to opponent

    } else if (cmd == "move") {
        std::string start, end;
        std::cin >> start >> end;

    } else if (cmd == "setup") {
        

    } else {
        std::cout << "Invalid command: " << cmd << std::endl;
    }
}
