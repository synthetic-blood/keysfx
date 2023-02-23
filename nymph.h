#pragma once
#include<SDL.h>
#include<vector>
#include"window.h"
float randomizeFloatInRange(float max, float min);
struct Particle
{
    float size = rand()%16+8;
    float vx = 0, vy = 0;
    float x = 0, y = 0;
    SDL_Rect rect;
    Particle(float x, float y, float vx, float vy):x(x),y(y),vx(vx),vy(vy),rect({x,y,size,size}){}
    Offset(double deltaTime){x+=vx*deltaTime;y+=vy*deltaTime;rect.x=x;rect.y=y;}
};
struct ExplosionFX
{
    private:
    std::vector<std::vector<Particle>::iterator> pool;
    Uint32 started = SDL_GetTicks();
    Uint16 time = 3000;
    Uint16 timer = 0;
    SDL_Color color;
    std::vector<Particle> particles;
    public:
    ExplosionFX(SDL_Rect rect, SDL_Color color):color(color)
    {
        int skip = 5;
        for(int y = 0; y < rect.h; y+=skip)
        {
            for(int x = 0; x < rect.w; x+=skip)
            {
                float tx = ((rand()%1000)+100)*0.001;
                float ty = ((rand()%1000)+100)*0.001;
                if(rand()%2)
                    tx= -tx;
                if(rand()%2)
                    ty= -ty;
                particles.push_back(Particle(rect.x+x,rect.y+y, tx, ty));//randomizeFloatInRange(-1,1),randomizeFloatInRange(-1,1)));
            }
        }
    }
    void Update(SDL_Renderer *renderer, double deltaTime)
    {
        timer = SDL_GetTicks() - started;
        if(timer>time)
        {
            particles.clear();
            return;           
        }
        SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,1000-(timer/time*255));
        for(auto p = particles.begin(); p != particles.end(); p++)
        {
            if(p->y<0||p->y>app.h||p->x>app.w||p->x<0)
                pool.push_back(p);
            p->Offset(deltaTime);
            SDL_RenderFillRect(renderer, &p->rect);
        }
        for(auto pl = pool.begin(); pl != pool.end(); pl++)
        {
            particles.erase(*pl);
        }
        pool.clear();
    }
};
struct Nymph
{
    std::vector<ExplosionFX> v_ExplosionFX;
    void UpdateExplosionFX(SDL_Renderer *renderer, double deltaTime)
    {
        for(auto e = v_ExplosionFX.begin(); e != v_ExplosionFX.end(); e++)
        {
            e->Update(renderer, deltaTime);
        }
    }
    void runExplosionFX(ExplosionFX efx)
    {
        v_ExplosionFX.push_back(efx);
    }
    ~Nymph()
    {
        v_ExplosionFX.clear();
    }
};

extern Nymph nymphCore;