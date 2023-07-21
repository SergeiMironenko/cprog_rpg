#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "player.h"  // Функции игрока
#include "enemy.h"  // Функции противника
#include "mechanics.h"  // Игровые функции, механики
#include "functions.h"  // Неигровые функции
#include "locations.h"  // Описание локаций

void menu(Player *player)
{
    srand(time(NULL));
    char c = '\n';
    char exit = 0;  // 0 - игра, 1 - выход, 2 - проигрыш
    char location = 0;
    char room = 0;
    char next_room = 0;
    char choice = 0;
    char choice_max = 0;
    char dungeon_state[38] = {0};  // 1 бит - посещена / не посещена комната
    while (!exit)
    {
        switch(location)
        {
            case 0:
                dungeon(room, &next_room, player, dungeon_state);
                break;
            // case 1:
            //     village();
            //     break;
            // case 2:
            //     mountain();
            //     break;
            // case 3:
            //     hell();
            //     break;
        }
        room = next_room;
        if (player->hp <= 0)
        {
            exit = 2;
            printf("Игрок погиб.\n");
        }
    }
}

int main()
{
    Player *player = init_player(5, 20, 10);
    menu(player);
    free(player);
    return 0;
}
