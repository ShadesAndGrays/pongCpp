#include "score.hpp"
int Score::getScore(){return this->score; }
void Score::setScore(int score){ this->score = score;}
void Score::resetScore(){ this->score = 0;}
void Score::increment(){this->score++;}
