#ifndef __GAMEPAD_H__
#define __GAMEPAD_H__

typedef struct{
    bool start;
    bool select;
    bool a;
    bool b;
    bool left;
    bool right;
    bool up;
    bool down;
} State;

class Gamepad{
    private:
        State state;
        bool buttonSelected;
        bool directionSelected;

        static Gamepad* instance;
        Gamepad();

    public:
        Gamepad(Gamepad &other) = delete;

        static Gamepad* getInstance();

        void init();
        bool isButtonSelected();
        bool isDirectionSelected();
        void set(unsigned char value);
        unsigned char get();

        State* getState();
};


#endif