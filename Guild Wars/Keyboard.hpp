#ifndef Keyboard_h
#define Keyboard_h

#include <map>

using namespace std;

class Keyboard {
public:
    Keyboard() {;}

    bool isKeyUp(unsigned char key);
    bool isKeyDown(unsigned char key);

    void normalKeysUp(unsigned char key, int x, int y);
    void normalKeysDown(unsigned char key, int x, int y);

private:
    map<unsigned char, bool> keyboard_state;

};

#endif
