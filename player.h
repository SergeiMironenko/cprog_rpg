#ifndef PLAYER_H_
#define PLAYER_H_

typedef struct Player
{
    int hp;
    int max_hp;
    int damage;
    int luck;
    char inventory;
} Player;

Player *init_player(int damage, int max_hp, int luck);  // Инициализация игрока
void hit_player(Player *player, int damage);  // Получение урона игроком
void player_info(Player *player);  // Вывод информации об игроке

#endif  // PLAYER_H_
