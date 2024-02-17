#include "ai.hpp"
#include "player.hpp"
#include "constants.hpp"
#include <raylib.h>
ai::ai(ball *bl): ptr_ball(bl) {
    move_speed = 70.0f;
    position = Vector2{WIDTH-30, 300};
    size = Vector2{25,120};

}

void  ai::process(float delta) {
    position.y = ptr_ball->get_position().y;
}
