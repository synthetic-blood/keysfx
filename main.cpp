#include<SDL.h>
#include<SDL_ttf.h>
#include<random>
#include<time.h>
#include"global.h"
int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    app.create("RyaS", 0.9,0.9);
    mainGameSize = app.nw*4;
    gamePosition = (app.w/2)-(mainGameSize/2);
    Key::loadKeys();
    TTF_Init();
    //SDL_Window *app = SDL_CreateWindow("RyaS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900,600, SDL_WINDOW_SHOWN);
    //SDL_Renderer *renderer = SDL_CreateRenderer(app, -1, 0);
    //SDL_Event eve;
    Text combo;
    bool running = true;
    srand(time(NULL));
    Note::nextNote();
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;

    while (running)
    {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        gameFlow.deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency());
        gameFlow.last = gameFlow.now;
        while (SDL_PollEvent(&app.eve))
        {
            switch (app.eve.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                const Uint8 *kk = SDL_GetKeyboardState(NULL);
                for(int i = 0; i < 4; i++)
                {
                    if(kk[Key::kkeys[i]]&&app.eve.key.repeat==0)
                        Key::keys[i].pressed = true;
                }
                if(kk[SDL_SCANCODE_SPACE]&&app.eve.key.repeat==0)
                {
                    gameFlow.pause();
                }
                if(kk[SDL_SCANCODE_ESCAPE])
                    running = false;
            }
        }
        SDL_SetRenderDrawColor(app.renderer,0,0,0,0);
        SDL_RenderClear(app.renderer);
        combo.display(app.renderer, Note::combo);
        Note::renderNotes(app.renderer, gameFlow.deltaTime);
        Key::renderKeys(app.renderer);
        nymphCore.UpdateExplosionFX(app.renderer, gameFlow.deltaTime);
        SDL_RenderPresent(app.renderer);
    }
    Note::notes.clear();
    SDL_Quit();
    return 0;
}