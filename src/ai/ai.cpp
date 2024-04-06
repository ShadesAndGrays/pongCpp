#include "ai.hpp"
#include "constants.hpp"
#include <cmath>
#include <cstdlib>
#include <fmt/core.h>
#include <raylib.h>
#include <raymath.h>

ai::ai(ball *bl): ptr_ball(bl) {
    move_speed = 220.0f;
    position = Vector2{WIDTH-30, 300};
    size = Vector2{25,120};
    randDir = 0;

}

void ai::process(float delta) {
    if (abs(ptr_ball->get_position().x - position.x) <  WIDTH/4.0){
        if (abs(ptr_ball->get_position().y - position.y) > size.y/3){

        position.y = Lerp(position.y,position.y + (Clamp(ptr_ball->get_position().y - position.y,-1,1)) , delta*move_speed);
        }
        randDir = rand() % 3 - 1;
    }
    else{

        if(randDir == 0){
            randDir = rand() % 3 - 1;
        }
        else{

            position.y = Lerp(position.y,position.y + randDir , delta * move_speed * 0.7);
        }


    }
    if(!in_bound()){
        randDir = 0;
    }
}
