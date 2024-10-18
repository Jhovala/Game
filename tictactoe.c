/* 
    Tutorial: https://www.youtube.com/watch?v=_889aB2D1KI
    made by Bro Code follow by @jhovala 2024
    
    to do: I want the player to be blue and the computer red,
           color_result get variable name of color, strcpy change color
           but I don't know how to pass the values ​​to print_board xD
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

const char RED[10] = "\e[0;31m";
const char GRN[10] = "\e[0;32m";
const char YEL[10] = "\e[0;33m";
const char BLU[10] = "\e[0;34m";
const char WHT[10] = "\e[0m";

char* color_result;
char color_00[10] = "\e[0m";
char color_01[10] = "\e[0m";
char color_02[10] = "\e[0m";
char color_10[10] = "\e[0m";
char color_11[10] = "\e[0m";
char color_12[10] = "\e[0m";
char color_20[10] = "\e[0m";
char color_21[10] = "\e[0m";
char color_22[10] = "\e[0m";

char board[3][3];

const char PLAYER =  'X';
const char COMPUTER =  'O';

int check_free_spaces();
char check_winner();

char* set_color(char*, char*, char*);

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
    
    while(winner == ' ' && check_free_spaces() !=0){
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

    printf("\nPlay again? (%sY%s/%sN%s): ",GRN ,WHT ,RED ,WHT);
    scanf("%c");
    scanf("%c");
    scanf("%c", &response);
    response = toupper(response);

    } while (response == 'Y');
    
    printf("\nThanks for playing!!!\n");

    return 0;
}

void reset_board(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            board[i][j] = ' ';
        }
    }
}

void print_board(){
    printf("\n");
    printf(" %s%c %s| %s%c %s| %s%c ",color_00 ,board[0][0],YEL ,color_01 ,board[0][1],YEL ,color_02 ,board[0][2]);
    printf("%s\n---|---|---\n",YEL);
    printf(" %s%c %s| %s%c %s| %s%c ",color_10 ,board[1][0],YEL ,color_11 ,board[1][1],YEL ,color_12 ,board[1][2]);
    printf("%s\n---|---|---\n",YEL);
    printf(" %s%c %s| %s%c %s| %s%c ",color_20 ,board[2][0],YEL ,color_21 ,board[2][1],YEL ,color_22 ,board[2][2]);
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
        sprintf(a, "%d", x);
        
        printf("Enter col #(1-3): ");
        scanf("%d", &y);
        y--;
        sprintf(b, "%d", y);
                
        if(board[x][y] != ' '){ printf("\nInvalid move!"); }
        else {
            //another method to get color_00
            //snprintf(color_name, sizeof(color_name), "%s%s%s", color_, a, b); 
            color_result = set_color(color_, a, b);
            strcpy(color_result, BLU); //change color for sure but no show cuz print_board replaces it
            board[x][y] = PLAYER;
            break; }
    } while (board[x][y] != ' ');
    
}

void computer_move(){
    srand(time(0));
    int x, y;
    char a[10], b[10], color_[10] = "color_";

    if(check_free_spaces() > 0){
        do{
            x = rand() % 3;
            y = rand() % 3;
            sprintf(a, "%d", x);
            sprintf(b, "%d", y);
        } while (board[x][y] != ' ');

        color_result = set_color(color_, a, b);
        strcpy(color_result, RED);
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
    if (winner == PLAYER){ printf("\nYou WIN!"); }
    else if (winner == COMPUTER){ printf("\nYou LOSE!"); }
    else { printf("\nDraw!"); }
}

char* set_color(char* color_name, char* x, char* y){
    int total_len = strlen(color_name) + strlen(x) + strlen(y) + 1;
    char* color_result = (char*)malloc(total_len * sizeof(char));
    strcpy(color_result, color_name);
    strcat(color_result, x);
    strcat(color_result, y);

    return color_result;
}