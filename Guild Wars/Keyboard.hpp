#ifndef Keyboard_h
#define Keyboard_h

class Keyboard {
public:
    Keyboard();

    void update();

private:
    map<unsigned char, bool> keyboard_state;

}

#endif
