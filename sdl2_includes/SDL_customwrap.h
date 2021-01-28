#ifndef SDL_CUSTOM
#define SDL_CUSTOM


#include <SDL2/SDL.h>
#include <iostream>


class SDL_custom
{
public:
    SDL_custom()
    : init_value(SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "init_value: " << init_value << std::endl;
    }
    ~SDL_custom() { SDL_Quit(); }

    void delay(int x) { SDL_Delay(x); }
    bool valid_video() { return init_value >= 0;}


private:
    int init_value;

};

#endif
