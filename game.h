#ifndef game_h
#define game_h

#include "MKL46Z4.h"
#include "slcd.h"

#define NUMBEROFPLAYERS 2
#define DICE 4
#define VALUES 6
#define CATEGORIES 7
#define ROLLS 3

typedef struct s_player
{
	uint8_t Score;
	uint8_t Table[DICE];
	uint8_t iterator;// 0 to 3/
	uint8_t ValuesOfDice[VALUES];
	uint8_t Category;
	void (*ledOn)(void);
	void (*ledOff)(void);
} player;

//Global Variables

//extern volatile player Players[NUMBEROFPLAYERS];
extern volatile player * current_player;

//Functions

void Game(volatile player * Players);
//Move functions
void Move(volatile player * player_ptr);
void Roll(volatile player *player_ptr);
void ClearTable(volatile player *player_ptr);
void DisplayTable(volatile player *player_ptr);
//Score Counting functions
void ClearValuesOfDice(volatile player *player_ptr);
void CountDice(volatile player *player_ptr);
uint8_t Value2Index(volatile player *player_ptr, uint8_t value);
uint8_t Max(volatile player *player_ptr);
void CountScore(volatile player *player_ptr);


#endif
