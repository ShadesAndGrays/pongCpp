#include "sound_manager.hpp"
#include <map>

#include <raylib.h>
#include <string>

sound_manager *sound_manager::sound_manager_instance = nullptr;

sound_manager::sound_manager(){
    InitAudioDevice();
    load_sound(soundfx::BLIP1, "sounds/pickupCoin.wav");
    load_sound(soundfx::GOAL,"sounds/goal.wav");
    load_sound(soundfx::GOAL,"sounds/goal.wav");
    load_sound(soundfx::GOOD_END,"sounds/goodEnding.wav");
    load_sound(soundfx::BAD_END,"sounds/badEnding.wav");

}
sound_manager::~sound_manager(){
for (sound_item i: sound_list){
    UnloadSound(i.second.fx);
}
}
sound::sound(){}
sound::sound(Sound sfx):fx(sfx){
}

void sound::play(){
   PlaySound(fx); 
}
sound_manager * sound_manager::get_sound_manager_instance(){
    if (sound_manager_instance == nullptr)
        sound_manager_instance = new sound_manager;
    return sound_manager_instance;
}
void sound_manager::load_sound(soundfx SFX, const char* path){
    sound_item si;
    si.first = SFX;
    si.second = sound(LoadSound(path));
    sound_list.insert(si);
}
void sound_manager::play_sound(soundfx SFX){
        sound_list.at(SFX).play();
}
