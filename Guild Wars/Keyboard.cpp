#include "Keyboard.hpp"

bool Keyboard::isKeyUp(unsigned char key) {
    return !keyboard_state[key];
}

bool Keyboard::isKeyDown(unsigned char key) {
    return keyboard_state[key];
}


void Keyboard::normalKeysDown(unsigned char key, int x, int y) {
	keyboard_state[key] = true;
}

void Keyboard::normalKeysUp(unsigned char key, int x, int y){
	keyboard_state[key] = false;
}
