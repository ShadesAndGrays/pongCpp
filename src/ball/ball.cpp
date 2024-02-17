#include "ball.hpp"
#include "player.hpp"
#include <cstddef>
#include <fmt/core.h>
#include <raylib.h>

extern player * ptr_player; 
ball::ball() : speed(200.0) ,size(10.0f),position({0,0}), velocity(Vector2{-50,0}){

    
}
void ball::process(float delta){
    
    move(delta);
    
}
void ball::set_positon(Vector2 pos){
    position = pos;

}
void ball::move(float delta){
    if(is_colliding()){
        fmt::println("Collidin");
        velocity = check_collision();
    }
    position.x += velocity.x *delta; 
    position.y += velocity.y * delta; 
}
bool ball::is_colliding(){

    
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
Vector2 ball::check_collision(){

    Vector2 collision_vector = velocity;
    collision_vector.x = -collision_vector.x; 
    return collision_vector;
}
void ball::draw(){
    DrawCircleV(position, size, RED); 
}
