#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "enemy.h"
#include "functions.h"
#include "mechanics.h"
#include "locations.h"

// Схватка
void dungeon_fight(Player *player, char *enemy_name, int enemy_hp, int enemy_damage, char *dungeon_state, int i, int fight_value_new, int fight_value_old)
{
    char random_value = rand() % 10 + 1;  // 1 <= random_value <= 10
    char fight_value = 0;
    if (dungeon_state[i] & 1 == 1)
    {
        fight_value = fight_value_old;
    }
    else
    {
        fight_value = fight_value_new;
    }
    if (random_value <= fight_value)
    {
        printf("!!! На игрока нападает %s.\n", enemy_name);
        Enemy *enemy = init_enemy(enemy_damage, enemy_hp, enemy_name);
        if (fight(player, enemy)) printf("*** Противник (%s) убит.\n", enemy_name);
        else printf("*** Игрок убит.\n");
        player_info(player);
        free(enemy);
    }
}

// Подземелья
int dungeon(char room, char *next_room, Player *player, char *dungeon_state)
{
    player_info(player);
    char choice = 0;

    // КРЫСА
    char rat_hp = 3, rat_dmg = 2;

    // ЧЕРНАЯ КРЫСА
    char blackrat_hp = 4, blackrat_dmg = 6;

    // ПОЛЫЙ РЫЦАРЬ
    char hollowknight_hp = 10, hollowknight_dmg = 4;

    // ЗАКЛЮЧЕННЫЙ
    char condemned_hp = 7, condemned_dmg = 3;

    // ГИГАНТСКИЙ ПАУК
    char spider_hp = 7, spider_dmg = 3;

    // ОГРОМНЫЙ ЧЕРВЬ
    char worm_hp = 11, worm_dmg = 2;

    // ГИГАНТСКА КРЫСА
    char bigrat_hp = 4, bigrat_dmg = 6;

    // СКЕЛЕТ
    char skeleton_hp = 21, skeleton_dmg = 5;

    switch(room)
    {
        case 0:
            // Описание комнаты
            printf("*** Помещение похоже на тюремную камеру. С потолка свисает скелет. Из помещения есть два выхода.\n");

            // Варианты действий в комнате
            printf("Пойти налево (1)\n");  // 0 -> 1
            printf("Пойти направо (2)\n");  // 0 -> 2

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 1;
                    break;
                case 2:
                    *next_room = 2;
                    break;
            }
            break;
        case 1:
            // Описание комнаты
            if (player->torch) printf("*** Длинный коридор.\n");
            else printf("*** Длинный коридор с тусклым факелом.\n");

            // Схватка
            dungeon_fight(player, "КРЫСА", rat_hp, rat_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Вернуться в тюремную камеру со скелетом (1)\n");  // 1 -> 0
            printf("Пройти в узкую щель в стене (2)\n");  // 1 -> 3
            if (player->hp > 0)
            {
                if (player->torch)
                {
                    printf("Пройти в проход, около которого подставка под факел (3)\n");  // 1 -> 4
                    printf("Осмотреть подставку под факел (4)\n");  // 1 -> 1
                }
                else
                {
                    printf("Пройти в проход, около которого висит факел (3)\n");  // 1 -> 4
                    printf("Взять факел (4)\n");  // 1 -> 1
                }
            }

            // Выбор игрока
            choice = validate_input(4);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 0;
                    break;
                case 2:
                    *next_room = 3;
                    break;
                case 3:
                    *next_room = 4;
                    break;
                case 4:
                    *next_room = 1;
                    if (player->torch)
                    {
                        printf("*** Железная скоба, вбитая в стену. Ничего особенного.\n");
                    }
                    else
                    {
                        player->torch = 1;  // Взять факел
                    }
                    break;
            }
            break;
        case 2:
            // Описание комнаты
            if (dungeon_state[2] & 2) printf("*** Полуосвещенная комната. В углу комнаты находится спуск вниз.\n");
            else printf("*** Полуосвещенная комната. Большую часть угла комнаты занимает плотная и огромная паутина.\n");

            // Схватка
            dungeon_fight(player, "КРЫСА", rat_hp, rat_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Вернуться в тюремную камеру со скелетом (1)\n");  // 2 -> 0
            printf("Пройти в освещенную комнату (2)\n");  // 2 -> 5
            if (player->torch)
            {
                if (dungeon_state[2] & 2)
                {
                    printf("Спуститься (3)\n");  // 2 -> 9
                }
                else
                {
                    printf("Сжечь паутину (3)\n");  // 2 -> 2
                    
                }
            }
            else
            {
                printf("Осмотреть паутину (3)\n");  // 2 -> 2
            }

            // Выбор игрока
            choice = validate_input(3);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 0;
                    break;
                case 2:
                    *next_room = 5;
                    break;
                case 3:
                    if (dungeon_state[2] & 2) *next_room = 9;
                    else *next_room = 2;
                    dungeon_state[2] |= 2;
                    break;
            }
            break;
        case 3:
            // Описание комнаты
            if (dungeon_state[3] & 2) printf("*** Каморка с разбитыми сосудами.\n");
            else printf("*** Что-то наподобие каморки с замшелыми глиняными сосудами.\n");

            // Схватка
            dungeon_fight(player, "КРЫСА", rat_hp, rat_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Протиснуться в щель в стене (1)\n");  // 3 -> 1
            printf("Пройти в массивную дверь (2)\n");  // 3 -> 6
            if (dungeon_state[3] & 2) printf("Осмотреть осколки сосудов (3)\n");
            else printf("Разбить сосуды (3)\n");  // 3 -> 3

            // Выбор игрока
            choice = validate_input(3);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 1;
                    break;
                case 2:
                    *next_room = 6;
                    break;
                case 3:
                    *next_room = 3;
                    if (!(dungeon_state[3] & 2))
                    {
                        char r = rand() % 2;
                        if (r)
                        {
                            // Схватка
                            dungeon_fight(player, "ЧЕРНАЯ КРЫСА", 4, 6, dungeon_state, 3, 5, 0);
                        }
                        else
                        {
                            printf("*** В сосудах ничего не было.\n");
                            dungeon_state[3] |= 2;
                        }
                    }
                    break;
            }
            break;
        case 4:
            // Описание комнаты
            if (player->torch) printf("*** Благодаря факелу комнату можно разглядеть. В углу комнаты стоит сундук.\n");
            else printf("*** Темная комната. Вряд ли получится ощупать ее наугад...\n");

            // Схватка
            dungeon_fight(player, "ЧЕРНАЯ КРЫСА", blackrat_hp, blackrat_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;
            
            // Варианты действий в комнате
            if (player->torch)
            {
                if (dungeon_state[4] & 2)
                {
                    printf("Открыть сундук (1)\n");  // 4 -> 4
                }
                else
                {
                    printf("Осмотреть пустой сундук (1)\n");  // 4 -> 4
                    dungeon_state[4] |= 2;
                }
            }
            else
            {
                printf("Двигаться вперед в темноту (1)\n");  // 4 -> 4
            }
            printf("Вернуться назад (2)\n");  // 4 -> 1

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 4;
                    if (player->torch)
                    {
                        if (player->cursed_sword)
                        {
                            printf("*** Пустой сундук.\n");
                        }
                        else
                        {
                            player->cursed_sword = 1;
                            printf("*** Игрок берет из сундука проклятый меч.\n");
                        }
                    }
                    else
                    {
                        printf("*** Ничего не получается нащупать.\n");
                    }
                    break;
                case 2:
                    *next_room = 1;
                    break;
            }
            break;
        case 5:
            // Описание комнаты
            printf("*** Длинная комната с высоким потолком. Через узкие окна наверху пробивается свет. На одном конце проход с паутиной, на другом - решетка, около которой стоят доспехи. По бокам расположены две двери: массивная железная и хлипкая деревянная.\n");

            // Схватка
            dungeon_fight(player, "ПОЛЫЙ РЫЦАРЬ", hollowknight_hp, hollowknight_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Войти в проход с паутиной (1)\n");  // 5 -> 2
            if (dungeon_state[5] & 2) printf("Войти в арку с открытой решеткой (2)\n");  // 5 -> 14
            else printf("Осмотреть решетку (2)\n");  // 5 -> 5
            printf("Войти в железную дверь (3)\n");  // 5 -> 6
            printf("Войти в деревянную дверь (4)\n");  // 5 -> 38

            // Выбор игрока
            choice = validate_input(4);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 2;
                    break;
                case 2:
                    if (dungeon_state[5] & 2)
                    {
                        *next_room = 14;
                    }
                    else
                    {
                        *next_room = 5;
                        printf("*** Решетка выглядит также сурово, как стоящие рядом доспехи. Ее открыть не получится, так же как и пролезть через прутья.\n");
                    }
                    break;
                case 3:
                    *next_room = 6;
                    break;
                case 4:
                    *next_room = 38;
                    break;
            }
            break;
        case 6:
            // Описание комнаты
            printf("*** Огромный зал высотой в несколько человеческих ростов. Через пробитый потолок пробивается яркий свет, он освещает обломки потолка, лежащие на полу. По краям зала стоят чаши с огнем.\n");

            // Схватка
            dungeon_fight(player, "КРЫСА", rat_hp, rat_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Войти в освещенное помещение (1)\n");  // 6 -> 5
            printf("Войти в каморку (2)\n");  // 5 -> 3
            printf("Войти в комнату без двери (3)\n");  // 5 -> 7
            printf("Войти в дверь с шестеренкой (4)\n");  // 5 -> 8

            // Выбор игрока
            choice = validate_input(4);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 5;
                    break;
                case 2:
                    *next_room = 3;
                    break;
                case 3:
                    *next_room = 7;
                    break;
                case 4:
                    *next_room = 8;
                    break;
            }
            break;
        case 7:
            // Описание комнаты
            printf("*** Вход в комнату разбит. Дверь от помещения лежит недалеко в зале. В одной из стенок есть просвет в соседнюю комнату. Эта стенка кажется ненадежной.\n");

            // Схватка
            dungeon_fight(player, "КРЫСА", rat_hp, rat_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Выйти в зал (1)\n");  // 7 -> 6
            if (dungeon_state[7] & 2) printf("Войти в разбитый проход (2)\n");  // 7 -> 17
            else printf("Попытаться пробить стенку (2)\n");  // 7 -> 7

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 6;
                    break;
                case 2:
                    if (dungeon_state[7] & 2)
                    {
                        *next_room = 17;
                    }
                    else
                    {
                        char r = rand() % 2;
                        if (r)
                        {
                            dungeon_state[7] |= 2;
                            printf("*** Стенка разбита, можно пройти дальше.\n");
                        }
                        else
                        {
                            hit_player(player, 1);
                            printf("*** Стенка оказалсь крепче, чем казалось.\n");
                        }
                    }
                    break;
            }
            break;
        case 8:
            // Описание комнаты
            printf("*** Некоторое подобие технического помещения неизвестного назначения. В комнате несколько разных механизмов и рычагов.\n");

            // Схватка
            // dungeon_fight(player, "КРЫСА", 2, 3, dungeon_state, 6, 5, 1);

            // Варианты действий в комнате
            printf("Вернуться в зал (1)\n");  // 8 -> 6
            if (dungeon_state[5] & 2) printf("Осмотреть механизмы (2)\n");  // 8 -> 8
            else printf("Опустить один из рычагов (2)\n");  // 8 -> 8

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 6;
                    break;
                case 2:
                    *next_room = 8;
                    if (dungeon_state[5] & 2)
                    {
                        printf("*** Шестерни, диски, валы, покрытые толстенным слоем пыли.\n");
                    }
                    else
                    {
                        dungeon_state[5] |= 2;
                        printf("*** Слышен звук работающего механизма, который затихает через пару секунд.\n");
                    }
                    break;
            }
            break;
        case 9:
            // Описание комнаты
            printf("*** Очень темный подвал. Пахнет сыростью. За стенками слышны странные звуки. Как будто кто-то ползает.\n");

            // Схватка
            dungeon_fight(player, "ГИГАНТСКИЙ ПАУК", spider_hp, spider_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Подняться из подвала (1)\n");  // 9 -> 2
            printf("Пройти во 2 комнату подвала (2)\n");  // 9 -> 10

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 2;
                    break;
                case 2:
                    *next_room = 10;
                    break;
            }
            break;
        case 10:
            // Описание комнаты
            printf("*** Благодаря факелу можно разглядеть влажные кирпичи стен и сырую землю под ногами.\n");

            // Схватка
            dungeon_fight(player, "ГИГАНТСКИЙ ПАУК", spider_hp, spider_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Пройти в 1 комнату подвала (1)\n");  // 10 -> 9
            printf("Пройти в 3 комнату подвала (2)\n");  // 10 -> 11

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 9;
                    break;
                case 2:
                    *next_room = 11;
                    break;
            }
            break;
        case 11:
            // Описание комнаты
            if (dungeon_state[11] & 2) printf("*** Эта комната выглядит безопасной. Ступеньки освещает комната библиотеки.\n");
            else printf("*** Эта комната выглядит безопасной. Видны ступеньки, ведущие наверх. Около них есть рычаг.\n");

            // Схватка

            // Варианты действий в комнате
            printf("Спуститься ниже (1)\n");  // 11 -> 12
            if (dungeon_state[11] & 2) printf("Подняться по ступенькам в библиотеку (2)\n");  // 11 -> 15
            else printf("Опустить рычаг (2)\n");  // 11 -> 11
            printf("Пройти во 2 комнату подвала (3)\n");  // 11 -> 10

            // Выбор игрока
            choice = validate_input(3);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 12;
                    break;
                case 2:
                    if (dungeon_state[11] & 2)
                    {
                        *next_room = 15;
                    }
                    else
                    {
                        *next_room = 11;
                        printf("*** Тяжелый рычаг длиной с предплечье. Поддался с большим трудом.\n");
                        dungeon_state[11] |= 2;
                    }
                    break;
                case 3:
                    *next_room = 10;
                    break;
            }
            break;
        case 12:
            // Описание комнаты
            printf("*** В помещении по пояс воды. Даже не воды, а тяжелой жижы, в которой плавают доски, плесень и много другой дряни. Отвратительно пахнет.\n");

            // Схватка
            dungeon_fight(player, "ОГРОМНЫЙ ЧЕРВЬ", worm_hp, worm_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Пройти в другое затопленное помещение (1)\n");  // 12 -> 13
            printf("Подняться (2)\n");  // 12 -> 11

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 13;
                    break;
                case 2:
                    *next_room = 11;
                    break;
            }
            break;
        case 13:
            // Описание комнаты
            printf("*** На мокрых стенах висит странная биомасса. И не одна. Судя по звукам и колыханиям, под водой таких штук еще больше.\n");

            // Схватка
            dungeon_fight(player, "ОГРОМНЫЙ ЧЕРВЬ", worm_hp, worm_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Пройти в другой затопленное помещение (1)\n");  // 13 -> 12
            if (dungeon_state[13] & 2) printf("Подняться и выйти в пробитый проход (2)\n");  // 13 -> 33
            else printf("Сверху непрочная стена, попытаться пробить (2)\n");

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 12;
                    break;
                case 2:
                    if (dungeon_state[13] & 2)
                    {
                        *next_room = 33;
                    }
                    else
                    {
                        char r = rand() % 2;
                        if (r)
                        {
                            *next_room = 33;
                            dungeon_state[13] |= 2;
                            printf("*** Вместе с выбитыми кирпичами вы вываливаетесь в маленькую каморку.\n");
                        }
                        else
                        {
                            hit_player(player, 1);
                            printf("*** Стена все еще держится.\n");
                        }
                    }
                    break;
            }
            break;
        case 14:
            // Описание комнаты
            printf("*** Освещенное помещение. Свет пробивается через окна под потолком. Около стен стоят доспехи. На них не так много пыли, как на остальных поверхностях.\n");

            // Схватка
            dungeon_fight(player, "ПОЛЫЙ РЫЦАРЬ", hollowknight_hp, hollowknight_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Пройти в библиотеку (1)\n");  // 14 -> 15
            if (dungeon_state[5] & 2) printf("Пройти в арку с открытой решеткой (2)\n");  // 14 -> 5
            else printf("Опустить рычаг (2)\n");

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 15;
                    break;
                case 2:
                    if (dungeon_state[5] & 2)
                    {
                        *next_room = 5;
                    }
                    else
                    {
                        *next_room = 14;
                        dungeon_state[5] |= 2;
                        printf("*** Слышен скрежет металла и звук механизма. Решетка громоздко поднимается и застывает в верхнем открытом положении.\n");
                    }
                    break;
            }
            break;
        case 15:
            // Описание комнаты
            if (dungeon_state[11] & 2) printf("*** Библиотека. Сверху висят две раскошные люстры. Помещение заставлено шкафами с аккуратно составленными книгами. За одним отъехавшим шкафом есть спуск вниз.\n");
            else printf("*** Библиотека. Сверху висят две раскошные люстры. Помещение заставлено шкафами с аккуратно составленными книгами.\n");

            // Схватка

            // Варианты действий в комнате
            printf("Пройти в высокую широкую арку (1)\n");  // 15 -> 16
            printf("Открыть позолоченную дверь (2)\n");  // 14 -> 36
            printf("Пройти в освещенную комнату с доспехами (3)\n");  // 15 -> 14

            // Выбор игрока
            choice = validate_input(3);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 16;
                    break;
                case 2:
                    *next_room = 36;
                    break;
                case 3:
                    *next_room = 14;
                    break;
            }
            break;
        case 16:
            // Описание комнаты
            printf("*** Большой зал библиотеки высотой с три этажа. Стены заставлены шкафами, у которых стоят несколько длинных лестниц. На потолке висят четыре люстры с блестящими украшениями.\n");

            // Схватка
            // dungeon_fight(player, "ПОЛЫЙ РЫЦАРЬ", 10, 4, dungeon_state, 5, 5, 1);
            char r = rand() % 2;
            if (r)
            {
                printf("*** Ощущается чье-то присутствие.\n");
            }
            else
            {
                hit_player(player, 1);
                printf("*** В игрока врезается книга, прилетевшая откуда-то из зала с высокой скоростью.\n");
            }

            // Варианты действий в комнате
            printf("Пройти в позолоченную дверь (1)\n");  // 16 -> 36
            printf("Пройти в меньшее помещение библиотеки (2)\n");  // 16 -> 15
            printf("Выйти из библиотеки в деревянную дверцу (3)\n");  // 16 -> 34

            // Выбор игрока
            choice = validate_input(3);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 36;
                    break;
                case 2:
                    *next_room = 15;
                    break;
                case 3:
                    *next_room = 34;
                    break;
            }
            break;
        case 17:
            // Описание комнаты
            printf("*** Странное помещение. На стене написано 1С. Из помещения ведет одна дверь с табличкой 2С.\n");

            // Схватка

            // Варианты действий в комнате
            printf("Пройти в дверь 2С (1)\n");  // 17 -> 20
            printf("Вернуться в разбитый проход (2)\n");  // 17 -> 7

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 20;
                    break;
                case 2:
                    *next_room = 7;
                    break;
            }
            break;
        case 18:
            // Описание комнаты
            printf("*** Сквозь кровь на стене видна табличка 1В.\n");

            // Схватка
            dungeon_fight(player, "ЗАКЛЮЧЕННЫЙ", condemned_hp, condemned_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Вернуться в 2В (1)\n");  // 17 -> 20

            // Выбор игрока
            choice = validate_input(1);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 21;
                    break;
            }
            break;
        case 19:
            // Описание комнаты
            printf("*** .\n");

            // Схватка
            dungeon_fight(player, "ЗАКЛЮЧЕННЫЙ", condemned_hp, condemned_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Пройти в 2В (1)\n");  // 17 -> 20

            // Выбор игрока
            choice = validate_input(1);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 21;
                    break;
            }
            break;
        case 20:
            // Описание комнаты
            printf("*** Похоже, это уже настоящее тюремное помещение. Но почему камеры связаны друг с другом? Это камера 2С.\n");

            // Схватка
            dungeon_fight(player, "ЗАКЛЮЧЕННЫЙ", condemned_hp, condemned_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Вернуться в 1С (1)\n");  // 20 -> 17
            printf("Пройти в 2В (2)\n");  // 20 -> 21

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 17;
                    break;
                case 2:
                    *next_room = 21;
                    break;
            }
            break;
        case 21:
            // Описание комнаты
            printf("*** Еще одна камера. 2В\n");

            // Схватка
            dungeon_fight(player, "ЗАКЛЮЧЕННЫЙ", condemned_hp, condemned_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Пройти в 2С (1)\n");  // 21 -> 20
            printf("Пройти в 3В (2)\n");  // 21 -> 24
            printf("Пройти в 2А (3)\n");  // 21 -> 22
            printf("Пройти в 1В (4)\n");  // 21 -> 18

            // Выбор игрока
            choice = validate_input(4);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 20;
                    break;
                case 2:
                    *next_room = 24;
                    break;
                case 3:
                    *next_room = 22;
                    break;
                case 4:
                    *next_room = 18;
                    break;
            }
            break;
        case 22:
            // Описание комнаты
            printf("*** Странно, что здесь относительно светло. На стенках камер висят факелы, защищенные металлической решеткой. Даже если факел был бы нужен, вряд ли получилось бы его достать.\n");

            // Схватка
            dungeon_fight(player, "ЗАКЛЮЧЕННЫЙ", condemned_hp, condemned_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Пройти в 2В (1)\n");  // 22 -> 21
            printf("Пройти в 1А (2)\n");  // 22 -> 22

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 21;
                    break;
                case 2:
                    *next_room = 22;
                    printf("*** Дверь не поддается. За ней слышно тихое рычание.\n");
                    break;
            }
            break;
        case 23:
            // Описание комнаты
            printf("*** 3С. В глаза бросается позолоченная дверь, ведущая из камер.\n");

            // Схватка
            dungeon_fight(player, "ЗАКЛЮЧЕННЫЙ", condemned_hp, condemned_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Пройти в позолоченную дверь (1)\n");  // 23 -> 36
            printf("Пройти в 4В (2)\n");  // 23 -> 26

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 36;
                    break;
                case 2:
                    *next_room = 26;
                    break;
            }
            break;
        case 24:
            // Описание комнаты
            printf("*** Пол в крови. Что-то попадается под ноги: это тушка крысы. Комната 3В.\n");

            // Схватка
            dungeon_fight(player, "ЗАКЛЮЧЕННЫЙ", condemned_hp, condemned_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Пойти по кровавому следу в 3А (1)\n");  // 24 -> 25
            printf("Пройти в 2В (2)\n");  // 24 -> 21

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 25;
                    break;
                case 2:
                    *next_room = 21;
                    break;
            }
            break;
        case 25:
            // Описание комнаты
            printf("*** 3А. Вместо факелов с решетками на полу стоит чаша с тусклой почти догоревшей свечой. Рядом мертвая крыса.\n");

            // Схватка
            dungeon_fight(player, "ЗАКЛЮЧЕННЫЙ", condemned_hp, condemned_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Пройти в 4А (1)\n");  // 25 -> 28
            printf("Пройти в 3В (2)\n");  // 25 -> 24

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 28;
                    break;
                case 2:
                    *next_room = 24;
                    break;
            }
            break;
        case 26:
            // Описание комнаты
            printf("*** 4С. В прошлых камерах пол был из кирпича или плитки. Здесь половина пола без кладки, в земле вырыта яма под одну из соседних комнат.\n");

            // Схватка
            dungeon_fight(player, "ЗАКЛЮЧЕННЫЙ", condemned_hp, condemned_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Проползти под заевшей дверью в 5С (1)\n");  // 26 -> 29
            printf("Пройти в 3С (2)\n");  // 26 -> 23
            printf("Пройти в 4В (3)\n");  // 26 -> 27

            // Выбор игрока
            choice = validate_input(3);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 29;
                    break;
                case 2:
                    *next_room = 23;
                    break;
                case 3:
                    *next_room = 27;
                    break;
            }
            break;
        case 27:
            // Описание комнаты
            if (player->torch) printf("*** Хорошо, что есть факел. Нет нужды вглядываться в каждый угол.\n");
            else printf("*** 4В. Здесь нет факела. Очень темно. Из какой-то камеры слышно рычание.\n");

            // Схватка
            dungeon_fight(player, "ЗАКЛЮЧЕННЫЙ", condemned_hp, condemned_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            if (player->torch)
            {
                printf("Пройти в 4С (1)\n");  // 27 -> 26
                printf("Пройти в 4А (2)\n");  // 27 -> 28
            }
            else
            {
                printf("Цифры не видно, но можно разглядеть букву А. Войти (1)\n");  // 27 -> 26
                printf("Табличку не разглядеть. Войти (2)\n");  // 27 -> 28
            }
            

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 28;
                    break;
                case 2:
                    *next_room = 26;
                    break;
            }
            break;
        case 28:
            // Описание комнаты
            printf("*** 4А. На полу лежат сброшенные кандалы и цепи.\n");

            // Схватка
            dungeon_fight(player, "ЗАКЛЮЧЕННЫЙ", condemned_hp, condemned_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("На двери висят еще одни кандалы. Войти в 5А (1)\n");  // 28 -> 31
            printf("Пройти в 4В (2)\n");  // 28 -> 27
            printf("Пройти в 3А (3)\n");  // 28 -> 25
            

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 31;
                    break;
                case 2:
                    *next_room = 27;
                    break;
                case 3:
                    *next_room = 25;
                    break;
            }
            break;
        case 29:
            // Описание комнаты
            printf("*** Крысиные тушки, сложенные в огромную кучу. Вокруг стоят несколько свечей догорающих свечей.\n");

            // Схватка
            dungeon_fight(player, "ЗАКЛЮЧЕННЫЙ", condemned_hp, condemned_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Вернуться назад (1)\n");  // 29 -> 26
            

            // Выбор игрока
            choice = validate_input(1);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 26;
                    break;
            }
            break;
        case 30:
            // Описание комнаты
            printf("*** 5В. Пламя факела за решеткой колышется. Из-за одной из дверей веет сквозняком.\n");

            // Схватка

            // Варианты действий в комнате
            printf("Пойти на сквозняк и открыть дверь (1)\n");  // 30 -> 32
            printf("Войти в 5А (2)\n");  // 30 -> 31
            

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 32;
                    break;
                case 2:
                    *next_room = 31;
                    break;
            }
            break;
        case 31:
            // Описание комнаты
            printf("*** На полу лежит табличка 5А. В середине комнаты пустой стул. Рядом лежат сломанные кандалы.\n");

            // Схватка
            dungeon_fight(player, "ЗАКЛЮЧЕННЫЙ", condemned_hp, condemned_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Войти в дверь без таблички (1)\n");  // 31 -> 30
            printf("Войти в 4А (2)\n");  // 31 -> 28
            

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 30;
                    break;
                case 2:
                    *next_room = 28;
                    break;
            }
            break;
        case 32:
            // Описание комнаты
            printf("*** Комната похожа на погреб. Под потолком некоторое подобие отверстий, через которые веет сквозняком. В углу комнаты стоит много бочек.\n");

            // Схватка
            dungeon_fight(player, "ГИГАНТСКАЯ КРЫСА", bigrat_hp, bigrat_dmg, dungeon_state, room, 10, 0);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            if (dungeon_state[32] & 2) printf("Выйти в дверь с огромным кольцом (1)\n");  // 32 -> 35
            else printf("Снять засов с двери и пройти в следующую комнату (1)\n");
            printf("Пойти в лабиринт с камерами заключенных (2)\n");  // 32 -> 30
            

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 35;
                    if (!(dungeon_state[32])) dungeon_state[32] |= 2;
                    break;
                case 2:
                    *next_room = 30;
                    break;
            }
            break;
        case 33:
            // Описание комнаты
            printf("*** В углу стоят метлы и лопаты, дверь приоткрыта.\n");

            // Схватка
            dungeon_fight(player, "КРЫСА", rat_hp, rat_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            printf("Выйти в приоткрытую дверь (1)\n");  // 33 -> 34
            if (dungeon_state[13] & 2) printf("Спуститься (2)\n");  // 33 -> 13
            else printf("На противоположной стене нет нескольких кирпичей. Выбить стену (2)\n");  // 33 -> 13, 33

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 34;
                    break;
                case 2:
                    if (dungeon_state[13] & 2)
                    {
                        *next_room = 13;
                    }
                    else
                    {
                        char r = rand() % 2;
                        if (r)
                        {
                            *next_room = 13;
                            dungeon_state[13] |= 2;
                            printf("*** Стена пробита. Вы слетаете вместе с кирпичами вниз по ступенькам в полузатопленное помещение.\n");
                        }
                        else
                        {
                            hit_player(player, 1);
                            printf("*** Кирпичи сдвинулись, но все еще в стене.\n");
                        }
                    }
                    break;
            }
            break;
        case 34:
            // Описание комнаты
            printf("*** Комната излучает некоторое спокойствие. Кажется, здесь безопасно. На потолке квадратное отверстие, сквозь которое падает свет и освещает помещение.\n");

            // Схватка

            // Варианты действий в комнате
            printf("Войти в железную дверь (1)\n");  // 34 -> 35
            printf("Войти в приоткрытую дверь с инвентарем (2)\n");  // 34 -> 33
            printf("Войти в дверь с барельефом книги (3)\n");  // 33 -> 16

            // Выбор игрока
            choice = validate_input(3);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 35;
                    break;
                case 2:
                    *next_room = 33;
                    break;
                case 3:
                    *next_room = 16;
                    break;
            }
            break;
        case 35:
            // Описание комнаты
            printf("*** Около стен стоят скамьи, на которых сидят пустые доспехи, склонив головы. Самая большая дверь закрыта, но в ней есть замочная скважина.\n");

            // Схватка

            // Варианты действий в комнате
            printf("Войти в комнату с алтарем (1)\n");  // 35 -> 34
            printf("Открыть дверь в погреб (2)\n");  // 35 -> 32, 35
            if (player->key) printf("Выйти из подземелий (3)\n");  // 35 -> WIN
            else printf("Осмотреть дверь со скважиной (3)\n");  // 35 -> 35

            // Выбор игрока
            choice = validate_input(3);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 34;
                    break;
                case 2:
                    if (dungeon_state[32] & 2)
                    {
                        *next_room = 32;
                    }
                    else
                    {
                        *next_room = 35;
                        printf("*** Дверь не поддается.\n");
                    }
                    break;
                case 3:
                    if (player->key)
                    {
                        printf("WIN\n");
                    }
                    else
                    {
                        printf("*** На двери выгравирован символ со змеем и черепом.\n");
                    }
                    break;
            }
            break;
        case 36:
            // Описание комнаты
            if (dungeon_state[36] & 2) printf("*** Просторный освещенный зал с троном.\n");
            printf("*** Просторный освещенный зал. С трона встает скелет.\n");

            // Схватка
            dungeon_fight(player, "СКЕЛЕТ", skeleton_hp, skeleton_dmg, dungeon_state, room, 10, 0);
            if (player->hp <= 0) return 0;

            printf("*** Получен ключ от подземелий\n");
            player->key = 1;
            dungeon_state[36] |= 2;

            // Варианты действий в комнате
            printf("Малый зал библиотеки (1)\n");  // 35 -> 34
            printf("Большой зал библиотеки (2)\n");  // 35 -> 32
            printf("Войти в комнату за троном (3)\n");  // 35 -> 35

            // Выбор игрока
            choice = validate_input(3);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 15;
                    break;
                case 2:
                    *next_room = 16;
                    break;
                case 3:
                    *next_room = 37;
                    // printf("\n");
                    break;
            }
            break;
        case 37:
            // Описание комнаты
            printf("*** q\n");

            // Схватка

            // Варианты действий в комнате
            printf("Зал (1)\n");  // 37 -> 36

            // Выбор игрока
            choice = validate_input(1);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 36;
                    break;
            }
            break;
        case 38:
            // Описание комнаты
            if (player->torch) printf("*** С потолка редко что-то капает. Напротив двери стоит сундук.\n");
            else printf("*** Очень темно. Только слышны звуки капель.\n");

            // Схватка
            dungeon_fight(player, "ЧЕРНАЯ КРЫСА", blackrat_hp, blackrat_dmg, dungeon_state, room, 5, 1);
            if (player->hp <= 0) return 0;

            // Варианты действий в комнате
            if (player->torch)
            {
                if (dungeon_state[2] & 2) printf("Осмотреть открытый сундук (1)\n");
                else printf("Открыть сундук (1)\n");
            }
            else
            {
                printf("Попытаться найти что-нибудь в темноте (1)\n");
            }
            printf("Вернуться назад (2)\n");  // 38 -> 5

            // Выбор игрока
            choice = validate_input(2);

            // Результат выбора игрока
            switch(choice)
            {
                case 1:
                    *next_room = 38;
                    if (player->torch)
                    {
                        if (dungeon_state[2] & 2)
                        {
                            printf("*** Кроме старых тряпок в сундуке больше ничего нет.\n");
                        }
                        else
                        {
                            dungeon_state[2] |= 2;
                            player->cursed_ring = 1;
                            printf("*** Найдено проклятое кольцо.\n");
                        }
                    }
                    else
                    {
                        printf("*** Безуспешно.\n");
                    }
                    break;
                case 2:
                    *next_room = 5;
                    break;
            }
            break;
    }

    // Событие: комната посещена
    if (!(dungeon_state[room] & 1)) dungeon_state[room] |= 1;

    // Зарядка кольца
    if (player->ring < 3) player->ring++;
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
