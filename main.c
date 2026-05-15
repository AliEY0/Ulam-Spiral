#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#define N 899
#define SCREEN_WIDTH 899
#define SCREEN_HEIGHT 899

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

bool is_prime(int n){
    if(n == 2) return true;
    if(n < 2 || n % 2 == 0) return false;
    for(int i = 3; i * i <= n; i++)
        if(n % i == 0)
            return false;
    return true;
}

bool is_valid(int currow, int curcol){
    if(curcol < 0 || currow < 0 || curcol >= N || currow >= N) return false;
    return true;
}

void print_arr(int** newarr){
    printf("----------------------------\n");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d ", *(newarr[i] + j));
        }
        printf("\n");
    }
    printf("----------------------------\n");
}
int** create_spiral(int n){
    int curdir = 0;    
    int** newarr = malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        *(newarr + i) = malloc(n * sizeof(int));
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            *(newarr[i] + j) = 0;
        }
    }
    int tel = 0;
    int row = N / 2, col = N / 2;
    *(newarr[row] + col) = ++tel;
    while(tel < N * N){
        if(is_valid(row + dy[curdir], col + dx[curdir])){
            if(*(newarr[row + dy[curdir]] + (col + dx[curdir])) == 0){
                *(newarr[row + dy[curdir]] + (col + dx[curdir])) = ++tel;
                row += dy[curdir];
                col += dx[curdir];
                
                int row_newdir = (row + dy[(curdir + 1) % 4]);
                int col_newdir = (col + dx[(curdir + 1) % 4]);

                if(is_valid(row_newdir, col_newdir)){
                    if(*(newarr[row_newdir] + col_newdir) == 0)
                        curdir =  (curdir + 1) % 4;
                }else{
                        curdir =  (curdir + 1) % 4;
                }
            }
        }
    }
    return newarr;   
}

void render_spiral(int** spiral){
    SDL_Init(SDL_INIT_VIDEO);
    struct SDL_Window* window = SDL_CreateWindow("Ulam Spiral", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    struct SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            struct SDL_Rect rect = { i * (SCREEN_HEIGHT / N), j * (SCREEN_WIDTH / N), (SCREEN_HEIGHT / N), (SCREEN_WIDTH / N)};
            if(is_prime(spiral[i][j]))
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            else    
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

            SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    SDL_Event event;
    bool quit = false;
    while(!quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = true;
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void free_2D_array(int** arr){
    for(int i = 0; i < N; i++)
        free(*(arr+ i)); 
    free(arr);
}
int main() {
    if(N % 2){
        int** spiral = create_spiral(N);
        render_spiral(spiral);
        free_2D_array(spiral);
    }

    for(int i = 900; i >= 750; i--){
        for(int j = 1; j <= 5; j++){
            if(i % j == 0){
                if((i / j) % 2 == 1)
                    printf("i = %d, j = %d -> i / j = %d\n", i, j, i / j);
            }
        }
    }


    return 0;
}
