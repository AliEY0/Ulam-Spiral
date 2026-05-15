#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

#define SQUARE 200
#define N 5
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};
int curdir = 0;

bool is_prime(int n){
    if(n < 2) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;
    for(int i = 3; i * i <= n; i++)
        if(n % i == 0)
            return false;
    return true;
}

bool is_valid(int currow, int curcol){
    if(curcol < 0) return false;
    if(currow < 0) return false;
    if(curcol >= N) return false;
    if(currow >= N) return false;
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
        printf("row: %d\n", row);
        printf("col: %d\n", col);
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

        print_arr(newarr);
        getchar();
        //printf("%d\n", tel);
        //tel++;
    }
    return newarr;   
}

int main() {
    int arr[5][5] = {
        {21, 22, 23, 24, 25},
        {20,  7,  8,  9, 10},
        {19,  6,  1,  2, 11},
        {18,  5,  4,  3, 12},
        {17, 16, 15, 14, 13}
    };
    int** spiral = create_spiral(N);
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
    //SDL_Delay(10000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    for(int i = 0; i < N; i++){
        free(*(spiral+ i)); 
    }

    free(spiral);
    return 0;
}
