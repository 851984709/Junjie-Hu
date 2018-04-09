#include<stdio.h>
#include<SDL2/SDL.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL",
                                         SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                         200,200,
                                         SDL_WINDOW_SHOWN);
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    int i,k;
    SDL_Surface *image;
    for(i=0;i<10;i++)
    {
    int key1,key2;
    while(key1 = _getch())
    {
        if(key1 == 27)//ESC½¨ÍË³ö
            break;
        key2 =_getch();
        if(key1 = 224)
        {
            switch(key2)
            {
            case 72:
                image = SDL_LoadBMP("up.bmp");
                printf("上");
                break;
            case 75:
                image = SDL_LoadBMP("down.bmp");
                printf("下");
                break;
            case 77:
                image = SDL_LoadBMP("left.bmp");
                printf("左");
                break;
            case 80:
                image = SDL_LoadBMP("right.bmp");
                printf("右");
                break;
            }
        }
    }
            SDL_BlitSurface(image,NULL,surface,NULL);
            SDL_UpdateWindowSurface(window);
            SDL_Delay(200);
    }
    SDL_Delay(1000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
