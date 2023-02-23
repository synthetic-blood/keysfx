#pragma once
#include<SDL.h>
#include<vector>
#include<random>
#include<string>
#include"flow.h"
#include"positions.h"
#include"window.h"
enum noteType
{
    hit, hold
};
enum noteGroupType
{
    solo
};
class Note
{
    //--------------------------
    static bool followRoll;//roll stuff
    static std::vector<int> roll;    
    //---
    static bool preview;
    static Uint32 songLength;
    static Uint32 songPos;
    //---------------------------
    static Uint8 holdAlign;
    //----------------------------
    noteType type;// note specifies---
    noteGroupType group = solo;
    //--------------------------------------
    public://static-----------------
    static Uint16 combo;
    static std::vector<Note> notes;
    static void nextNote();
    static void renderNotes(SDL_Renderer* renderer, double deltaTime);
    //----------------------------
    public:
    bool missed = false;
    bool initialized = false;
    SDL_Color color = {rand()%255+100,rand()%255,rand()%255+32,255};
    int length;
    double pos = -length;
    Uint8 align;
    SDL_Rect note;
    Note()
    {
        //roll purpose
        if(followRoll)
            align = roll[songPos];
        else
            align = rand()%4;
        songPos++;

        Uint8 r = rand()%5;
        if(rand()%9==0)//hold
            type = hit;
        else
            type = hit;
        if(type == hold)
            length = app.nh*4;
        else 
            length = app.nh;
        pos = -length;

        note.x = align*(app.nw)+gamePosition;
        note.y = -pos;
        note.w = app.nw;
        note.h = length;
    }
};