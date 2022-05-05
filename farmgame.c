#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <windows.h>

char type[100];
int day = 0, stamina = 16, money = 800;

int istype(char check[100]){ 
    //  ใช้แทน strcmp
    for (int i = 0; i <= strlen(type); i++){
        type[i] = toupper(type[i]);
    }
    if (strcmp(type, check) == 0){
        return 1;
    }
    else{
        return 0;
    }

}

void home(){
    printf("******************************************************\n");
    printf("         Are you sure you want to go to bed?          \n");
    printf("                   Today will pass,                   \n");
    printf("        and the remaining stamina will be gone.       \n");
    printf("               [Y] yes           [N] no               \n");
    printf("******************************************************\n");
    printf("\n");
    input:
    printf("->");
    scanf(" %[^\n]", type);
    if (istype("Y") || istype("YES")){
        system("cls");
        printf("******************************************************\n");
        printf("                  - TODAY IS OVER -                   \n");
        printf("******************************************************\n");
        for (int i = 5; i >= 0; i--){
            printf("%d\n", i);
            sleep(1);
        }
        day++;
        stamina = 16;
        system("cls");
    }
    else if (istype("N") || istype("NO")){
        printf("I think i'm fine.\n");
        sleep(1);
    }
    else {
        printf("Error\n");
        goto input;
    }
}

void shop(){
    printf("Comming soon\n");
    sleep(1);
    system("cls");
}

void farm(){
    printf("Comming soon\n");
    sleep(1);
    system("cls");
}

int main(){
    SetConsoleTitle("FARM");
    start:
    system("cls");
    printf("======================================================\n");
    printf("            THIS IS ' FARM' GAME                      \n");
    printf("======================================================\n");
    printf("                     type [start]                     \n");
    printf("\n-> ");
    scanf(" %[^\n]", type);
    if (istype("START")){
        system("cls");
        printf("story : One day. There are YouTubers who make content for farmers to race to grow crops to sell,\n");
        printf("to compete against who earns the most money, and you are one of the contestants.\n");
        printf("++ you will start the game with 800 coin ++\n");
        printf("++ each day you have 16 stamina, to do some action will reduce your stamina ++\n");
        printf("++ the goal of the game is to save as much money as you can ++\n");
        printf("++ when you play a game, you must type a word or a number to activate the action written on the line ++\n");
        while (1){
            printf("******************************************************\n");
            printf("                        DAY %02d                        \n", day);
            printf("	       stamina:%02d money:%d                \n", stamina, money);
            printf("*****************************************************\n");
            printf(" type [H] to go to home (sleep for skip the day)\n");
            printf(" type [S] to go to shop\n");
            printf(" type [F] to go to farm\n");
            printf(" type [X] to exit this game\n");
            printf("\n");
            printf("******************************************************\n");
            printf("event:\n");
            printf("******************************************************\n");
            if (0){
                error:
                printf("Error\n");
            }
            printf("-> ");
            scanf(" %[^\n]", type);
            system("cls");
            if (istype("H") || istype("HOME")){
                home();
            }
            else if (istype("S") || istype("SHOP")){
                shop();
            }
            else if (istype("F") || istype("FARM")){
                farm();
            }
            else if (istype("X") || istype("EXIT")){
                break;
            }
            else{
                goto error;
            }
        }
    }
    else{
        goto start;
    }
    printf("******************************************************\n");
    printf("                   thx for playing                    \n");
    printf("******************************************************\n");
    sleep(3);
    printf("******************************************************\n");
    printf("                     - END GAME -\n");
    printf("your money = %d\n", money);
    printf("                   thx for playing\n");
    printf("******************************************************\n");
    scanf(" %c", type);
    return 0;
}