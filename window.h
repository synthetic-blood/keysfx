#pragma once
#include<SDL.h>
struct WINDOW
{
    static bool videoInitialized; 
    SDL_Window* app;
    SDL_Renderer* renderer;
    SDL_Event eve;
    //window properties
    private:
    bool running = false;
    public:
    Uint16 w = 0;
    Uint16 h = 0;
    SDL_DisplayMode display;
    //object properties
    Uint16 nh;
    Uint16 nw;
    Uint16 kh;
    //----------------
    //gets
    bool isRunning()
    {
        return running;
    }
    
    //----------------
    void create(const char* title, float factorX, float factorY)
    {
        SDL_GetDesktopDisplayMode(0, &display);
        w = display.w * factorX;
        h = display.h * factorY;
        nw = w/16;
        nh = h/8;
        kh = 100;//float(h)/16.f;
        app = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(app, -1, 0);
        running = true;
    }
     
    void handleEvents()
    {
        while (SDL_PollEvent(&eve))
        {
            switch (eve.type)
            {
                case SDL_QUIT:
                    running = false;
            }
        }
    }
    ~WINDOW()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(app);
    }
};
extern WINDOW app;