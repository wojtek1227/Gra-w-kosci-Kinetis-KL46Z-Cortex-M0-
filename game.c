#include "game.h"

void Game(volatile player * Players)
{
	uint8_t i;
	for(i = 0;i < NUMBEROFPLAYERS;i++)
  {
		current_player = Players + i;
		Move(current_player);
  }
}

void Move(volatile player * player_ptr)
{
	uint8_t i;
	player_ptr->ledOn();
	ClearTable(player_ptr);
	for(i = 0;i < ROLLS;i++)
  {
		player_ptr->iterator = 0;
		Roll(player_ptr);
  }
	while (player_ptr->iterator < 5) {}; //
	player_ptr->ledOff();
}

void Roll(volatile player *player_ptr)
{
	while (player_ptr->iterator < 4)
  {
		DisplayTable(player_ptr);
		slcdDotsOff();
		if (player_ptr->iterator < 4)
		{
			slcdSetDot(1,player_ptr->iterator + 1);
		}
  }
}
void ClearTable(volatile player *player_ptr)
{
	/*Clears Table*/
	uint8_t i;
	for(i = 0;i < DICE;i++)
  {
		player_ptr->Table[i] = 0;
  }
}

void DisplayTable(volatile player *player_ptr)
{
	uint8_t i;
	for(i = 0;i < DICE;i++)
  {
		slcdSet(player_ptr->Table[i],i+1);
  }
}

void ClearValuesOfDice(volatile player *player_ptr)
{
	uint8_t i;
	for(i = 0;i < VALUES;i++)
  {
		player_ptr->ValuesOfDice[i] = 0;
  }
}

void CountDice(volatile player *player_ptr)
{
	uint8_t i, CurrentValue;
	ClearValuesOfDice(player_ptr);
	for(i = 0;i < DICE;i++)
  {
		CurrentValue = player_ptr->Table[i];
		player_ptr->ValuesOfDice[CurrentValue - 1] += 1;
  }
}

uint8_t Value2Index(volatile player *player_ptr, uint8_t value)
{
	//This function is looking for a value in array and returns its index
	uint8_t index, i;
	for(i = 0;i < VALUES;i++)
  {
		if (player_ptr->ValuesOfDice[i] == value)
		{
			index = i;
		}
  }
	return index;
}

uint8_t Max(volatile player *player_ptr)
{
	uint8_t max, i;
	volatile uint8_t *Tab = player_ptr->ValuesOfDice;
	for(max = 0, i = 0;i < VALUES;i++)
  {
		if (max <= *(Tab + i))
		{
			max = *(Tab + i);
		}
  }
	return max;
}

void CountScore(volatile player *player_ptr)
{
	uint8_t max;
	max = Max(player_ptr);
	switch (max)
  {
  	case 4://We're looking for Four Of A Kind
  		break;
  	case 3://We're looking for Three Of A Kind
  		break;
		case 2://We're looking for Two Pairs or Pair
  		break;
		case 1://We're looking for any of Straights
  		break;
  	default:
  		break;
  }
	
}
