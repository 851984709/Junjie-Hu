#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL",
                                         SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                         800,800,
                                         SDL_WINDOW_SHOWN);
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_Rect rect;
    rect.x=300;
    rect.y=300;

    SDL_Surface *image = SDL_LoadBMP("1.bmp");
    SDL_Surface *leftorright;

    SDL_Event event;
    bool quit=false;
    while(quit==false)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT) quit=true;

            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    leftorright=SDL_LoadBMP("left.bmp");
                }
                else if (event.button.button==SDL_BUTTON_RIGHT)
                {
                    leftorright=SDL_LoadBMP("right.bmp");
                }
                SDL_BlitSurface(leftorright,NULL,surface,&rect);
                SDL_UpdateWindowSurface(window);
            }

            else if(event.type==SDL_KEYDOWN)
            {
                if(event.key.keysym.sym==SDLK_UP)
                    rect.y-=50;
                else if(event.key.keysym.sym==SDLK_DOWN)
                    rect.y+=50;
                else if(event.key.keysym.sym==SDLK_LEFT)
                    rect.x-=50;
                else if(event.key.keysym.sym==SDLK_RIGHT)
                    rect.x+=50;
                    SDL_FillRect(surface,NULL,0);
                SDL_BlitSurface(leftorright,NULL,surface,&rect);
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
