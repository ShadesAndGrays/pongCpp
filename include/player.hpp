#pragma once
#include <raylib.h>
#include <raymath.h>
class player{

    protected: 
        Vector2 position ; 
        Vector2 size ; 
        float move_speed;
    public:
        player();
        Vector2 get_size();
        bool in_bound();
        void set_position(Vector2 pos);
        Vector2 get_position();
        virtual void process(float delta);
        void draw();
};
