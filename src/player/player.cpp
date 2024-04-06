#include "player.hpp"
#include <fmt/core.h>
#include <raylib.h>
#include <raymath.h>
#include "constants.hpp"

player::player(): move_speed(220.0f), size(Vector2{25,120}),position(Vector2{30,200}){
    fmt::println("{} , {} start position", this->position.x, this->position.y);
}
void player::set_position(Vector2 pos){
    this->set_position(pos);

}
Vector2 player::get_position(){
    return  this->position;

}

void player::process(float delta){
    if (IsKeyDown(KEY_W)) {
        position.y -= move_speed * delta;
    }
    else if (IsKeyDown(KEY_S)) {
        position.y += move_speed * delta;
    }

    in_bound();
}

void player::draw(){
    Rectangle rect = Rectangle{position.x - size.x/2.0f ,position.y- size.y/2.0f, size.x,size.y};
    
    DrawRectangleRec(rect, WHITE);
    // DrawCircleV(position, 2,RED);
}
bool player::in_bound(){
    if (position.y < 0 + size.y/2.0f)
    {
        position.y = 0 + size.y/2.0f;
        return false;
    }

    else if (position.y > HEIGHT - size.y/2.0f)
    {
        position.y = HEIGHT - size.y/2.0f;
        return false;
    }
    return true; 
}
Vector2 player::get_size(){
    return size;
}
