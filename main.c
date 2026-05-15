#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#define SQUARE 200
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

bool is_prime(int n){
    if(n == 2) return false;
    if(n % 2 == 0) return false;
    for(int i = 3; i * i <= n; i++)
        if(n % i == 0)
            return false;
    return true;
}


void create_spiral(int n){
    int arr[n][n];
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            arr[i][j] = i + j;
        }
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
           
}

int main() {
    int arr[5][5] = {
        {21, 22, 23, 24, 25},
        {20,  7,  8,  9, 10},
        {19,  6,  1,  2, 11},
        {18,  5,  4,  3, 12},
        {17, 16, 15, 14, 13}
    };
    create_spiral(5);
    SDL_Init(SDL_INIT_VIDEO);
    struct SDL_Window* window = SDL_CreateWindow("Ural Spiral", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    struct SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for(int i = 0; i < SCREEN_HEIGHT / 5; i++){
        for(int j = 0; j < SCREEN_WIDTH / 5; j++){
            struct SDL_Rect rect = { i * (SCREEN_HEIGHT / 5), j * (SCREEN_WIDTH / 5), SQUARE, SQUARE};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            if(!is_prime(arr[i][j]))
                SDL_RenderDrawRect(renderer, &rect);
            else
                SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
    //SDL_RenderDrawRect(renderer, rect);
    //SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
