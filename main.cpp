#include<iostream>
#include<SDL.h>
#include "game.h"
#include "support.h"
#include<vector>
#include<ctime>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
using namespace std;

//**************************************************************
int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SDL_Event e;
        // load cac hinh anh vao 1 mang
    vector <SDL_Texture *> game_images = load_image(renderer);
    SDL_Texture * car1 = game_images[1];
    SDL_Texture * car2 = game_images[2];
    SDL_Texture * car3 = game_images[3];
    SDL_Texture * car4 = game_images[4];

    Mix_OpenAudio(44100 , MIX_DEFAULT_FORMAT , 2 , 2048);
    Mix_Music * backgroundsound  = Mix_LoadMUS("sound/bgsound.mp3");
    Mix_Chunk * sound_effect = Mix_LoadWAV("sound/carcrash.wav");

    double speed = 1.6;
    int totalscores = 0;
    string scores  = "";
    bool running = false;
    int car1X , car2X, car3X , car4X;
    double car1Y  = 0 , car2Y  = -100 , car3Y  = -200, car4Y = -300;
    car1X = getRandomNumber(borderLeft , borderRight);
    car2X = getRandomNumber(borderLeft , borderRight);
    car3X = getRandomNumber(borderLeft , borderRight);
    car4X = getRandomNumber(borderLeft , borderRight);
    int racerX = (SCREEN_WIDTH - car_width) / 2;
    int racerY = SCREEN_HEIGHT / 3 * 2;
    int background1Y = 0;
    int background2Y = -600;

    Mix_PlayMusic(backgroundsound , -1);

    menu_game(running , renderer , window);

    while(running){
        SDL_RenderClear(renderer);
        SDL_Texture * background = game_images[0];
        renderTexture(background , renderer , 0 , background1Y , SCREEN_WIDTH, SCREEN_HEIGHT);
        renderTexture(background , renderer , 0 , background2Y , SCREEN_WIDTH, SCREEN_HEIGHT);
        background1Y += 1;
        background2Y += 1;
        if(background2Y > 0){
            background1Y = 0;
            background2Y = -600;
        }
            //hien thi diem so
        scores = "score :" + to_string(totalscores);
        SDL_Texture * texture = create_text( renderer , scores);
        renderTexture(texture, renderer , 2 , 2 , 80 , 35);

         //hien thi cac xe dua may
        renderTexture(car1 , renderer , car1X , car1Y , car_width , car_height);
        renderTexture(car2 , renderer , car2X , car2Y , car_width , car_height);
        renderTexture(car3 , renderer , car3X , car3Y , car_width , car_height);
        renderTexture(car4 , renderer , car4X , car4Y , car_width , car_height);
            //tinh diem va tao lai cac xe dua may cho vong lap tiep theo
        countScore_newLoopCar(car1Y, car2Y, car3Y, car4Y, car1X , car2X, car3X , car4X, totalscores, speed);
          // level game
        speed = level_game(totalscores);
            //tao xe nguoi choi va dieu khien
        control_car(renderer , racerX , racerY , running);
             //va cham
        accident(car1Y, car2Y, car3Y, car4Y, car1X , car2X, car3X , car4X, racerX , racerY , running , sound_effect);

        if(running == false){
            // chon choi lai hoac thoat
            play_again(running, renderer, car1Y , car2Y , car3Y , car4Y , racerX , racerY , totalscores , speed);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_Delay(200);
    Mix_FreeMusic(backgroundsound);
    SDL_RenderClear(renderer);
    SDL_Texture* tao = loadTexture("images/highscore.bmp", renderer);
    renderTexture(tao, renderer , 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT);
    show_score("score.txt", renderer);
    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
