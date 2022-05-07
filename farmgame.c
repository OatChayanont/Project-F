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
    int buy, water, sale, regrowth , ea;
}p[10];

char plant_name[10][20] = {"corn", "tomato", "blueberry", "grape", "pumpkin", "parsnip", "bok choy", "cauliflower", "potato"};
int plant_buy[10] = {150, 50, 80, 60, 100, 20, 50, 80, 80};
int plant_water[10] = {7, 5, 6, 6, 6, 2, 2, 5, 5};
int plant_sale[10] = {200, 80, 120, 110, 420, 70, 130, 380, 380};
int plant_regrowth[10] = {1, 1, 1, 1, 0, 0, 0, 0, 0};

struct item{
    char name[20];
    int buy, ea;
}item[10]; 

char item_name[3][20] = {"insecticide", "fertilizer", "stimulus"};
int item_buy[3] = {20, 50, 100};

struct farm{
    int w, mw, use, plant, water_yet, insect;
    char status[10];
}f[10];

int istype(char check[100]){ 
    //  ใช้แทน strcmp
    for (int i = 0; i <= strlen(type); i++){
        type[i] = tolower(type[i]);
    }
    if (strcmp(type, check) == 0){
        return 1;
    }
    else{
        return 0;
    }

}

void loading(char text[100]){
    printf("%s", text);
    for (int i = 0; i <= 2; i++){
        printf(" .");
        sleep(1);
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
        if (istype("y") || istype("yes")){
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
            for (int i = 1;i <= 9;i++){
                f[i].water_yet = 0;
            }
            system("cls");
            break;
        }
        else if (istype("n") || istype("no")){
            printf("\nI think i'm fine.\n");
            sleep(1);
            return;
        }
        else {
            error++;
        }
    }
}

void shop(){
    while(1){
        system("cls");
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
        printf("-> ");
        scanf(" %[^\n]s", type);
        if(istype("x") || istype("exit")){
            system("cls");
            return;
        }
        int id = atoi(type);
        if (strlen(type) > 2 || (id < 10 && strlen(type) >= 2)){
            id = 15;
        }
        int price = 0;
        if (1 <= id && id <= 12){
            if (id <= 9){
                price = p[id].buy;
                price -= (price*(dc/100));
                if (money >= price){
                    money -= price;
                    p[id].ea++;
                    printf("    You by %s seed. Now you have %s seed %d ea.\n", p[id].name, p[id].name, p[id].ea);
                }
                else printf("   You don't have enough money\n");
            }
            else {
                price = item[id].buy;
                price -= (price*(dc/100));
                if (money >= price){
                    money -= price;
                    item[id].ea++;
                    printf("    You by %s seed. Now you have %s seed %d ea.\n", item[id].name, item[id].name, item[id].ea);
                }
                else printf("   You don't have enough money\n");
            }
        }
        else{
            printf("    Error\n");
        }
        loading("wait a minute .");
    }
}

void farm(){
    while (1){
        start:
        printf("                        DAY %02d\n", day);
        printf("	       stamina:%d money:%d                \n", stamina, money);
        printf("======================================================\n");
        for (int i = 0; i <= 2; i++){
            printf("\n");
            for (int j = 1; j <= 3; j++){
                printf("  ++++++++++++++  ");
            }
            printf("\n");
            for (int j = 1; j <= 3; j++){
                if (f[j+(i*3)].use){
                printf("  |%12s|  ", p[f[j+(i*3)].plant].name);
                }
                else printf("  |            |  ");
            }
            printf("\n");
            for (int j = 1; j <= 3; j++){
                if (f[j+(i*3)].use){
                printf("  |    %d/%d     |  ", f[j+(i*3)].w, f[j+(i*3)].mw);
                }
                else printf("  |            |  ");
            }
            printf("\n");
            for (int j = 1; j <= 3; j++){
                if (f[j+(i*3)].use){
                printf("  |%12s|  ", f[j+(i*3)].status);
                }
                else printf("  |            |  ");
            }
            printf("\n");
            for (int j = 1; j <= 3; j++){
                printf("  |[%d] farm [%d]|  ", j+(i*3), j+(i*3));
            }
            printf("\n");
            for (int j = 1; j <= 3; j++){
                printf("  ++++++++++++++  ");
            }
            printf("\n");
        }
        printf("\n");
        printf("======================================================\n");
        printf("event:\n");
        printf("======================================================\n");
        printf("\n");
        printf(" type [P] to plant (-1 stamina per once)\n");
        printf(" type [W] to water (-1 stamina per once)\n");
        printf(" type [R] to remove plant (-1 stamina per once)\n");
        printf(" type [C] to harvest the plant that blooms and sell it automatically (-1 stamina per once)\n");
        printf(" type [I] to use insecticides(%d EA) (-1 stamina per once)\n", item[10].ea);
        printf(" type [T] to use stimulus(%d EA) (+2 stamina)\n", item[12].ea);
        printf(" type [X] to exit\n");
        printf("\n");
        printf("++ type a word in squre blacket to do what is written on the line. \n");
        printf("++ You can water each farm once a day ++\n");
        printf("\n");
        printf("-> ");
        scanf(" %[^\n]", type);
        if (istype("p") || istype("plant")){
            if(stamina <= 0){
                printf("You don't have enough stamina.\n");
                sleep(2);
                system("cls");
                continue;
            }
            printf("Enter farm number to plant (Enter X to cancel)\n");
            scanf(" %[^\n]", type);
            if (istype("x") || istype("cancel")){
                system("cls");
                continue;
            }
            int num = atoi(type);
            if(strlen(type) > 1){
                printf("Error\n");
                sleep(1);
                system("cls");
            }
            if (1 <= num && num <= 9 && f[num].use == 0){
                printf("******************************************************\n");
                printf("	   what seed do you want to plant?\n");
                for (int i = 1; i <= 9; i++){
                    printf(" [%d]%-12s (You have %-11s seed %2d ea.)\n", i, p[i].name, p[i].name, p[i].ea);
                }
                printf("******************************************************\n");
                printf("-> ");
                scanf(" %[^\n]", type);
                int c_num = atoi(type);
                for (int i = 1; i <= 9; i++){
                    if ((i == c_num || istype(p[i].name)) && p[i].ea >= 1){
                        stamina--;
                        p[i].ea--;
                        f[num].use = 1;
                        f[num].plant = i;
                        f[num].w = 0;
                        f[num].mw = p[i].water;
                        strcpy(f[num].status, "usual");
                        if (item[11].ea >= 1){
                            error:
                            printf(" fertilise? you have fertilizer %d ea\n", item[11].ea);
                            printf(" Y(yes)/N(no)?\n");
                            scanf(" %[^\n]", type);
                            if (istype("y") || istype("yes")){
                                f[num].mw--;
                                item[11].ea--;
                                printf(" fertilizer -1 ea. Now you have %d ea\n", item[11].ea);
                            }
                            else if (istype("n") || istype("no")){
                                printf("\n");
                            }
                            else{
                                goto error;
                            }
                        }
                        printf("Stamina -1\n");
                        loading("Plant");
                        system("cls");
                        goto start;
                    }
                    else if(p[i].ea <= 0){
                        printf("You don't have seed\n");
                        goto start;
                    }
                }
                printf("Error\n");
                system("cls");

            }
            else {
                printf("Error\n");
                sleep(1);
                system("cls");
            }
        }
        else if(istype("w") || istype("water")){
            if(stamina <= 0){
                printf("You don't have enough stamina.\n");
                sleep(2);
                system("cls");
                continue;
            }
            printf("Enter farm number to water (Enter X to cancel)\n");
            scanf(" %[^\n]", type);
            if (istype("x") || istype("cancel")){
                system("cls");
                continue;
            }
            int num = atoi(type);
            if(strlen(type) > 1){
                printf("Error\n");
                sleep(1);
                system("cls");
            }
            if (1 <= num && num <= 9){
                stamina--;
                if (f[num].water_yet == 0){
                f[num].w++;
                f[num].water_yet = 1;
                printf("Stamina -1\n");
                printf("Succeed\n");
                if (f[num].w >= f[num].mw){
                    strcpy(f[num].status, "bloom");
                }
                loading("Water");
                }
            }
            else {
                printf("Error\n");
                sleep(1);
                system("cls");
            }
        }
        else if(istype("r") || istype("remove")){
            if(stamina <= 0){
                printf("You don't have enough stamina.\n");
                sleep(2);
                system("cls");
                continue;
            }
            printf("Enter farm number to remove plant (Enter X to cancel)\n");
            scanf(" %[^\n]", type);
            if (istype("x") || istype("cancel")){
                system("cls");
                continue;
            }
            int num = atoi(type);
            if(strlen(type) > 1){
                printf("Error\n");
                sleep(1);
                system("cls");
            }
            if (1 <= num && num <= 9 && f[num].use == 1){
                stamina--;
                f[num].use = 0;
                printf("Stamina -1\n");
                printf("Succeed\n");
                loading("Remove");
            }
            else if (f[num].use == 0){
                printf("Don't have plant to remove in this farm\n");
                loading("Loading");
            }
            else {
                printf("Error\n");
                sleep(1);
                system("cls");
            }
        }
        else if(istype("c") || istype("harvest")){
            if(stamina <= 0){
                printf("You don't have enough stamina.\n");
                sleep(2);
                system("cls");
                continue;
            }
            printf("Enter farm number to harvest (Enter X to cancel)\n");
            scanf(" %[^\n]", type);
            if (istype("x") || istype("cancel")){
                system("cls");
                continue;
            }
            int num = atoi(type);
            if(strlen(type) > 1){
                printf("Error\n");
                sleep(1);
                system("cls");
            }
            if (1 <= num && num <= 9 && f[num].use == 1){
                stamina--;
                if (strcmp(f[num].status, "bloom") == 0){
                    if (p[f[num].plant].regrowth){
                        strcpy(f[num].status, "usual");
                        money += p[f[num].plant].sale;
                    }
                    else{
                        f[num].use = 0;
                        strcpy(f[num].status, "usual");
                        money += p[f[num].plant].sale;
                    }
                    loading("Harvest");
                }
                else {
                    printf("This plant not bloom\n");
                    loading("Loading");
                }
            }
            else if (f[num].use == 0){
                printf("This farm don't have plant.\n");
                loading("Loading");
            }
            else {
                printf("Error\n");
                sleep(1);
                system("cls");
            }
        } 
        else if(istype("i") || istype("insecticides")){
            if(stamina <= 0){
                loading("You don't have enough stamina.");
                system("cls");
                continue;
            }
            if(item[10].ea <= 0){
                loading("You don't have insecticides");
                system("cls");
                continue;
            }
            printf("Enter farm number to use insecticides (Enter X to cancel)\n");
            scanf(" %[^\n]", type);
            if (istype("x") || istype("cancel")){
                system("cls");
                continue;
            }
            int num = atoi(type);
            if(strlen(type) > 1){
                printf("Error\n");
                sleep(1);
                system("cls");
            }
            if (1 <= num && num <= 9 && f[num].use == 1){
                stamina--;
                f[num].insect = 0;
                if(f[num].w >= f[num].mw){
                    strcpy(f[num].status, "bloom");
                }
                else strcpy(f[num].status, "usual");
                printf("Stamina -1\n");
                printf("Succeed\n");
                loading("Use insecticides");
            }
            else if (f[num].use == 0){
                printf("Don't have plant to use insecticides in this farm\n");
                loading("Loading");
            }
            else {
                printf("Error\n");
                sleep(1);
                system("cls");
            }
        }
        else if(istype("t") || istype("stimulus")){
            if(item[12].ea <= 0){
                loading("You don't have stimulus");
                system("cls");
                continue;
            }
            else{
                loading("Use stimulus");
                stamina += 2;
                system("cls");
                continue;
            }
        }
        else if(istype("x") || istype("exit")){
            system("cls");
            break;
        }
        else{
            loading("Error");
        }
        system("cls");
    }
}

int main(){
    SetConsoleTitle("FARM");
    //set plant
    for (int i = 1; i <= 9; i++){
        strcpy(p[i].name, plant_name[i-1]);
        p[i].buy = plant_buy[i-1];
        p[i].water = plant_water[i-1];
        p[i].sale = plant_sale[i-1];
        p[i].regrowth = plant_regrowth[i-1];
        p[i].ea = 0;}
    //set item
    for (int i = 10; i <= 12; i++){
        strcpy(item[i].name, item_name[i-10]);
        item[i].buy = item_buy[i-10];
        item[i].ea = 0;}
    //set farm
    for (int i = 1; i <= 9; i++){
        strcpy(f[i].status, "");
        f[i].w = 0;
        f[i].mw = 0;
        f[i].use = 0;
        f[i].plant = 0;
        f[i].water_yet = 0;
        f[i].insect = 0;
    }

    start:
    system("cls");
    printf("======================================================\n");
    printf("            THIS IS ' FARM' GAME                      \n");
    printf("======================================================\n");
    printf("                     type [start]                     \n");
    printf("\n-> ");
    scanf(" %[^\n]", type);
    if (istype("start")){
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
            if (istype("h") || istype("home")){
                home();
            }
            else if (istype("s") || istype("shop")){
                shop();
            }
            else if (istype("f") || istype("farm")){
                farm();
            }
            else if (istype("x") || istype("exit")){
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