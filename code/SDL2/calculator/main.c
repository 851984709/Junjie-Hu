#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>

int i,j,k,mark=20,m=0,n,l,resultlength;
int h=50,w=50;
int result1;
int order[999];
int number1screen[20],number2screen[20],resultscreen[20];
int number1=0,number2=0,result;
SDL_Rect screen[3][20],key[5][4],keypicture[15];
SDL_Event event;
bool quit=false,quit1=false;
SDL_Surface *image;
SDL_Surface *surface;

void Fun(SDL_Window* window);
void Initialization(SDL_Window* window);//赋初值
void Number1(SDL_Window* window);
void Number2(SDL_Window* window);
void Numbersynthesis();
void Operation(SDL_Window* window);
void Repeat(SDL_Window* window);
int main(int argc, char *argv[])
{

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL",
                                          SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                          220,340,
                                          SDL_WINDOW_SHOWN);

    surface= SDL_GetWindowSurface(window);
    SDL_UpdateWindowSurface(window);
    image = SDL_LoadBMP("calculator.bmp");
    SDL_BlitSurface(image,NULL,surface,NULL);
    SDL_UpdateWindowSurface(window);

    Fun(window);


    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
void Fun(SDL_Window* window)
{
    while(quit1==false)
    {
    Initialization(window);
    Number1(window);
    Number2(window);
    Operation(window);
    Repeat(window);
    }
}
void Initialization(SDL_Window* window)
{
    m=0;
    number1=0,number2=0;
    quit=false,quit1=false;
    for(i=0; i<3; i++)//显示屏位置赋值
    {
        for(j=0;j<20;j++)
        {
        screen[i][j].h=25;
        screen[i][j].w=10;
        screen[i][j].x=10+j*10;//x×î´óÎª220
        screen[i][j].y=10+i*20;
        }
    }

    for(i=0; i<20; i++)//显示屏赋初值
        number1screen[i]=number2screen[i]=resultscreen[i]=15;

    for(i=0; i<5; i++)//键盘位置赋值
    {
        for(j=0; j<4; j++)
        {
            key[i][j].h=50;
            key[i][j].w=50;
            key[i][j].x=10+j*50;
            key[i][j].y=70+i*50;
        }
    }
    for(i=0; i<16; i++)//键盘位置赋值
    {
        keypicture[i].h=20;
        keypicture[i].w=10;
    }
    for(i=0;i<10;i++)
    {
        keypicture[i].x=i*10;
        keypicture[i].y=340;
        }
    for(i=10;i<16;i++)
        keypicture[i].y=365;
    keypicture[10].x=0;
    keypicture[11].x=10;
    keypicture[12].x=20;
    keypicture[13].x=30;
    keypicture[14].x=40;
    keypicture[15].x=10;
    keypicture[15].y=10;


    for(k=0; k<20; k++)
    {
        SDL_BlitSurface(image,&keypicture[number1screen[k]],surface,&screen[0][k]);
        SDL_BlitSurface(image,&keypicture[number1screen[k]],surface,&screen[1][k]);
        SDL_BlitSurface(image,&keypicture[number1screen[k]],surface,&screen[2][k]);
    }
    SDL_UpdateWindowSurface(window);
}
void Number1(SDL_Window* window)
{
    while(quit==false)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT||number1screen[19]==11||number1screen[19]==12||number1screen[19]==13||number1screen[19]==14)
            {
                n=m;
                quit=true;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    for(i=0; i<5; i++)
                    {
                        for(j=0; j<4; j++)
                        {
                            if(event.motion.x>key[i][j].x&&event.motion.x<key[i][j].x+30&&event.motion.y>key[i][j].y&&event.motion.y<key[i][j].y+50)
                            {
                                switch(i*4+j)//0 1 2 3 4 5 6 7 8 9 . + - * / →（左） → DEL AC =
                                {
                                case 4:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    }
                                    number1screen[19]=order[m]=7;
                                    break;
                                case 5:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    }
                                    number1screen[19]=order[m]=8;
                                    break;
                                case 6:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    }
                                    number1screen[19]=order[m]=9;
                                    break;
                                case 8:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    };
                                    number1screen[19]=order[m]=4;
                                    break;
                                case 9:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    }
                                    number1screen[19]=order[m]=5;
                                    break;
                                case 10:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    }
                                    number1screen[19]=order[m]=6;
                                    break;
                                case 12:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    }
                                    number1screen[19]=order[m]=1;
                                    break;
                                case 13:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    }
                                    number1screen[19]=order[m]=2;
                                    break;
                                case 14:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    }
                                    number1screen[19]=order[m]=3;
                                    break;
                                case 16:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    }
                                    number1screen[19]=order[m]=0;
                                    break;


                                case 7:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    }
                                    number1screen[19]=order[m]=13;
                                    break;
                                case 11:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    }
                                    number1screen[19]=order[m]=14;
                                    break;
                                case 15:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    }
                                    number1screen[19]=order[m]=11;
                                    break;

                                case 19:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    }
                                    number1screen[19]=order[m]=12;
                                    break;

                                case 17:
                                    for(l=0; l<19; l++)
                                    {
                                        number1screen[l]=number1screen[l+1];
                                    }
                                    number1screen[19]=order[m]=10;
                                    break;

                                case 0:
                                    order[m]=15;
                                    break;
                                case 1:
                                    order[m]=16;
                                    break;
                                case 2:Fun(window);
                                    order[m]=17;
                                    break;
                                case 3:
                                    order[m]=18;
                                    break;
                                }
                                m++;
                                for(k=0; k<20; k++)
                                    SDL_BlitSurface(image,&keypicture[number1screen[k]],surface,&screen[0][k]);
                                SDL_UpdateWindowSurface(window);
                            }
                        }
                    }
                }
            }

        }
    }
}
void Number2(SDL_Window* window)
{
    quit=false;
    while(quit==false)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)//||screenmark[19]==)
            {
                quit=true;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    for(i=0; i<5; i++)
                    {
                        for(j=0; j<4; j++)
                        {
                            if(event.motion.x>key[i][j].x&&event.motion.x<key[i][j].x+30&&event.motion.y>key[i][j].y&&event.motion.y<key[i][j].y+50)
                            {
                                switch(i*4+j)//0 1 2 3 4 5 6 7 8 9 . + - * / →（左） → DEL AC =
                                {
                                case 4:
                                    for(l=0; l<19; l++)
                                    {
                                        number2screen[l]=number2screen[l+1];
                                    }
                                    number2screen[19]=order[m]=7;
                                    break;
                                case 5:
                                    for(l=0; l<19; l++)
                                    {
                                        number2screen[l]=number2screen[l+1];
                                    }
                                    number2screen[19]=order[m]=8;
                                    break;
                                case 6:
                                    for(l=0; l<19; l++)
                                    {
                                        number2screen[l]=number2screen[l+1];
                                    }
                                    number2screen[19]=order[m]=9;
                                    break;
                                case 8:
                                    for(l=0; l<19; l++)
                                    {
                                        number2screen[l]=number2screen[l+1];
                                    };
                                    number2screen[19]=order[m]=4;
                                    break;
                                case 9:
                                    for(l=0; l<19; l++)
                                    {
                                        number2screen[l]=number2screen[l+1];
                                    }
                                    number2screen[19]=order[m]=5;
                                    break;
                                case 10:
                                    for(l=0; l<19; l++)
                                    {
                                        number2screen[l]=number2screen[l+1];
                                    }
                                    number2screen[19]=order[m]=6;
                                    break;
                                case 12:
                                    for(l=0; l<19; l++)
                                    {
                                        number2screen[l]=number2screen[l+1];
                                    }
                                    number2screen[19]=order[m]=1;
                                    break;
                                case 13:
                                    for(l=0; l<19; l++)
                                    {
                                        number2screen[l]=number2screen[l+1];
                                    }
                                    number2screen[19]=order[m]=2;
                                    break;
                                case 14:
                                    for(l=0; l<19; l++)
                                    {
                                        number2screen[l]=number2screen[l+1];
                                    }
                                    number2screen[19]=order[m]=3;
                                    break;
                                case 16:
                                    for(l=0; l<19; l++)
                                    {
                                        number2screen[l]=number2screen[l+1];
                                    }
                                    number2screen[19]=order[m]=0;
                                    break;

                                case 0:
                                    order[m]=15;
                                    break;
                                case 1:
                                    order[m]=16;
                                    break;
                                case 2:
                                    order[m]=17;
                                    break;
                                case 3:
                                    order[m]=18;
                                    break;
                                case 18:
                                    quit=true;
                                    //order[m]=19;
                                    break;
                                }
                                m++;
                                for(k=0; k<20; k++)
                                    SDL_BlitSurface(image,&keypicture[number2screen[k]],surface,&screen[1][k]);//
                                SDL_UpdateWindowSurface(window);
                            }
                        }
                    }
                }
            }

        }
    }
}
void Numbersynthesis()
{
    for(i=0;i<n-1;i++)
        number1=number1*10+order[i];
    for(i=n;i<m-1;i++)
        number2=number2*10+order[i];
}
void Operation(SDL_Window* window)
{

    Numbersynthesis();
    result1=result;
    switch(order[n-1])
    {
    case 11:result=number1+number2;break;
    case 12:result=number1-number2;break;
    case 13:result=number1*number2;break;
    case 14:result=number1/number2;break;
    }
    for(resultlength=0;result1>0;resultlength++)
        result1/=10;
    result1=result;
    for(i=19;i>=0&&result1>0;i--)
    {
        resultscreen[i]=result1%10;
        result1/=10;
    }
    for(k=0; k<20; k++)
        SDL_BlitSurface(image,&keypicture[resultscreen[k]],surface,&screen[2][k]);//resultscreen[k]
    SDL_UpdateWindowSurface(window);
}
void Repeat(SDL_Window* window)
{
     while(quit1==false)
     {
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_QUIT)
                quit1==true;
            else if(event.type == SDL_MOUSEBUTTONDOWN&&(event.motion.x>key[0][3].x&&event.motion.x<key[0][3].x+30&&event.motion.y>key[0][3].y&&event.motion.y<key[0][3].y+50))
                Fun(window);
        }
     }
}
