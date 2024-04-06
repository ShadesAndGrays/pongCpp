#include "ai.hpp"
#include "player.hpp"
#include "ball.hpp"
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
void draw(){
    
    std::string score_text = std::to_string(player_score.getScore()) +" : "+ std::to_string(ai_score.getScore());
    DrawTextEx(font, score_text.c_str(), Vector2{ WIDTH * 0.47, HEIGHT * 0.1}, 32, 0,Color{255,255,255,100});
    if (ptr_player != nullptr)
        ptr_player->draw();
    if(ptr_ball != nullptr)
        ptr_ball->draw();
    if (ptr_ai!= nullptr)
        ptr_ai->draw();
}
void cleanup(){
    delete ptr_player;
    delete ptr_ball;
    delete ptr_ai;
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

float scale = std::min((float)GetScreenWidth()/WIDTH, (float)GetScreenHeight()/HEIGHT);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    RenderTexture screen = LoadRenderTexture(WIDTH,HEIGHT);
    SetTextureFilter(screen.texture, TEXTURE_FILTER_BILINEAR); 
    ready();
    
    while (!WindowShouldClose())
    {
        process(GetTime() - prev_time);
        prev_time = GetTime();
        
        
        if(IsKeyPressed(KEY_SPACE))
        {
            cleanup();
            ready();
            player_score.setScore(0);
            ai_score.setScore(0);
            fmt::println("reseting");

        }
        if (ptr_ball->out_of_bounds() != OUT::NONE){

            ptr_ball->set_positon(Vector2{WIDTH/2.0f,HEIGHT/2.0f});
            ptr_ball->randomizeVelocity();
            switch (ptr_ball->out_of_bounds()) {
                case LEFT:
                    player_score.increment();
                    break;
                case RIGHT:
                    ai_score.increment();
                    break;
                default:
                    break;


            }

        }


        auto rect_bg = calculateScale(screen); 
        rect_bg.width += 2;
        rect_bg.height += 2;
        rect_bg.x -=1;
        rect_bg.y -=1;

        BeginTextureMode(screen);
        ClearBackground(BLACK);
        draw();
        EndTextureMode();

        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(BLACK);
        DrawRectangleRec(rect_bg, WHITE);
        DrawTexturePro(
                screen.texture,
                (Rectangle){ 0.0f, 0.0f, (float)screen.texture.width, (float)-screen.texture.height },
                calculateScale(screen), (Vector2){ 0, 0 }, 0.0f, WHITE);   
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
