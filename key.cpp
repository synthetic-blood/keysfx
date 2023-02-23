#include"key.h"
std::vector<Key> Key::keys;
std::array<SDL_Scancode, 4> Key::kkeys = {SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, SDL_SCANCODE_F};
Uint8 Key::counter = 0;