#include <stdio.h>

#include "player.h"
#include "locations.h"

// Подземелья, описание
void dungeon(char room, Player *player, char *dungeon_state)
{
    switch(room)
    {
        case 0:
            printf("Помещение похоже на тюремную камеру. С потолка свисает скелет. Из помещения есть два выхода.\n");
            printf("Пойти налево (1)\n");  // 0 -> 1
            printf("Пойти направо (2)\n");  // 0 -> 2
            break;
        case 1:
            if (player->inventory & 0b00000001 == 0b00000001)
            {
                printf("Длинный коридор.\n");
                printf("Вернуться с тюремную камеру со скелетом (1)\n");  // 1 -> 0
                printf("Пройти в узкую щель в стене (2)\n");  // 1 -> 3
                printf("Пройти в проход, около которого подставка под факел (3)\n");  // 1 -> 4
                printf("Осмотреть подставку под факел (4)\n");  // 1 -> 1
            }
            else
            {
                printf("Длинный коридор с тусклым факелом.\n");
                printf("Вернуться в тюремную камеру со скелетом (1)\n");  // 1 -> 0
                printf("Пройти в узкую щель в стене (2)\n");  // 1 -> 3
                printf("Пройти в проход, около которого висит факел (3)\n");  // 1 -> 4
                printf("Взять факел (4)\n");  // 1 -> 1
            }
            
            break;
        case 2:
            if (player->inventory & 0b00000001 == 0b00000001)
            {
                printf("Полуосвещенная комната. Большую часть угла комнаты занимает плотная и огромная паутина.\n");
                printf("Вернуться в тюремную камеру со скелетом (1)\n");  // 2 -> 0
                printf("Пройти в освещенную комнату (2)\n");  // 2-> 
                if (dungeon_state[2] & 0b00000001 == 0b00000001)
                {
                    printf("Спуститься (3)\n");  // 2 -> 
                }
                else
                {
                    printf("Сжечь паутину (3)\n");  // 2 -> 
                    dungeon_state[2] |= 0b00000001;
                }
                
            }
            else
            {
                printf("Полуосвещенная комната. Большую часть угла комнаты занимает плотная и огромная паутина.\n");
                printf("Вернуться в тюремную камеру со скелетом (1)\n");
                printf("Пройти в освещенную комнату (2)\n");
                printf("Осмотреть паутину (3)\n");
            }
            break;
        case 3:
            break;
        case 4:
            if (player->inventory & 0b00000001 == 0b00000001)
            {
                printf("Благодаря факелу комнату можно разглядеть. В углу комнаты стоит сундук.\n");
                printf("Открыть сундук (1)\n");  // 4 -> 4
                printf("Вернуться назад (2)\n");  // 4 -> 1
            }
            else
            {
                printf("Темная комната. Вряд ли получится ощупать ее наугад...\n");
                printf("Двигаться вперед в темноту (1)\n");  // 4 -> 4
                printf("Вернуться назад (2)\n");  // 4 -> 1
            }
            break;
    }
}

// Подземелья, количество вариантов в комнате
char dungeon_choice_max(char room)
{
    char choice_max = 0;
    switch(room)
    {
        case 0:
            choice_max = 2;
            break;
        case 1:
            choice_max = 4;
            break;
        case 2:
            choice_max = 3;
            break;
        case 4:
            choice_max = 2;
            break;
    }
    return choice_max;
}

// Подземелья, следующая комната
char dungeon_next_room(char room, char choice, Player *player)
{
    char next_room = 0;
    switch(room)
    {
        case 0:
            switch(choice)
            {
                case 1:
                    next_room = 1;
                    break;
                case 2:
                    next_room = 2;
                    break;
            }
            break;
        case 1:
            switch(choice)
            {
                case 1:
                    next_room = 0;
                    break;
                case 2:
                    next_room = 3;
                    break;
                case 3:
                    next_room = 4;
                    break;
                case 4:
                    if (player->inventory & 1 == 1)
                    {
                        printf("*** Железная скоба, вбитая в стену. Ничего особенного.\n");
                    }
                    else
                    {
                        player->inventory |= 0b00000001;
                    }
                    next_room = 1;
                    break;
            }
            break;
        case 2:
            switch(choice)
            {
                case 1:
                    next_room = 0;
                    break;
                case 2:
                    next_room = 2;
                    break;
                case 3:
                    next_room = 2;
                    break;
            }
            break;
        case 4:
            switch(choice)
            {
                case 1:
                    next_room = 4;
                    break;
                case 2:
                    next_room = 1;
                    break;
            }
            break;
    }
    return next_room;
}

// Деревни и окрестности
void village()
{

}

// Заснеженная гора
void mountain()
{

}

// Ад
void hell()
{

}
