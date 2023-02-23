//note flow controller
#pragma once
#include<SDL.h>

struct FLOW
{
    private:
    bool _pause = false;
    public:
    double deltaTime = 0.0, last = 0.0, now = 0.0;
    bool isPaused() {return _pause;}
    void pause()
    {
        _pause = !_pause;
    }
    
};
extern FLOW gameFlow;