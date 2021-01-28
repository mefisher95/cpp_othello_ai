#ifndef Game_Object_H
#define Game_Object_H

#include <SDL2/SDL.h>

class Game_Object
{
public:
    virtual void draw() = 0;
private:
};

#endif
