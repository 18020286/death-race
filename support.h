#ifndef SUPPORT_H_INCLUDED
#define SUPPORT_H_INCLUDED

#include<iostream>
#include<algorithm>
#include "game.h"
#include<SDL.h>
#include<SDL_mixer.h>
#include<vector>
#include<fstream>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char WINDOW_TITLE[] = "Racing boy";
const int borderLeft = 140;
const int borderRight = 660;
const int car_width = 50;
const int car_height = 80;
const int step  = 20;

int getRandomNumber(const int &a , const int &b);

void restart_x_y_score(double & Car1y , double & Car2y , double & Car3y , double & Car4y , int & Racerx , int & Racery , int &Score , double &Speed);

vector<SDL_Texture* > load_image(SDL_Renderer * renderer);

void menu_game(bool & running , SDL_Renderer* renderer , SDL_Window* window);

void countScore_newLoopCar(double &car1Y ,double &car2Y ,double &car3Y ,double &car4Y, int &car1X , int &car2X, int &car3X, int &car4X ,int &totalscores, double &speed);

double level_game(const int & totalscores);

void control_car(SDL_Renderer* renderer,int &racerX  ,int &racerY , bool &running);

void accident(double &car1Y ,double &car2Y ,double &car3Y ,double &car4Y,int &car1X ,int &car2X,int &car3X,int &car4X ,int &racerX,int &racerY, bool &running , Mix_Chunk * sound_effect );

void highScore(const int &high_score);

void play_again(bool & running ,SDL_Renderer* renderer,double &car1Y ,double &car2Y ,double &car3Y ,double &car4Y ,int  &racerX ,int &racerY ,int &totalscores ,double &speed);

void show_score (const string & file_name , SDL_Renderer * renderer);


#endif // SUPPORT_H_INCLUDED
