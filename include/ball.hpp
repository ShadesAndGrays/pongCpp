#pragma once

#include "player.hpp"
#include <raylib.h>

enum OUT{

    LEFT,
    RIGHT,
    NONE
};

class ball{
    protected:
        float speed;
        Vector2 position; 
        float size;

        void move(float delta);
        OUT ball_state;
    public:
        Vector2 velocity;

        ball();
        Vector2 get_position();
        void set_positon(Vector2 pos);
        void set_speed(float speed);
        float get_speed();
        void randomizeVelocity();
        void process(float delta);
        bool is_colliding(player * ptr_player);
        bool is_on_ceiling_or_floor();
        Vector2 check_collision();
        OUT out_of_bounds();
        void draw();

};
