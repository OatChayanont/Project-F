#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <windows.h>

char type[100];
int day = 1, stamina = 16, money = 800;
int dc = 0; //discount
int error = 0;

struct plant{
    char name[20];
    int buy, water, sale, ea;
}p[10];

char plant_name[10][20] = {"corn", "tomato", "blueberry", "grape", "pumpkin", "parsnip", "box", "cauliflower", "potato"};
int plant_buy[10] = {150, 50, 80, 60, 100, 20, 50, 80, 80};
int plant_water[10] = {7, 5, 6, 6, 6, 2, 2, 5, 5};
int plant_sale[10] = {200, 80, 120, 110, 420, 70, 130, 380, 380};

struct item{
    char name[20];
    int buy, ea;
}item[10]; 

char item_name[3][20] = {"insecticide", "fertilizer", "stimulus"};
int item_buy[3] = {20, 50, 100};

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
    while (1){
        system("cls");
        printf("******************************************************\n");
        printf("         Are you sure you want to go to bed?          \n");
        printf("                   Today will pass,                   \n");
        printf("        and the remaining stamina will be gone.       \n");
        printf("               [Y] yes           [N] no               \n");
        printf("******************************************************\n");
        if (error){
            printf("Error\n");
            error--;
        }
        printf("\n");
        printf("-> ");
        scanf(" %[^\n]", type);
        if (istype("Y") || istype("YES")){
            for (int i = 5; i > 0; i--){
            system("cls");
            printf("******************************************************\n");
            printf("                  - TODAY IS OVER -                   \n");
            printf("******************************************************\n");
                printf("Daypass in %d s\n", i);
                sleep(1);
            }
            day++;
            stamina = 16;
            system("cls");
            break;
        }
        else if (istype("N") || istype("NO")){
            printf("\nI think i'm fine.\n");
            sleep(1);
        }
        else {
            error++;
        }
    }
}

void shop(){
    printf("                        DAY %02d\n", day);
    printf("	       stamina:%02d money:%d                \n", stamina, money);
    printf("======================================================\n");
    printf("                       + SHOP +                       \n");
    printf("______________________________________________________\n");
    printf("|         seed          | price | water | sale price |\n");
    printf("______________________________________________________\n");
    for (int i = 1; i <= 9; i++){
        char name[20];
        strcpy(name, p[i].name);
    printf("| %d. %-18s |%6d |%6d |%11d |\n", i, strcat(name, " seed"), p[i].buy, p[i].water, p[i].sale);
    }
    printf("\n");
    printf("______________________________________________________\n");
    printf("|                    item                    | price |\n");
    printf("______________________________________________________\n");
    printf("| 10. insecticide (get rid of insects)       | %5d |\n", item[10].buy);
    printf("| 11. fertilizer (water for plant -1)        | %5d |\n", item[11].buy);
    printf("| 12. stimulus (stamina +2)                  | %5d |\n", item[12].buy);
    printf("\n");
    printf("===================================== [x] to exit ====\n");
    printf("event:\n");
    printf("======================================================\n");
    printf("\n");
    printf("++ type a number before order to buy seed or item that you want ++\n");
    printf("++ water refers to the number of days it takes to water a plant to grow ++\n");
    printf("++ sale price refers to the sale price of productivity as a plant matures ++\n");
    printf("\n");
    input:
    printf("-> ");
    scanf(" %[^\n]s", type);
    if(istype("X") || istype("EXIT")){
        system("cls");
        return;
    }
    int id = atoi(type);
    if (strlen(type) > 2){
        id = 13;
    }
    int price = 0;
    if (1 <= id && id <= 12){
        if (id <= 9){
            price = p[id].buy;
            price -= (price*(dc/100));
            if (money >= price){
                money -= price;
                p[id].ea++;
                printf("    You by %s. Now you have %s %d ea.\n", p[id].name, p[id].name, p[id].ea);
            }
            else printf("   You don't have enough money\n");
        }
        else {
            price = item[id].buy;
            price -= (price*(dc/100));
            if (money >= price){
                money -= price;
                item[id].ea++;
                printf("    You by %s. Now you have %s %d ea.\n", item[id].name, item[id].name, item[id].ea);
            }
            else printf("   You don't have enough money\n");
        }
        goto input;
    }
    else{
        printf("    Sorry we don't have that item\n");
        goto input;
    }
}

void farm(){
    printf("Comming soon\n");
    sleep(1);
    system("cls");
}

int main(){
    SetConsoleTitle("FARM");
    //set plant
    for (int i = 1; i <= 9; i++){
    strcpy(p[i].name, plant_name[i-1]);
    p[i].buy = plant_buy[i-1];
    p[i].water = plant_water[i-1];
    p[i].sale = plant_sale[i-1];
    p[i].ea = 0;}
    //set item
    for (int i = 10; i <= 12; i++){
    strcpy(item[i].name, item_name[i-10]);
    item[i].buy = item_buy[i-10];
    item[i].ea = 0;}


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
            if (error){
                printf("ERROR\n");
                error--;
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
                error++;
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