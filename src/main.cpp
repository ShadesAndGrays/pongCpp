#include "player.hpp"
#include "ball.hpp"
#include "pong.hpp"
#include <fmt/core.h>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include "constants.hpp"

player *ptr_player = nullptr;
ball *ptr_ball = nullptr;

void ready(){
    ptr_player = new player; 
    ptr_ball = new ball;
    ptr_ball->set_positon(Vector2{WIDTH/2.0f,HEIGHT/2.0f});
}
void process(float delta){
    if(ptr_player != nullptr)
        ptr_player->process(delta);
    if (ptr_ball != nullptr)
        ptr_ball->process(delta);
}
void draw(){
    if (ptr_player != nullptr)
        ptr_player->draw();
    if(ptr_ball != nullptr)
        ptr_ball->draw();
}
void cleanup(){
    delete ptr_player;
    delete ptr_ball;
}
int main(){
    InitWindow(WIDTH,HEIGHT,"Pong");
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
        }



        BeginTextureMode(screen);
        ClearBackground(BLACK);
        draw();
        EndTextureMode();

        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(BLACK);
        DrawTexturePro(screen.texture,(Rectangle){ 0.0f, 0.0f, (float)screen.texture.width, (float)-screen.texture.height },
                           (Rectangle){ 0,0,(float)GetScreenWidth(), (float)GetScreenHeight() }, (Vector2){ 0, 0 }, 0.0f, WHITE);   
        EndMode2D();
        EndDrawing();
    }
    cleanup();
}
