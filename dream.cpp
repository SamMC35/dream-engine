#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<tuple>
#include<map>
#include<string>
#include<sstream>

#include "dream.h"

using namespace std;

//This is my SDL tool which I use to use to make SDL programming easier
//Jan 20, 2019 Made lots of graphical fucntions


SDL_Window *window = NULL;
SDL_Renderer *renderer=  NULL;
SDL_Surface *surface = NULL;
SDL_Texture *texture =  NULL;
SDL_GameController  *game_controller[2];
SDL_Event  event;
SDL_Event event_joy;

Mix_Chunk *audio;

const Uint8* inkeys =  SDL_GetKeyboardState(NULL);
//Uint8 inctrl = SDL_GameControllerGetButton(NULL, NULL);
const int FPS = 60;
const int TPS = 1000/FPS;
const int JOYSTICK_DEAD_ZONE = 8000;

float avgFPS;
int countedFrames = 0;

TTF_Font *font = NULL;

int color[1][3]=
{
    {255,255,255}
};

int timer = 0;

int mouse_pos_x,mouse_pos_y;

std::map<int, bool> keypressed;



Timer::Timer()
{
    startTime = SDL_GetTicks();
}

Uint32 Timer::get_time()
{
    return (SDL_GetTicks() - startTime);
}

Uint32 Timer::get_time(int a)
{
    return (SDL_GetTicks() - setTime);
}

void Timer::reset_time()
{
    startTime = SDL_GetTicks();
}


class LTimer
{
public:

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 StartTicks, PausedTicks;
    Uint32 getTicks();

    bool started;
    bool paused;

    LTimer()
    {


        StartTicks = 0;
        PausedTicks = 0;

        started = false;
        paused = false;
    }
};

void LTimer::start()
{
    started = true;
    paused = false;
    StartTicks = SDL_GetTicks();
    PausedTicks = 0;
}

Uint32 LTimer::getTicks()
{
    Uint32 time = 0;

    time = SDL_GetTicks() - StartTicks;
    return time;
}

LTimer capTimer, fpsTimer;


//Texture class functions



Texture::~Texture()
{
    SDL_DestroyTexture(texture);
}
void Texture::loadFile(char *path)
{
    cout << path <<endl;
    img_surface = SDL_LoadBMP(path);
    cout << img_surface <<endl;
    if(img_surface == NULL)
        img_surface = SDL_LoadBMP("engine/exp.bmp");
    cout << "Lill" <<endl;

    //SDL_SetColorKey(img_surface, SDL_TRUE, SDL_MapRGB(img_surface->format, 0, 0, 0 ) );
    cout << "Lill" <<endl;
    texture = SDL_CreateTextureFromSurface(renderer, img_surface);
    cout << "Lill" <<endl;
    width = img_surface->w;
    height = img_surface->h;

    swidth = width;
    sheight = height;

    degrees = 0;
    flip = 0;

    SDL_FreeSurface(img_surface);
    cout << "Lill" <<endl;
}

SDL_Texture* Texture::returnTexture()
{
    return texture;
}

int Texture::getWidth()
{
    return width;
}

int Texture::getHeight()
{
    return height;
}

void Texture::RotateTexture(double degrees)
{
    this->degrees = degrees;
}

void Texture::FlipTexture(int flip)
{
    this->flip = flip;
}

void Texture::ScaleTexture(int swidth, int sheight)
{
    if(swidth == 0)
        this->swidth = width;
    else
        this->swidth = swidth;

     if(sheight == 0)
        this->sheight = height;
    else
        this->sheight = sheight;
}

void LoadWindow(char* name, int SCREEN_WIDTH, int SCREEN_HEIGHT)		//Initializes SDL
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);

    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "0" ) )
    {
        printf( "WarningUint8*: Linear texture filtering not enabled!" );
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //cout << "SDL_NumJoysticks:" << SDL_NumJoysticks() <<endl;
    for(int i = 0; i < SDL_NumJoysticks(); i++)
    {
        if(SDL_IsGameController(i))
        {
            game_controller[i] = SDL_GameControllerOpen(i);
        }
    }

    if(SDL_INIT_EVERYTHING < 0 || window == NULL ||  renderer == NULL)
    {
        cout<<"Fckup in LoadWindow()";
    }




    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    LTimer fpsTimer;
    fpsTimer.start();

}

/*void printCtr()
{
    system("clear");
    cout << SDL_GameControllerMapping(game_controller)<<endl;
}*/

void DrawScreen()		//Draws the screen
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

}

void DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b)
{
    SDL_SetRenderDrawColor(renderer, r, g,
    b, SDL_ALPHA_OPAQUE);

    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    //SDL_RenderPresent(renderer);
}

void DrawSurfaceQuad(int x, int y, int length, int breadth, int r, int g, int b)
{
    SDL_SetRenderDrawColor(renderer, r, g,
    b, SDL_ALPHA_OPAQUE);


    SDL_Rect rect;		//Creates a SDL_Rectangle

    rect.x = x;			//Defining its dimensions
    rect.y = y;
    rect.w = length;
    rect.h = breadth;


    //Uint32 white = SDL_MapRGB(surface->format, color[color_id][0], color[color_id][1], color[color_id][2])

    //SDL_FillRect(surface, &rect, white);
    //texture = SDL_CreateTextureFromSurface(texture, surface);
    SDL_RenderFillRect(renderer, &rect);
}

void DrawQuad(int x, int y, int length,int breadth, int color_id)
{
    SDL_SetRenderDrawColor(renderer, color[color_id][0], color[color_id][1],
    color[color_id][2], SDL_ALPHA_OPAQUE);

    SDL_RenderDrawLine(renderer, x, y, x, y+breadth);
    SDL_RenderDrawLine(renderer, x,y+breadth, x+length, y+breadth);
    SDL_RenderDrawLine(renderer, x+length, y+breadth, x+length, y);
    SDL_RenderDrawLine(renderer, x+length, y, x, y);

   // SDL_RenderPresent(renderer);
}



void DrawTriangle(int x, int y, int length, int height, int color_id)
{
    SDL_SetRenderDrawColor(renderer, color[color_id][0],
    color[color_id][1],color[color_id][2], SDL_ALPHA_OPAQUE);

    SDL_RenderDrawLine(renderer, x, y, x+length, y);
    SDL_RenderDrawLine(renderer, x, y, x+length/2, y+height);
    SDL_RenderDrawLine(renderer, x+length, y, x+length/2, y+height);
}


bool done()		//Checks if the quit is pressed
{
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
        return true;
    else if(keyDown(SDL_SCANCODE_E))
        return true;
    else
        return false;
}

bool PointInRect(int x, int y, tuple <int,int,int,int> r1)
{
    if(x >= get<0>(r1) && x <= get<0>(r1)+get<2>(r1) && y >= get<1>(r1) && y <= get<1>(r1)+get<3>(r1))
        return true;
    else
        return false;
}

bool Col_Check(tuple <int,int,int,int> r1, tuple <int,int,int,int> r2)
{
    if(PointInRect(get<0>(r1), get<1>(r1), r2) || PointInRect(get<0>(r1)+get<2>(r1), get<1>(r1), r2) ||PointInRect(get<0>(r1), get<1>(r1) + get<3>(r1), r2) || PointInRect(get<0>(r1)+get<2>(r1), get<1>(r1)+get<3>(r1), r2))
        return true;
    else
        return false;
}

void Render(int fps)		//Renders the current stack
{
    capTimer.start();
    int Scr_fps = 1000/fps;
    float avgFPS = countedFrames/(fpsTimer.getTicks()/ 1000.f);

    //SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);
    SDL_RenderPresent(renderer);
    ++countedFrames;
    int frameTicks = capTimer.getTicks();

	cout << avgFPS <<endl;

    if(frameTicks <= Scr_fps)
    {
      //cout<<Scr_fps-frameTicks<<endl;
      SDL_Delay(Scr_fps - frameTicks);
    }

  //SDL_Delay(1000/fps);
//   cout<<"fuck";
}

void CloseWindow()	//Closes the window
{
    //TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    //SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);

    //SDL_DestroySurface(surface);
    TTF_Quit();
    SDL_Quit();
}

void PlayAudio(char* path)	//Audio player
{
    audio = Mix_LoadWAV(path);
    Mix_PlayChannel(-1, audio, 0);
    //Mix_FreeChunk(audio);
}


bool keyDown(int key)  //Input methods
{
    return (inkeys[key] != 0);
}

bool keyPressedDown(int key) //this checks if the key is *just* pressed, returns true only once until the key is up again
{
  if(keypressed.find(key) == keypressed.end()) keypressed[key] = false;
  if(inkeys[key])
  {
    if(keypressed[key] == false)
    {
      keypressed[key] = true;
      return true;
    }
  }
  else keypressed[key] = false;

  return false;
}

bool ctrlDown(int i, SDL_GameControllerButton ctrl)
{
    return (SDL_GameControllerGetButton(game_controller[i], ctrl));
}

void WriteStringText(string text, int size, int x, int y)
{
    int texW = 0;
    int texH = 0;

    font  =  TTF_OpenFont("8bit.ttf", size);

    SDL_Color color = {255,255,255}; //white color

    surface = TTF_RenderText_Solid(font, text.c_str(), color);

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

    SDL_Rect textrect = {x, y, texW, texH};

    SDL_RenderCopy(renderer, texture, NULL, &textrect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

void Ticks()
{
    float ticks2 = SDL_GetTicks()/1000.f;

    stringstream time1;

    time1.str("");

    time1 << "The time is: " << SDL_GetTicks();

    WriteStringText(time1.str().c_str(), 14, 40, 60);
}

void LoadImage(char* text, int x, int y,  int w, int h) //Image Loader
{

}

void Delay(int seconds)
{
    SDL_Delay(seconds * 1000);
}

int GetMouse_X()
{
    return mouse_pos_x;
}

int GetMouse_Y()
{
    return mouse_pos_y;
}

void LoadSprites(Texture *tex, int x, int y)
{
    //Load Sprite

    texture = tex->returnTexture();

    SDL_Rect sprite = {x,y,tex->getWidth(),tex->getHeight()};

    SDL_RenderCopy(renderer, texture, NULL, &sprite);
    //Render the sprite
}

void RenderSprites(Texture *tex, int x, int y)
{
    //Load Sprite

    texture = tex->returnTexture();

    SDL_Rect sprite = {x, y, tex->swidth, tex->sheight};

    SDL_RenderCopy(renderer, texture, NULL, &sprite);
    //Render the sprite

}

void RenderSpritesCropped(Texture *tex, int x ,int y,int stx,int sty,int swd,int sht)
{

    SDL_RendererFlip flip = SDL_FLIP_NONE;

    switch(tex->flip)
    {
        case 0:
            flip = SDL_FLIP_NONE;
            break;

        case 1:
            flip = SDL_FLIP_HORIZONTAL;
            break;

        case 2:
            flip = SDL_FLIP_VERTICAL;
            break;

        default:
            break;
    }

	texture = tex->returnTexture();

    if(swd == 0)
        swd = tex->swidth;
    if(sht == 0)
        sht = tex->sheight;

    SDL_Rect sprite = {x, y, tex->swidth, tex->sheight};

    SDL_Rect clip = {stx,sty,swd,sht};

    SDL_RenderCopyEx(renderer, texture, &clip, &sprite,tex->degrees,NULL,flip);
    //Render the sprite

}

void LoadSpritesFlipped(char* path, int x, int y, int wd, int ht,double degrees, int flip_val)
{
   /*



    SDL_SetColorKey(img_surface, SDL_TRUE, SDL_MapRGB(img_surface->format, 0, 0, 0 ) );

    texture = SDL_CreateTextureFromSurface(renderer, img_surface);

    SDL_Rect sprite = {x, y, wd, ht};

    SDL_FreeSurface(img_surface);

    SDL_RenderCopyEx(renderer, texture, NULL, &sprite,degrees,NULL,flip);
    //Render the sprite
    SDL_DestroyTexture(texture);*/
}
