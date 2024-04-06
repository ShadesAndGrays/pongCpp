#include "ball.hpp"
#include "ai.hpp"
#include "player.hpp"
#include <cmath>
#include <cstdlib>
#include <fmt/core.h>
#include <raylib.h>
#include <raymath.h>
#include "constants.hpp" 
#include "sound_manager.hpp"

extern player * ptr_player; 
extern ai * ptr_ai;
ball::ball() : 
    speed(300.0f) ,
    size(10.0f),
    position({0,0}), 
    velocity(Vector2{-1.2,0.4}),
    ball_state(OUT::NONE){

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
    velocity = Vector2Normalize(velocity);
    position.x += velocity.x * speed * delta; 
    position.y += velocity.y * speed * delta; 
}
bool ball::is_colliding(player* ptr_player){

    Vector2 player_position = ptr_player->get_position();
    Vector2 current_postion = position;
    Vector2 distance = Vector2{player_position.x - current_postion.x,player_position.y - current_postion.y};
    if (abs(distance.x + 5 * (distance.x > 0 ? 1 : -1) ) > (ptr_player->get_size().x * 0.6) )
        return false;
    if (abs(distance.y) < ptr_player->get_size().y/2.0f)
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
    else if (abs(0 - current_postion.y) < size)
        return true;
    return false;
}
Vector2 ball::check_collision(){
    if (position.x <= 0){
        ball_state =  LEFT;
    }
    else if(position.x >= WIDTH){
        ball_state = RIGHT;
    }
    else{
        ball_state =  NONE;
    }

    Vector2 collision_vector = velocity;
    if(is_colliding(ptr_player) ){
        collision_vector.x = std::fabs(collision_vector.x);
        // Calculating y offest
        float distance_from_center = ptr_player->get_position().y - position.y;
        distance_from_center = distance_from_center / position.y;
        collision_vector.y = -Clamp(distance_from_center * 2, -0.4 ,0.4);
        // Teleporting to front
        position.x = ptr_player->get_position().x + (ptr_player->get_size().x * 0.6 + size);

        sound_manager::get_sound_manager_instance()->play_sound(soundfx::BLIP1);

    }else if(is_colliding(ptr_ai)){

        float distance_from_center = ptr_ai->get_position().y - position.y;
        distance_from_center = distance_from_center / position.y;
        collision_vector.y = -Clamp(distance_from_center * 2, -0.4 ,0.4);

        collision_vector.x = std::fabs(collision_vector.x) * -1;
        position.x = ptr_ai->get_position().x - (ptr_ai->get_size().x * 0.6 + size);
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

OUT ball::out_of_bounds(){
    return ball_state;
}

void ball::randomizeVelocity(){
    velocity.x *= rand() % 10 -5 > 0 ? -1 : 1;
    velocity.y *= rand() % 10 -7 > 0 ? -1 : 1;

}
