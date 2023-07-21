#ifndef PLAYER_H_
#define PLAYER_H_

typedef struct Player
{
    char hp;
    char max_hp;
    char damage;
    char magic;

    char cursed_damage;
    char cursed_magic;

    // Инвентарь
    char heal;
    char torch;
    char cursed_sword;
    char cursed_ring;
    char key;
    char ring;
} Player;

Player *init_player(char damage, char max_hp, char magic);  // Инициализация игрока
void hit_player(Player *player, char damage);  // Получение урона игроком
void player_info(Player *player);  // Вывод информации об игроке

#endif  // PLAYER_H_
