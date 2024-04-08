#include "ai.hpp"
#include "player.hpp"
#include "ball.hpp"
#include <cmath>
#include <fmt/core.h>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include "constants.hpp"
#include "score.hpp"
#include "sound_manager.hpp"

player *ptr_player = nullptr;
ball *ptr_ball = nullptr;
ai * ptr_ai = nullptr;
Score player_score;
Score ai_score;
Font font;

Rectangle calculateScale(RenderTexture2D texture);

void ready(){
    sound_manager::get_sound_manager_instance();
    ptr_player = new player; 
    ptr_ball = new ball;
    ptr_ai = new ai(ptr_ball); 
    ptr_ball->set_positon(Vector2{WIDTH/2.0f,HEIGHT/2.0f});

}
void process(float delta){

    if (ptr_ball != nullptr)
        ptr_ball->process(delta);
    if(ptr_player != nullptr)
        ptr_player->process(delta);
    if (ptr_ai != nullptr)
        ptr_ai->process(delta);
}

float check_score(){
    float score = player_score.getScore() - ai_score.getScore();
    score/=52.0f;
    score = Clamp(score, -1.0, 1.0);
    return score;

}
void draw(){


    if(ptr_ball != nullptr)
        ptr_ball->draw();
    if (ptr_player != nullptr)
        ptr_player->draw();
    if (ptr_ai!= nullptr)
        ptr_ai->draw();
}
void cleanup(){
    if (ptr_player){
        delete ptr_player;
        ptr_player = nullptr;
    }
    if (ptr_ball){
        delete ptr_ball;
        ptr_ball = nullptr;
    }
    if (ptr_ai){
        delete ptr_ai;
        ptr_ai = nullptr;
    }
}

void reset(){
    cleanup();
    ready();
    player_score.setScore(0);
    ai_score.setScore(0);
    fmt::println("reseting");
}
int main(){
    InitWindow(WIDTH,HEIGHT,"Pong");
    font = LoadFont("font/SpaceMono-Regular.ttf");
    SetTextureFilter(font.texture,TEXTURE_FILTER_BILINEAR);
    float prev_time =0;
    Camera2D camera = Camera2D{0};
    camera.target= (Vector2){ WIDTH / 2.0f, HEIGHT / 2.0f };
    camera.offset = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    SetTargetFPS(60);
    int level = 30;
    bool game_over = false;

    float scale = std::min((float)GetScreenWidth()/WIDTH, (float)GetScreenHeight()/HEIGHT);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    RenderTexture screen = LoadRenderTexture(WIDTH,HEIGHT);
    SetTextureFilter(screen.texture, TEXTURE_FILTER_BILINEAR); 
    RenderTexture scoreScreen = LoadRenderTexture(WIDTH, HEIGHT * 0.1f);
    SetTextureFilter(scoreScreen.texture, TEXTURE_FILTER_POINT); 
    RenderTexture gameOverScreen = LoadRenderTexture(WIDTH,HEIGHT);

    ready();

    while (!WindowShouldClose())
    {

        auto  rect_bg = calculateScale(screen); 
        auto scorebg = rect_bg; 

        if (abs(check_score()) == 1) {
            if (!game_over){
                game_over = true;
                if (check_score() == 1){
                    sound_manager::get_sound_manager_instance()->play_sound(soundfx::GOOD_END);
                }
                else if (check_score() == -1){
                    sound_manager::get_sound_manager_instance()->play_sound(soundfx::BAD_END);
                }
                cleanup();
            }else{
                if(IsKeyPressed(KEY_SPACE)){
                    reset();
                    game_over = false;
                    continue;
                }

            }
        }

        process(GetTime() - prev_time);
        prev_time = GetTime();


        if(IsKeyPressed(KEY_R))
        {
            reset();
            game_over = false;
        }
        if (!game_over){


            if (ptr_ball->out_of_bounds() != OUT::NONE){

                ptr_ball->set_positon(Vector2{WIDTH/2.0f,HEIGHT/2.0f});
                ptr_ball->randomizeVelocity();
                ptr_ball->set_speed(ptr_ball->get_speed() + level/3.0f);
                sound_manager::get_sound_manager_instance()->play_sound(soundfx::GOAL);
                switch (ptr_ball->out_of_bounds()) {
                    case LEFT:
                        ai_score.increment();
                        ptr_player->set_move_speed(ptr_player->get_move_speed() + level/6.0f);
                        break;
                    case RIGHT:
                        player_score.increment();
                        ptr_ai->set_move_speed(ptr_ai->get_move_speed() + level/2.0f); 
                        ptr_ball->set_speed(ptr_ball->get_speed() + level/2.5f);
                        break;
                    default:
                        break;
                }
                if (level > 6){
                    level-=0.5;
                }


            }

            if (IsKeyDown(KEY_A)){
                player_score.increment();
            }
            else if(IsKeyDown(KEY_D)){
                ai_score.increment();
            }

            rect_bg.width += 2;
            rect_bg.height += 2;
            rect_bg.x -=1;
            rect_bg.y -=1;

            scorebg.y = 2;
            scorebg.height = scoreScreen.texture.height; 
        }




        BeginTextureMode(screen);
        ClearBackground(BLACK);
        draw();
        EndTextureMode();

        BeginTextureMode(scoreScreen);
        ClearBackground(BLACK);
        std::string score_text = std::to_string(player_score.getScore()) +" : "+ std::to_string(ai_score.getScore());
        DrawTextEx(font, score_text.c_str(), Vector2{ WIDTH * 0.45, HEIGHT * 0.01}, 32, 0,Color{255,255,255,140});

        DrawRectangleV(Vector2{WIDTH * 0.1, HEIGHT * 0.07},Vector2{WIDTH * 0.8f, HEIGHT * 0.01f}, Color{230,100,105,255});
        DrawRectangleV(Vector2{WIDTH * 0.1, HEIGHT * 0.07},Vector2{WIDTH * 0.4f + (WIDTH * 0.4f) * check_score(),HEIGHT * 0.01f}, Color{100,215,220,255});

        EndTextureMode();

        BeginTextureMode(gameOverScreen);
        ClearBackground(BLACK);
        if (check_score() > 0)
            DrawText("You won!! >:)", WIDTH * 0.25, HEIGHT * 0.4, 40, YELLOW);
        else{
            DrawText("You LOST >:(", WIDTH * 0.25, HEIGHT * 0.4, 40, RED);
        };
        DrawText("Press space to Play Again!!!", WIDTH * 0.2,HEIGHT * 0.5, 40, WHITE);
        EndTextureMode();

        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(BLACK);
        if (!game_over){

            DrawRectangleRec(rect_bg, WHITE);

            DrawRectangleV({scorebg.x - 1 ,scorebg.y - 1},{scorebg.width +2, scorebg.height +2},WHITE);

            DrawTexturePro(
                    screen.texture,
                    (Rectangle){ 0.0f, 0.0f, (float)screen.texture.width, (float)-screen.texture.height },
                    calculateScale(screen), (Vector2){ 0, 0 }, 0.0f, WHITE);   

            DrawTexturePro(
                    scoreScreen.texture, 
                    (Rectangle){ 0.0f, 0.0f, (float)scoreScreen.texture.width, (float)-scoreScreen.texture.height },
                    scorebg, {0}, 0,WHITE);
        }
        else{
            DrawTexturePro(gameOverScreen.texture,
                    Rectangle{0,0,(float)gameOverScreen.texture.width,-(float)gameOverScreen.texture.height},
                    calculateScale(gameOverScreen),
                    {0},0,WHITE);
        }

        EndMode2D();
        EndDrawing();
    }
    cleanup();
}

Rectangle calculateScale(RenderTexture2D texture){
    float unit;
    float screen;
    float scaleFactor;
    if (GetScreenWidth() <  GetScreenHeight()){

        unit = texture.texture.width;
        screen = GetScreenWidth();
    }
    else {
        unit = texture.texture.width;
        screen = GetScreenHeight();
    }
    scaleFactor = screen/unit;
    float x = GetScreenWidth()/2.0 - texture.texture.width/2.0 * scaleFactor ;
    float y = GetScreenHeight()/2.0 - texture.texture.height/2.0 * scaleFactor;
    return Rectangle{x,y,texture.texture.width * scaleFactor, texture.texture.height * scaleFactor};
}
