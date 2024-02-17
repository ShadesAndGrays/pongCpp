#include "ball.hpp"
#include "ai.hpp"
#include "player.hpp"
#include <fmt/core.h>
#include <raylib.h>
#include "constants.hpp" 
#include "sound_manager.hpp"
extern player * ptr_player; 
extern ai * ptr_ai;
ball::ball() : speed(180.0) ,size(10.0f),position({0,0}), velocity(Vector2{-1.2,0.8}){

    
}
void ball::process(float delta){
    
    move(delta);
    
}
void ball::set_positon(Vector2 pos){
    position = pos;

}

Vector2 ball::get_position(){
    return position;
}
void ball::move(float delta){
    velocity = check_collision();
    position.x += velocity.x * speed * delta; 
    position.y += velocity.y * speed * delta; 
}
bool ball::is_colliding(player* ptr_player){

    Vector2 player_position = ptr_player->get_position();
    Vector2 current_postion = position;
    if (abs(player_position.x - current_postion.x) > ptr_player->get_size().x)
        return false;
    if (abs(player_position.y - current_postion.y) < ptr_player->get_size().y/2.0f)
    {
        return true;
    }
    return false;
}
bool ball::is_on_ceiling_or_floor(){
    Vector2 player_position = ptr_player->get_position();
    Vector2 current_postion = position;
    if (abs(HEIGHT - current_postion.y) < size)
    {
        return true;
    }
    else if (abs(0 - current_postion.y)<size)
        return true;
    return false;
}
Vector2 ball::check_collision(){

    Vector2 collision_vector = velocity;
    if(is_colliding(ptr_player) || is_colliding(ptr_ai)){
        collision_vector.x = -collision_vector.x; 
        sound_manager::get_sound_manager_instance()->play_sound(soundfx::BLIP1);
    }
    if(is_on_ceiling_or_floor()){
        collision_vector.y = -collision_vector.y;
        sound_manager::get_sound_manager_instance()->play_sound(soundfx::BLIP1);
}
    return collision_vector;
}
void ball::draw(){
    DrawCircleV(position, size, RED); 
}
