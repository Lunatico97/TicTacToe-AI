#include <iostream>
#include <SDL2/SDL.h>
#define SCR_W 640
#define SCR_H 480
#define BRD_X 200
#define BRD_Y 100
#define BRD_D 50

struct Board{
    char positions[3][3] = {
                            {'_', '_', '_'}, 
                            {'_', 'X', '_'}, 
                            {'O', '_', '_'}
                           } ;
} ;

void printBoardState(struct Board b){
    for(int i=0; i<3; i++){
        std::cout << b.positions[i][0] << " | " << b.positions[i][1] << " | " << b.positions[i][2] << std::endl ;
        if(i != 2) std::cout << "---------" << std::endl ;
    }
    std::cout << "--------------------------------------------------------------" << std::endl ;
}

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING) ;
    SDL_Window *window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_W, SCR_H, 0) ;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0) ;
    bool isProgramActive = true ;
    SDL_Event event ;
    SDL_Rect tempRect ;
    struct Board board ;
    int mouseX, mouseY ;
    char turn, wait, temp ;

    if(argc < 2){
        std::cerr << "Choose who starts first: RED (X) or BLUE (O) !! [X/O] ?" << std::endl ;
        std::cerr << "For example: ./tictactoe X" << std::endl ;
        exit(1) ;
    }
    else{
        turn = argv[1][0] ;
        if(turn == 'X') wait = 'O' ;
        else wait = 'X' ;
    }

    // Game Loop     
    while(isProgramActive){
        // Event Handler
        SDL_GetMouseState(&mouseX, &mouseY) ;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                isProgramActive = false ;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN){ 
                if(mouseX > BRD_X && mouseY > BRD_Y && mouseX < (BRD_X+BRD_D*3) && mouseY < (BRD_Y+BRD_D*3)){
                    // Within the bounds
                    board.positions[(mouseY-BRD_Y)/BRD_D][(mouseX-BRD_X)/BRD_D] = turn ;
                    temp = turn ;
                    turn = wait ;
                    wait = temp ;
                }
                printBoardState(board) ;
                std::cout << "Turn: " << turn << std::endl ;
                std::cout << "Wait: " << wait << std::endl ;
            }
        } 

        // Graphics   
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255) ;     
        SDL_RenderClear(renderer) ;
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255) ;
                tempRect = {BRD_X + j*BRD_D, BRD_Y + i*BRD_D, BRD_D, BRD_D} ;
                if(board.positions[i][j] == '_')
                    SDL_RenderDrawRect(renderer, &tempRect) ;
                else if(board.positions[i][j] == 'X'){
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255) ;
                    SDL_RenderFillRect(renderer, &tempRect) ;
                }
                else{
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255) ;
                    SDL_RenderFillRect(renderer, &tempRect) ;
                }
            }
        }

        SDL_RenderPresent(renderer) ;
    }

    SDL_DestroyRenderer(renderer) ;
    SDL_DestroyWindow(window) ;
    SDL_Quit() ;
    return 0 ;
}