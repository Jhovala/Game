/* 
    Tutorial: https://www.youtube.com/watch?v=_889aB2D1KI
    made by Bro Code and add colors by @jhovala 2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

char RED[10] = "\e[0;31m";
char GRN[10] = "\e[0;32m";
char YEL[10] = "\e[0;33m";
char BLU[10] = "\e[0;34m";
char WHT[10] = "\e[0m";

char* color_result;
char* put_color[3][3];
char board[3][3];

const char PLAYER =  'X';
const char COMPUTER =  'O';

int check_free_spaces();
char check_winner();

void reset_board();
void print_board();
void player_move();
void computer_move();
void print_winner(char);

int main(){
    printf("%sTIC TAC TOE the Game!\n", GRN);
    printf("%sPlayer -> %s%c%S",WHT ,BLU, PLAYER, WHT);
    printf("\n%sComputer -> %s%c%s\n",WHT, RED, COMPUTER, WHT);    

    char winner = ' ';
    char response;

    do
    {
    winner = ' ';
    response = ' ';

    reset_board();
    
    while(winner == ' ' && check_free_spaces() != 0){
        print_board();

        player_move();
        winner = check_winner();
        if(winner != ' ' || check_free_spaces() == 0){ break; }

        computer_move();
        winner = check_winner();
        if(winner != ' ' || check_free_spaces() == 0){ break; }
    }

    print_board();
    print_winner(winner);
    getchar(); // add this to run in linux

    printf("\nPlay again? (%sY%s/%sN%s): ",GRN ,WHT ,RED ,WHT);
    //scanf("%c"); // this no
    //scanf("%c"); // run in linux
    scanf("%c", &response);
    response = toupper(response);

    } while (response == 'Y');
    
    printf("\nThanks for playing!!! visit Bro Code channel on YouTube\n");

    return 0;
}

void reset_board(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            color_result = WHT;
            put_color[i][j] = color_result;
            board[i][j] = ' ';
        }
    }
}

void print_board(){
    printf("\n");
    printf(" %s%c %s| %s%c %s| %s%c ",put_color[0][0] ,board[0][0],YEL ,put_color[0][1] ,board[0][1],YEL ,put_color[0][2] ,board[0][2]);
    printf("%s\n---|---|---\n",YEL);
    printf(" %s%c %s| %s%c %s| %s%c ",put_color[1][0] ,board[1][0],YEL ,put_color[1][1] ,board[1][1],YEL ,put_color[1][2] ,board[1][2]);
    printf("%s\n---|---|---\n",YEL);
    printf(" %s%c %s| %s%c %s| %s%c ",put_color[2][0] ,board[2][0],YEL ,put_color[2][1] ,board[2][1],YEL ,put_color[2][2] ,board[2][2]);
    printf("%s\n",WHT);
}

int check_free_spaces(){
    int free_spaces = 9;
    
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){ if(board[i][j] != ' '){ free_spaces--;} }
    }

    return free_spaces;
}

void player_move(){
    int x, y;
    char a[10], b[10], color_[10] = "color_";

    do{
        printf("\nEnter row #(1-3): ");
        scanf("%d", &x);
        x--;
        
        printf("Enter col #(1-3): ");
        scanf("%d", &y);
        y--;
                
        if(board[x][y] != ' '){ printf("\nInvalid move!"); }
        else {
            color_result = BLU;
            put_color[x][y] = color_result;
            board[x][y] = PLAYER;
            break; }
    } while (board[x][y] != ' ');
    
}

void computer_move(){
    srand(time(0));
    int x, y;

    if(check_free_spaces() > 0){
        do{
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        color_result = RED;
        put_color[x][y] = color_result;
        board[x][y] = COMPUTER;

    } else { print_winner(' '); }
}

char check_winner(){
    for (int i = 0; i < 3; i++){ if (board[i][0] == board[i][1] && board[i][0] == board[i][2]){ return board[i][0]; } }
    for (int i = 0; i < 3; i++){ if (board[0][i] == board[1][i] && board[0][i] == board[2][i]){ return board[0][i]; } }
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]){ return board[0][0]; }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0]){ return board[0][2]; }

    return ' ';
}

void print_winner(char winner){
    if (winner == PLAYER){ printf("\nYou %sWIN%s!", GRN, WHT); }
    else if (winner == COMPUTER){ printf("\nYou %sLOSE%s!", RED, WHT); }
    else { printf("\n%sDraw%s!", BLU, WHT); }
}
