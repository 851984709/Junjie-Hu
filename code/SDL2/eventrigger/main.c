#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL",
                                         SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                         800,600,
                                         SDL_WINDOW_SHOWN);
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_Rect rect;

    SDL_Surface *image = SDL_LoadBMP("1.bmp");

    SDL_Event event;
    bool quit=false;

    while(quit==false)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)
            {
                quit=true;
            }
            else if(event.type==SDL_MOUSEMOTION)
            {

                rect.x= event.motion.x-image->w/2 ;
                rect.y= event.motion.y-image->h/2;
                SDL_FillRect(surface,NULL,0);
                SDL_BlitSurface(image,NULL,surface,&rect);
                SDL_UpdateWindowSurface(window);
            }
        }
    }

    SDL_Delay(1000);
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
