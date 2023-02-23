#include"note.h"
#include"key.h"
#include"nymph.h"
#include"window.h"
#include<iostream>
std::vector<Note> Note::notes;
std::vector<std::vector<Note>::iterator> poll_note;
Uint16 Note::combo = 0;
Uint32 Note::songPos = 0;
Uint8 Note::holdAlign = 0;
bool Note::followRoll = false;
bool Note::preview = true;
std::vector<int> Note::roll = {};
Uint32 Note::songLength = roll.size();
void Note::nextNote()
{
    notes.push_back(Note());
}

void Note::renderNotes(SDL_Renderer* renderer, double deltaTime)
{
    if(!notes.empty())
        if((notes.end()-1)->pos > 0)
            if(followRoll)
            {
                if(songPos < songLength)
                    nextNote();
            }
            else//generate notes endlessly
                nextNote();
    for(auto n = notes.begin(); n != notes.end();n++)
    {
        Key &key = Key::keys[n->align];
        //--logic-
            //erase
            if(n->pos > app.h)
            {
                combo=0;
                poll_note.push_back(n);
            }
            //hit
            if(n->type == hit && SDL_HasIntersection(&n->note, &key.key) && key.pressed)
            {
                nymphCore.runExplosionFX(ExplosionFX(n->note,n->color));
                combo++;
                poll_note.push_back(n);
            }
        //update position
        if(!gameFlow.isPaused())
        {
            n->pos+=0.5*deltaTime;
            n->note.y=n->pos;
        }
        //--render-
        SDL_Color c = n->color;
        SDL_SetRenderDrawColor(renderer,c.r,c.g,c.b,255);
        SDL_RenderFillRect(renderer, &n->note);
    }
    //erase
    for(auto p = poll_note.begin(); p != poll_note.end();p++)
        notes.erase(*p);
    poll_note.clear();
}