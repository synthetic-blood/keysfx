#include<SDL_ttf.h>
#include<sstream>
#include"window.h"
class Text
{
    TTF_Font *pixel;
    SDL_Color color = {255,255,255,255};
    SDL_Surface *panelS;
    SDL_Texture *panelT;
    SDL_Rect dst = {app.w/2,app.h/2,0,0};
    std::stringstream text;
    public:
    Text()
    {
        pixel = TTF_OpenFont("pixel.ttf",120);
    }
    void display(SDL_Renderer *renderer, Uint16 combo)
    {
        text << "x" << combo;
        panelS = TTF_RenderText_Solid(pixel, text.str().c_str(), color);
        panelT = SDL_CreateTextureFromSurface(renderer, panelS);
        TTF_SizeText(pixel, text.str().c_str(), &dst.w, &dst.h);
        dst.x = (app.w/2)-(dst.w/2);
        text.str("");
        SDL_RenderCopy(renderer, panelT, NULL, &dst);

        SDL_FreeSurface(panelS);
        SDL_DestroyTexture(panelT);
    }
};