#pragma once
#include "ball.hpp"
#include "player.hpp"

class ai: public player{
    public:

    ai(ball bl);
    void process();

};

