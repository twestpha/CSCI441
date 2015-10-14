#include "Keyboard.hpp"

void Keyboard::normalKeysDown(unsigned char key, int x, int y) {
    if(key == 'q' || key == 'Q' || key == 27)
        exitProgram(0);

	keyboard_state[key] = true;
}

void Keyboard::normalKeysUp(unsigned char key, int x, int y){
	keyboard_state[key] = false;
}
