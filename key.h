#include<SDL.h>
#include<vector>
#include<array>
#include"flow.h"
#include"positions.h"
#include"window.h"
class Key
{
    public:
    static std::vector<Key> keys; 
    static void loadKeys()
    {
        for(int i = 0; i < 4;i++)
        {
            keys.push_back(Key());
        }
    }
	static std::array<SDL_Scancode, 4> kkeys;
    static Uint8 counter;
    static void renderKeys(SDL_Renderer* renderer)
    {
		const Uint8 *kk = SDL_GetKeyboardState(NULL);
        for(auto k = keys.begin(); k != keys.end(); k++)
        {
            SDL_SetRenderDrawColor(renderer, 255,255,255,255);
            if(!gameFlow.isPaused())
			    k->effect = kk[kkeys[k->id]];
            if(k->effect)
            {
                SDL_RenderFillRect(renderer, &k->key);
            }
            else
            {
                SDL_RenderDrawRect(renderer, &k->key);
            }
			k->pressed = false;
        }
    }
    public:
    bool pressed = false, effect = false, holding = false;
    Uint8 id = counter;
    SDL_Rect key;

	Key():key({id*app.nw+gamePosition,app.h-app.kh,app.nw,app.kh}){counter++;}
};