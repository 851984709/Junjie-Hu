#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
SDL_Rect rect;
SDL_Surface* imagesurface;
bool moveright=true;
bool movedown=true;

void updateposition();

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL",
                                         SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                         WINDOW_WIDTH,WINDOW_HEIGHT,
                                         SDL_WINDOW_SHOWN);

    SDL_Renderer* rend=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(rend);

    imagesurface = SDL_LoadBMP("1.bmp");
    SDL_Texture* image=SDL_CreateTextureFromSurface(rend,imagesurface);

    rect.x=0;
    rect.y=0;
    rect.w=imagesurface->w;
    rect.h=imagesurface->h;

    SDL_Event event;
    bool quit=false;

    while(quit==false)
    {
        while(SDL_PollEvent(&event))
        {
        if(event.type==SDL_QUIT) quit=true;
        }
        updateposition();
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend,image,NULL,&rect);
        SDL_Delay(5);
        SDL_RenderPresent(rend);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
void updateposition()
{
    if(moveright==true)
    {
        rect.x++;
        if(rect.x>=WINDOW_WIDTH-imagesurface->w)
            moveright=false;
    }
    else  {
        rect.x--;
        if(rect.x<=0)
            moveright=true;
    }
     if(movedown==true)
    {
        rect.y++;
        if(rect.y>=WINDOW_HEIGHT-imagesurface->h)
            movedown=false;
    }
    else  {
        rect.y--;
        if(rect.y<=0)
            movedown=true;
    }
}
