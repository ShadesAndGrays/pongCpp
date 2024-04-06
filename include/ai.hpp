#pragma once
#include "ball.hpp"
#include "player.hpp"


class ai: public player{
    private:
        ball* ptr_ball = nullptr;
        int randDir;
    public:
        ai(ball *bl);
        void process(float delta) override;

};

