#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

struct Enemy
{
    SDL_Rect rect;
    int life;
    int boomstage;
    int enegy;
} enemyplane[100],playerplane;
int WIDTH=800,HEIGHT=600;
int score;
int shellnumber,enemynumber,enemyshellnumber;
int maxenegy=4500,shelldamage=200,laserdamage=5,scorestage1=1500;
bool quit=false;
bool lasercreatejudge=false;

SDL_Rect planerect,shellrect[999],blackrect,enemyshellrect[999],backgroundrect,liverect,enegyrect,
         scorerect,laserrect,newgamerect,failmenurect,returnrect,regamerect,exitrect;
SDL_Event event;

SDL_Renderer* rend;
SDL_Texture* face;
SDL_Texture* faceselect;
SDL_Texture* background;
SDL_Texture* condition;
SDL_Texture* plane;
SDL_Texture* enemy;
SDL_Texture* shell;
SDL_Texture* black;
SDL_Texture* boom;
SDL_Texture* youdied;
SDL_Texture* failmenu;

void Face(SDL_Window* window);
void Photolead();
void Initialization();
void Gamefun(SDL_Window* window);
void Background();
void Shellcreate(int x,int y);
void Laserrectcreate(int x,int y);
void Shellmove();
void Enemycreate();
void Enemyboom();
void Boomshow();
void Enemyact();
void Enemyshellcreate(int i);
void Enemyshellmove();
void Attackedjudge(SDL_Window* window);
void Fail(SDL_Window* window);
void Condition();

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL",
                                          SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                          WIDTH,HEIGHT,
                                          SDL_WINDOW_SHOWN);
    rend=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    Photolead();
    Initialization();
    Face(window);
    return 0;
}
void Face(SDL_Window* window)
{
    SDL_RenderCopy(rend,face,NULL,NULL);
    SDL_RenderPresent(rend);
    SDL_Delay(1000);
    while(quit==false)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)
            {
                quit=true;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    if(event.motion.x>=newgamerect.x&&event.motion.x<=(newgamerect.x+newgamerect.w)&&event.motion.y>=newgamerect.y&&event.motion.y<=(newgamerect.y+newgamerect.h))
                    {
                        //SDL_RenderCopy(rend,faceselect,NULL,&newgamerect);
                        //SDL_RenderPresent(rend);
                        //SDL_Delay(50);
                        Gamefun(window);
                    }
                    // if(event.motion.x>=40&&event.motion.x<=200&&event.motion.y>=100&&event.motion.y<=160)
                    // if(event.motion.x>=40&&event.motion.x<=200&&event.motion.y>=100&&event.motion.y<=160)
                    else if(event.motion.x>=40&&event.motion.x<=200&&event.motion.y>=340&&event.motion.y<=370)
                        quit=true;
                }
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void Photolead()
{
    SDL_Surface* facesurface = SDL_LoadBMP("face.bmp");
    SDL_Surface* faceselectsurface = SDL_LoadBMP("faceselect.bmp");
    SDL_Surface* backgroundsurface = SDL_LoadBMP("background.bmp");
    SDL_Surface* conditionsurface = SDL_LoadBMP("condition.bmp");
    SDL_Surface* planesurface = SDL_LoadBMP("plane.bmp");
    SDL_Surface* enemysurface = SDL_LoadBMP("enemy.bmp");
    SDL_Surface* shellsurface = SDL_LoadBMP("shell.bmp");
    SDL_Surface* blacksurface = SDL_LoadBMP("black.bmp");
    SDL_Surface* boomsurface = SDL_LoadBMP("boom.bmp");
    SDL_Surface* youdiedsurface = SDL_LoadBMP("youdied.bmp");
    SDL_Surface* failmenusurface = SDL_LoadBMP("failmenu.bmp");

    SDL_SetColorKey(enemysurface,SDL_TRUE,SDL_MapRGB(enemysurface->format,19,207,88));
    SDL_SetColorKey(conditionsurface,SDL_TRUE,SDL_MapRGB(conditionsurface->format,19,207,88));
    SDL_SetColorKey(planesurface,SDL_TRUE,SDL_MapRGB(planesurface->format,19,207,88));
    SDL_SetColorKey(youdiedsurface,SDL_TRUE,SDL_MapRGB(youdiedsurface->format,19,207,88));
    SDL_SetColorKey(failmenusurface,SDL_TRUE,SDL_MapRGB(failmenusurface->format,19,207,88));
    SDL_SetColorKey(shellsurface,SDL_TRUE,SDL_MapRGB(shellsurface->format,191,175,238));
    SDL_SetColorKey(boomsurface,SDL_TRUE,SDL_MapRGB(boomsurface->format,0,0,0));

    face=SDL_CreateTextureFromSurface(rend,facesurface);
    faceselect=SDL_CreateTextureFromSurface(rend,faceselectsurface);
    background=SDL_CreateTextureFromSurface(rend,backgroundsurface);
    condition=SDL_CreateTextureFromSurface(rend,conditionsurface);
    plane=SDL_CreateTextureFromSurface(rend,planesurface);
    enemy=SDL_CreateTextureFromSurface(rend,enemysurface);
    shell=SDL_CreateTextureFromSurface(rend,shellsurface);
    black =SDL_CreateTextureFromSurface(rend,blacksurface);
    boom =SDL_CreateTextureFromSurface(rend,boomsurface);
    youdied=SDL_CreateTextureFromSurface(rend,youdiedsurface);
    failmenu=SDL_CreateTextureFromSurface(rend,failmenusurface);

    SDL_SetTextureBlendMode(faceselect,SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(black,SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(condition,SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(plane,SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(enemy,SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(boom,SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(failmenu,SDL_BLENDMODE_BLEND);

    SDL_SetTextureAlphaMod(faceselect,100);
    SDL_SetTextureAlphaMod(condition,200);
    SDL_SetTextureAlphaMod(plane,100);
    SDL_SetTextureAlphaMod(failmenu,230);
}
void Initialization()
{
    playerplane.rect.x=0;
    playerplane.rect.y=0;
    playerplane.rect.w=50;
    playerplane.rect.h=50;
    playerplane.life=300;
    playerplane.enegy=0;

    blackrect.x=0;
    blackrect.y=0;
    blackrect.w=800;
    blackrect.h=600;

    backgroundrect.h=600;
    backgroundrect.w=WIDTH;
    backgroundrect.y=1800;
    backgroundrect.x=0;

    liverect.h=20;
    liverect.w=120;
    liverect.x=15;
    liverect.y=10;

    enegyrect.h=20;
    enegyrect.w=0;
    enegyrect.x=15;
    enegyrect.y=40;

    scorerect.h=20;
    scorerect.w=0;
    scorerect.x=15;
    scorerect.y=70;

    laserrect.w=4;
    laserrect.y=0;

    newgamerect.x=40;
    newgamerect.y=100;
    newgamerect.h=60;
    newgamerect.w=160;

    failmenurect.x=200;
    failmenurect.y=0;
    failmenurect.w=400;
    failmenurect.h=600;

    returnrect.x=200;
    returnrect.y=320;
    returnrect.w=300;
    returnrect.h=80;

    regamerect.x=200;
    regamerect.y=180;
    regamerect.w=300;
    regamerect.h=80;

    exitrect.x=200;
    exitrect.y=460;
    exitrect.w=300;
    exitrect.h=80;

    shellnumber=0,enemynumber=0,enemyshellnumber=0;
    score=0;
}
void Gamefun(SDL_Window* window)
{
    int i;
    playerplane.rect.x= event.motion.x-playerplane.rect.w/2 ;
    playerplane.rect.y= event.motion.y-playerplane.rect.h/2;
    while(quit==false)
    {
        SDL_RenderClear(rend);
        Background();
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)
            {
                quit=true;
            }
            else if(event.type==SDL_MOUSEMOTION)
            {
                SDL_RenderCopy(rend,black,NULL,&playerplane.rect);
                playerplane.rect.x= event.motion.x-playerplane.rect.w/2 ;
                playerplane.rect.y= event.motion.y-playerplane.rect.h/2;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button==SDL_BUTTON_LEFT)
                    Shellcreate(event.motion.x,event.motion.y);
                else if(event.button.button==SDL_BUTTON_RIGHT)
                    lasercreatejudge=true;
            }
            else if(event.type == SDL_MOUSEBUTTONUP)
                if(event.button.button==SDL_BUTTON_RIGHT)
                    lasercreatejudge=false;
        }
        Shellmove();
        Enemycreate();
        Enemyact();
        for(i=0; i<enemynumber; i++)
            SDL_RenderCopy(rend,enemy,NULL,&enemyplane[i].rect);
        Boomshow();
        Enemyboom();
        Attackedjudge(window);
        Enemyshellmove();

        Laserrectcreate(event.motion.x,event.motion.y);

        Condition();

        SDL_RenderCopy(rend,plane,NULL,&playerplane.rect);
        SDL_RenderPresent(rend);
        SDL_Delay(5);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void Background()
{

    static int length=1200;
    if(backgroundrect.y==0)
    {
        backgroundrect.h=600;
        backgroundrect.w=WIDTH;
        backgroundrect.y=1800;
        backgroundrect.x=0;
        static int length=1200;
    }
    SDL_RenderCopy(rend,background,&backgroundrect,NULL);
    backgroundrect.y--;
}
void Shellcreate(int x,int y)
{
    shellrect[shellnumber].h=8;
    shellrect[shellnumber].w=4;
    shellrect[shellnumber].x=x-shellrect[shellnumber].w/2;
    shellrect[shellnumber].y=y-30;
    shellnumber++;
    SDL_RenderCopy(rend,shell,NULL,&shellrect[shellnumber]);
}
void Laserrectcreate(int x,int y)
{
    if(playerplane.enegy>0&&lasercreatejudge)
    {
        playerplane.enegy--;
        laserrect.x=x;
        laserrect.h=y-30;
        SDL_RenderCopy(rend,shell,NULL,&laserrect);
    }
}
void Shellmove()
{
    int i,k;
    for(i=0; i<shellnumber; i++)
    {
        shellrect[i].y-=2;
        SDL_RenderCopy(rend,shell,NULL,&shellrect[i]);
        if(shellrect[i].y>=HEIGHT)
        {
            for(k=i; k<shellnumber-1; k++)
                shellrect[k]=shellrect[k+1];
            shellnumber--;
            i--;
        }
    }
}
void Enemycreate()
{
    static int enemycreatejudge=0;
    if(enemycreatejudge%300==0)
    {
        enemyplane[enemynumber].rect.h=40;
        enemyplane[enemynumber].rect.w=40;
        enemyplane[enemynumber].rect.x=rand()%WIDTH;
        enemyplane[enemynumber].rect.y=-20;
        enemyplane[enemynumber].life=200;
        enemyplane[enemynumber].boomstage=50;
        SDL_RenderCopy(rend,enemy,NULL,&enemyplane[enemynumber].rect);
        enemynumber++;
    }
    enemycreatejudge++;
}
void Enemyboom()
{
    int i,j,k,l;
    for(j=0; j<enemynumber; j++)
    {
        for(i=0; i<shellnumber; i++)
        {
            if(shellrect[i].x>enemyplane[j].rect.x&&shellrect[i].x<(enemyplane[j].rect.x+enemyplane[j].rect.w)
                    &&shellrect[i].y>enemyplane[j].rect.y&&shellrect[i].y<(enemyplane[j].rect.y+enemyplane[j].rect.h))
            {
                for(k=i; k<shellnumber-1; k++)
                    shellrect[k]=shellrect[k+1];
                i--;
                shellnumber--;
                if(enemyplane[j].life>0)
                {
                    enemyplane[j].life-=shelldamage;
                    if(score<=scorestage1)
                        score+=10;
                    if(playerplane.enegy<=maxenegy)
                        playerplane.enegy+=50;
                }
            }
        }
        if(laserrect.x>enemyplane[j].rect.x&&laserrect.x<(enemyplane[j].rect.x+enemyplane[j].rect.w))
        {
            if(enemyplane[j].life>0&&lasercreatejudge)
            {
                enemyplane[j].life-=laserdamage;
                if(score<=scorestage1)
                    score+=1;
            }
        }
    }
}
void Boomshow()
{
    SDL_Rect boomrect;
    int i,j;
    for(i=0; i<enemynumber; i++)
    {
        if(enemyplane[i].life==0)
        {
            if(enemyplane[i].boomstage>=0)
            {
                boomrect.h=50-enemyplane[i].boomstage;
                boomrect.w=50-enemyplane[i].boomstage;
                boomrect.x=enemyplane[i].rect.x+enemyplane[i].boomstage/2;
                boomrect.y=enemyplane[i].rect.y+enemyplane[i].boomstage/2;
                SDL_SetTextureAlphaMod(boom,255-5*enemyplane[i].boomstage);
                SDL_SetTextureAlphaMod(enemyplane,5*enemyplane[i].boomstage);
                SDL_RenderCopy(rend,enemyplane,NULL,&enemyplane[i].rect);
                SDL_RenderCopy(rend,boom,NULL,&boomrect);
                enemyplane[i].boomstage--;
            }
            else
            {
                for(j=i; j<enemynumber-1; j++)
                    enemyplane[j]=enemyplane[j+1];
                enemynumber--;
            }

        }
    }
    SDL_SetTextureAlphaMod(plane,255);
}
void Enemyact()
{
    int i;
    static int actjudge=0;
    int actspeed=2;
    if(actjudge%actspeed==1)
    {
        for(i=0; i<enemynumber; i++)
        {
            if(enemyplane[i].life!=0)
            {
                Enemyshellcreate(i);
                if(enemyplane[i].rect.y<75)
                    enemyplane[i].rect.y++;
                else if(enemyplane[i].rect.x<playerplane.rect.x)
                    enemyplane[i].rect.x++;
                else if(enemyplane[i].rect.x>playerplane.rect.x)
                    enemyplane[i].rect.x--;
                else Enemyshellcreate(i);
            }
        }
    }
    actjudge++;
}
void Enemyshellcreate(int i)
{
    static int enemyshootjudge=0;
    int enemyshootspeed=50;
    if(enemyshootjudge%enemyshootspeed==0)
    {
        enemyshellrect[enemyshellnumber].h=8;
        enemyshellrect[enemyshellnumber].w=4;
        enemyshellrect[enemyshellnumber].x=enemyplane[i].rect.x+enemyplane[i].rect.w/2-2;
        enemyshellrect[enemyshellnumber].y=enemyplane[i].rect.y+enemyplane[i].rect.h+4;
        SDL_RenderCopy(rend,shell,NULL,&enemyshellrect[enemyshellnumber]);
        enemyshellnumber++;
    }
    enemyshootjudge++;
}
void Enemyshellmove()
{
    int i,k;
    for(i=0; i<enemyshellnumber; i++)
    {
        SDL_RenderCopy(rend,shell,NULL,&enemyshellrect[i]);
        enemyshellrect[i].y+=2;
        if(enemyshellrect[i].y>=HEIGHT)
        {
            for(k=i; k<enemyshellnumber-1; k++)
                enemyshellrect[k]=enemyshellrect[k+1];
            enemyshellnumber--;
            i--;
        }
    }
}
void Attackedjudge(SDL_Window* window)
{
    int i,k;
    for(i=0; i<enemyshellnumber; i++)
    {
        if(enemyshellrect[i].x>playerplane.rect.x&&enemyshellrect[i].x<(playerplane.rect.x+playerplane.rect.w)
                &&enemyshellrect[i].y>playerplane.rect.y&&enemyshellrect[i].y<(playerplane.rect.y+playerplane.rect.h))
        {
            if(playerplane.life==0) Fail(window);
            else
            {
                playerplane.life--;
                for(k=i; k<enemyshellnumber-1; k++)
                {
                    enemyshellrect[k]=enemyshellrect[k+1];
                    i--;
                    enemyshellnumber--;
                }
            }
        }
    }
}
void Fail(SDL_Window* window)
{
    SDL_Rect youdiedrect;
    youdiedrect.w=200;
    youdiedrect.h=100;
    youdiedrect.x=(800-200)/2;
    youdiedrect.y=(600-100)/2;
    SDL_RenderCopy(rend,failmenu,NULL,&failmenurect);
    SDL_RenderPresent(rend);
    while(quit==false)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)
            {
                quit=true;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    if(event.motion.x>=regamerect.x&&event.motion.x<=(regamerect.x+regamerect.w)&&event.motion.y>=regamerect.y&&event.motion.y<=(regamerect.y+regamerect.h))
                    {
                        Initialization();
                        Gamefun(window);
                    }
                    else if(event.motion.x>=returnrect.x&&event.motion.x<=(returnrect.x+returnrect.w)&&event.motion.y>=returnrect.y&&event.motion.y<=(returnrect.y+returnrect.h))
                     {
                         Initialization();
                         Face(window);
                     }
                     if(event.motion.x>=exitrect.x&&event.motion.x<=(exitrect.x+exitrect.w)&&event.motion.y>=exitrect.y&&event.motion.y<=(exitrect.y+exitrect.h))
                    {
                         quit=true;
                         break;
                    }
                }
            }
        }
    }
}
void Condition()
{
    liverect.w=playerplane.life/2;
    enegyrect.w=playerplane.enegy/30;
    scorerect.w=score/10;

    SDL_SetTextureColorMod(condition,28,235,102);
    SDL_RenderCopy(rend,condition,NULL,&liverect);
    SDL_SetTextureColorMod(condition,235,218,28);
    SDL_RenderCopy(rend,condition,NULL,&enegyrect);
    SDL_SetTextureColorMod(condition,62,28,235);
    SDL_RenderCopy(rend,condition,NULL,&scorerect);
}
