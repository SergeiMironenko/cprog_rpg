#include <stdio.h>
#include <stdlib.h>

#include "player.h"  // Функции игрока
#include "enemy.h"  // Функции противника
#include "mechanics.h"  // Игровые функции, механики
#include "functions.h"  // Неигровые функции
#include "locations.h"  // Описание локаций

void menu(Player *player)
{
    char c = '\n';
    char exit = 0;  // 0 - игра, 1 - выход, 2 - проигрыш
    char location = 0;
    char room = 0;
    char choice = 0;
    char choice_max = 0;
    char dungeon_state[20] = {0};
    while (!exit)
    {
        player_info(player);

        switch(location)
        {
            case 0:
                dungeon(room, player, dungeon_state);
                choice_max = dungeon_choice_max(room);
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
        choice = validate_input(choice_max);
        if (!choice) exit = 1;
        else room = dungeon_next_room(room, choice, player);
    }
}

int main()
{
    Player *player = init_player(5, 20, 10);
    menu(player);
    free(player);
    return 0;
}
