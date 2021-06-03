#include "support.h"

int getRandomNumber(const int &a , const int &b){

    int result = a + ( rand() % (b - car_width -  a) + 1 )   ;
    return result;
}

void restart_x_y_score(double & Car1y , double & Car2y , double & Car3y , double & Car4y , int & Racerx , int & Racery , int &Score , double &Speed){
    Car1y  = 0 ;
    Car2y  = -100 ;
    Car3y  = -200 ;
    Car4y = -300 ;
    Racerx = (SCREEN_WIDTH - car_width) / 2;
    Racery = SCREEN_HEIGHT / 3 * 2;
    Score = 0 ;
    Speed = 1.6 ;
}

vector<SDL_Texture* > load_image(SDL_Renderer * renderer)
{
    vector<SDL_Texture*> game_images;
    for(int i =  0 ; i < 10 ; i ++){
        game_images.push_back(loadTexture("images/background.bmp", renderer));
        game_images.push_back(loadTexture("images/car1.bmp", renderer));
        game_images.push_back(loadTexture("images/car2.bmp", renderer));
        game_images.push_back(loadTexture("images/car3.bmp", renderer));
        game_images.push_back(loadTexture("images/car4.bmp", renderer));
        game_images.push_back(loadTexture("images/racer.bmp", renderer));
        game_images.push_back(loadTexture("images/endgame.bmp", renderer));
        game_images.push_back(loadTexture("images/start.bmp", renderer));
        game_images.push_back(loadTexture("images/start1.bmp", renderer));
        game_images.push_back(loadTexture("images/over_again.bmp", renderer));
    }
    return game_images;
}

void menu_game(bool &running , SDL_Renderer* renderer , SDL_Window* window)
{
    SDL_Event e;
    SDL_Texture * start_image = loadTexture("images/start.bmp", renderer);
    SDL_Texture * off_volume = loadTexture("images/start1.bmp", renderer);
    renderTexture(start_image , renderer , 0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(renderer);
    while (true){
        static int count  = 0;
        if ( SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_MOUSEBUTTONDOWN){
                // thoat game
             if((e.button.x >= 750 && e.button.x <= 792) && (e.button.y >= 8 && e.button.y <= 44)){
                    quitSDL(window, renderer);
             }
                //tat bat nhac
             if((e.button.x >= 750 && e.button.x <= 784) && (e.button.y >= 68 && e.button.y <= 104)){
                    count ++;
                    SDL_RenderClear(renderer);
                    if(count % 2 == 1 ){
                            Mix_PauseMusic();
                            renderTexture(off_volume , renderer , 0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    }else {
                            Mix_ResumeMusic();
                            renderTexture( start_image, renderer , 0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT);
                    }
                    SDL_RenderPresent(renderer);
             }
                  //vao game
             if((e.button.x >= 630 && e.button.x <= 782) && (e.button.y >= 400 && e.button.y <= 518)){
                    running = true;
                    SDL_Delay(500);
                    break;
             }else running = false;
        }
    }
}

void countScore_newLoopCar(double &car1Y ,double &car2Y ,double &car3Y ,double &car4Y, int &car1X , int &car2X, int &car3X, int &car4X , int &totalscores, double &speed)
{
        if (car1Y > SCREEN_HEIGHT){
                totalscores ++;
                car1Y = - car_height;
                car1X = getRandomNumber(borderLeft,borderRight);
        } else {car1Y = car1Y + speed;}
        if (car2Y > SCREEN_HEIGHT){
                totalscores ++;
                car2Y = - car_height;
                car2X = getRandomNumber(borderLeft,borderRight);
        } else {car2Y = car2Y + speed;}
        if (car3Y > SCREEN_HEIGHT){
                totalscores ++;
                car3Y = - car_height;
                car3X = getRandomNumber(borderLeft,borderRight);
        } else {car3Y = car3Y + speed;}
        if (car4Y > SCREEN_HEIGHT){
                totalscores ++;
                car4Y = - car_height;
                car4X = getRandomNumber(borderLeft,borderRight);
        } else {car4Y = car4Y + speed;}

}

double level_game(const int & totalscores)
{
    double speed;
    if(totalscores < 7) {speed = 1.6 ;}
    if(totalscores >= 7 && totalscores < 18) {speed = 3 ;}
    if(totalscores >= 18 && totalscores < 30) {speed = 5 ;}
    if(totalscores >= 30 && totalscores < 45) {speed = 7 ;}
    if(totalscores >= 45 ) {speed = 9;}
    return speed;
}

void control_car(SDL_Renderer* renderer,int &racerX  ,int &racerY , bool &running)
{
        SDL_Event e;
        SDL_Texture * racer = loadTexture("images/racer.bmp", renderer);
        renderTexture(racer , renderer , racerX  , racerY , car_width , car_height );
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                    running = false;
                    break;
            }
            if (e.type == SDL_KEYDOWN) {

                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                        break;
                    }
                    if (e.key.keysym.sym == SDLK_LEFT) {
                            racerX = racerX  - step ;
                            if(racerX < borderLeft) racerX = borderLeft;
                    }
                    if (e.key.keysym.sym == SDLK_RIGHT){
                            racerX = racerX + step ;
                            if(racerX > borderRight - car_width) racerX = borderRight - car_width;
                    }
                    if (e.key.keysym.sym == SDLK_DOWN) {
                            racerY = racerY + step ;
                            if(racerY > SCREEN_HEIGHT - car_height) racerY = SCREEN_HEIGHT - car_height;
                    }
                    if (e.key.keysym.sym == SDLK_UP) {
                            racerY = racerY - step ;
                            if(racerY < 0 ) racerY = 0;
                    }
            }
        }
}

void accident(double &car1Y ,double &car2Y ,double &car3Y ,double &car4Y,int &car1X ,int &car2X,int &car3X,int &car4X ,int &racerX,int &racerY, bool &running , Mix_Chunk * sound_effect )
{
        if (((racerX >= (car1X - 45)) &&(racerX <= (car1X + 45)))&&((racerY >= (car1Y - 75)) &&(racerY) <= (car1Y + 75))){
            Mix_PlayChannel(-1 , sound_effect , 0);
            running = false;
            SDL_Delay(2000);
        }
        if (((racerX >= (car2X - 45)) &&(racerX <= (car2X + 45)))&&((racerY >= (car2Y - 75)) &&(racerY) <= (car2Y + 75))){
            Mix_PlayChannel(-1 , sound_effect , 0);
            running = false;
            SDL_Delay(2000);
        }
        if (((racerX >= (car3X - 45)) &&(racerX <= (car3X + 45)))&&((racerY >= (car3Y - 75)) &&(racerY) <= (car3Y + 75))){
            Mix_PlayChannel(-1 , sound_effect , 0);
            running = false;
            SDL_Delay(2000);
        }
        if (((racerX >= (car4X - 45)) &&(racerX <= (car4X + 45)))&&((racerY >= (car4Y - 75)) &&(racerY) <= (car4Y + 75))){
            Mix_PlayChannel(-1 , sound_effect , 0);
            running = false;
            SDL_Delay(2000);
        }
}

bool tmp(int a , int b){
    return a > b;
}

void highScore(const int &high_score)
{
    vector<int> score;
    ifstream file("score.txt");
    if(file.is_open()){
        while(!file.eof()){
            int a ;
            file >> a;
            score.push_back(a);
        }
    }
    file.close();
    if(high_score > score[9]){
        score.push_back(high_score);
        sort(score.begin(), score.end(),tmp);
        ofstream file("score.txt");
        if(file.is_open()){
            for(int i = 0 ; i < 10 ; i++){
                file << score[i] << endl;
            }
        }
    }
    file.close();
}

void play_again(bool & running ,SDL_Renderer* renderer,double &car1Y ,double &car2Y ,double &car3Y ,double &car4Y ,int  &racerX ,int &racerY ,int &totalscores ,double &speed)
{
    SDL_Event e;
    highScore(totalscores);
    SDL_Texture * over_again = loadTexture("images/over_again.bmp", renderer);
    renderTexture(over_again , renderer , 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT);
    SDL_RenderPresent(renderer);
    while(true){
        if ( SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_MOUSEBUTTONDOWN){
            if((e.button.x >= 335 && e.button.x <= 383) && (e.button.y >= 396 && e.button.y <= 433)){
                running = true;
                restart_x_y_score(car1Y , car2Y , car3Y , car4Y , racerX , racerY , totalscores , speed);
                break;
            }
            if((e.button.x >= 416 && e.button.x <= 453) && (e.button.y >= 396 && e.button.y <= 433)){
                break;
            }
        }
    }
}

void show_score (const string & file_name , SDL_Renderer * renderer){
    vector<int> save_score;
    ifstream file(file_name);
    if(file.is_open()){
        while(!file.eof()){
            int a ;
            file >> a;
            save_score.push_back(a);
        }
    }
    file.close();
    for(int i = 0 ; i < 10 ; i++){
        string score = "";
        score += to_string(save_score[i]);
        SDL_Texture* high_score = create_text(renderer , score) ;
        renderTexture(high_score, renderer , SCREEN_WIDTH/2 - 35 , 130 + 35 * i , 20 , 35 );
    }
}
