#pragma once

#include <SDL.h>
#include <SDL_TTF.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "types.h"
#include "draw.h"
#include "tile.h"
#include "image.h"
#include "sprite.h"
#include "background.h"
#include "font.h"
#include "formatstring.h"
#include "audio.h"
#include "dialog.h"
#include "stats.h"
#include "inventory.h"
#include "actor.h"
#include "room.h"

// The controller of the RPG engine
class RPG {
public:
    enum Keystate { RELEASED, PRESSED };
    static void init();
    static void exit();

    inline static SDL_Window* game_window() { return _game_window; }
    inline static SDL_Renderer* game_renderer() { return _game_renderer; }

    inline static void quit() { _done = true; }
    inline static bool is_done() { return _done; }

    static void process_events();
    static void step();
    static void draw();
    inline static Keystate key(const SDL_Scancode& key) { return _keys[key]; }
private:
    static struct ActorList {
        Actor** list;
        unsigned int length = 0;
        inline Actor* operator[] (unsigned int i) { return list[i]; }
    } _actors;

    inline static void _each_actor(std::function<void(Actor*)> f) {
        if (_actors.length) {
            for (unsigned int i = 0; i < _actors.length; i++) {
                f(_actors[i]);
            }
        }
    }

    static SDL_Window* _game_window;
    static SDL_Renderer* _game_renderer;
    static int _num_keys;
    static const Uint8* _sdl_keys;
    static Keystate* _keys;
    static bool _done;
};