#pragma once

#include "player.hpp"
#include <raylib.h>

class ball{
    protected:
        float speed;
        Vector2 position; 
        float size;

        void move(float delta);
    public:
        Vector2 velocity;

        ball();
        Vector2 get_position();
        void set_positon(Vector2 pos);
        void process(float delta);
        bool is_colliding(player * ptr_player);
        bool is_on_ceiling_or_floor();
        Vector2 check_collision();
        void draw();

};
