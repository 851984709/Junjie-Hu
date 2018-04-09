#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL",
                                         SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                         200,200,
                                         SDL_WINDOW_SHOWN);

    int i;
    for(i=0;;i++)
    {
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_Surface *image = SDL_LoadBMP("1.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("11.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("21.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("31.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("41.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("51.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("61.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("71.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("81.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("91.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("91.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("101.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("111.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("121.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("131.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("141.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("151.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("161.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("171.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("181.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("191.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("201.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("211.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("221.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("231.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("241.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("251.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("261.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("271.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);

    image = SDL_LoadBMP("280.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(200);
    }
    SDL_Delay(1000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
