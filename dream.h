#ifndef TIMER_H
#define TIMER_H


#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>
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

class Sound
{
public:
    Mix_Music *temp = NULL;
    int loops = 1;

    void loadMusic(char*);
    void playMusic();
};


class Texture
{
public:
    SDL_Texture *texture = NULL;
    SDL_Surface *img_surface = NULL;
    
    int width,height, swidth, sheight;
    double degrees;
    
    int flip;

    void loadFile(char*);
    SDL_Texture* returnTexture();

    int getWidth();
    int getHeight();

    void RotateTexture(double);
    void FlipTexture(int);
    void ScaleTexture(int,int);
    void AlphaTexture(Uint8);
    
    ~Texture();
};

struct Vector2
{
	int x, y, w, h;
};

struct Color
{
	Uint8 r,g,b;
};

class Font 
{
public:

    TTF_Font *font = NULL;

    void setFont();

    ~Font();
};
#endif
void printCtr();
void LoadWindow(char*, int, int);
void DrawScreen();
void CloseWindow();
void DrawLine(int, int, int, int,  int, int, int);
void DrawPixel(int, int , int , int ,int );

void DrawSurfaceQuad(int, int, int, int, Color);

bool done();
void Render(int);

void PlayAudio(char*);
void Delay(int);
void WriteStringText(string, int,int,int, Color);
void Ticks();

void LoadSprites(Texture*, int, int);
void RenderSpritesCropped(Texture*,int,int,int,int,int,int);
void RenderSprites(Texture*, int, int);
void LoadSpritesFlipped(char*,int,int,int,int,double,int);


bool Col_Check(tuple <int,int,int,int>, tuple <int,int,int,int>);


int GetMouse_X();
int GetMouse_Y();
bool isMouseClicked();
bool isMouseAClicked();

bool keyDown(int);
bool keyPressedDown(int);

bool musicPlaying();

bool ctrlDown(int, SDL_GameControllerButton);
bool joyDown(int,int);
float axisState(int,int);
