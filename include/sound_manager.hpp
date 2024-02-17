#pragma once
#include <raylib.h>
#include <map>
#include <string>

enum class soundfx;
class sound;
using sound_item = std::pair<soundfx,sound>;

class sound{
    public:
        Sound fx;
        sound();
        sound(Sound);
        void play();
        
};

enum class soundfx{
    BLIP1,
    BLIP2,
};

class sound_manager{
    private:
        static sound_manager *sound_manager_instance ;
        sound_manager();
       ~sound_manager();
        std::map<soundfx, sound> sound_list = {};
        void load_sound(soundfx SFX, const char* path);
    public:
      static sound_manager * get_sound_manager_instance();
        void play_sound(soundfx SFX);
};


