#ifndef LOCATIONS_H_
#define LOCATIONS_H_

int dungeon(char room, char *next_room, Player *player, char *dungeon_state);  // Подземелья, описание
char dungeon_choice_max(char room);  // Подземелья, количество вариантов в комнате
char dungeon_next_room(char room, char choice, Player *player, char *dungeon_state);  // Подземелья, следующая комната

#endif  // LOCATIONS_H_
