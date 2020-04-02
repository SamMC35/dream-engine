#ifndef TIMER_H
#define TIMER_H


#include<SDL2/SDL.h>
#include<string>
#include<tuple>

using namespace std;

//SDL_Window *window;
//SDL_Renderer *renderer;

class Timer
{
public:
    Uint32 startTime;
    Uint32 setTime;

    Timer();

    void init_timer();
    Uint32 get_time();
    Uint32 get_time(int a);
    void reset_time();
};

class Joystick
{
public:
    int Get_X();
    int Get_Y();
    bool butDown(int);
};


class Texture
{
public:
    SDL_Texture *texture = NULL;
    SDL_Surface *img_surface = NULL;
    int width,height;
    

    void loadFile(char*);
    SDL_Texture* returnTexture();

    int getWidth();
    int getHeight();


    ~Texture();
};
#endif
void printCtr();
void LoadWindow(char*, int, int);
void DrawScreen();
void CloseWindow();
void DrawLine(int, int, int, int,  int, int, int);
void DrawQuad(int, int, int, int, int);
void DrawSurfaceQuad(int, int, int, int, int, int, int);
void DrawCircle();
void DrawTriangle(int, int, int, int, int);
bool done();
void Render(int);
void PlayAudio(char*);
void Delay(int);
void WriteStringText(string, int,int,int);
void Ticks();
void LoadSprites(Texture*, int, int);
void LoadSpritesCropped(Texture*,int,int,int,int,int,int,int,int);
void LoadSpritesScaled(Texture*, int, int ,int ,int);
void LoadSpritesFlipped(char*,int,int,int,int,double,int);


bool Col_Check(tuple <int,int,int,int>, tuple <int,int,int,int>);


int GetMouse_X();
int GetMouse_Y();

bool keyDown(int);
bool keyPressedDown(int);
bool ctrlDown(int, SDL_GameControllerButton);
