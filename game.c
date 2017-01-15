#include "game.h"

void Game(volatile player * Players)
{
	uint8_t i;
	for(i = 0;i < NUMBEROFPLAYERS;i++) {
		
		current_player = Players + i;
		Move(current_player);
		CountScore(current_player);

  }
	i=WhoWon(Players);
	DisplayWinner(i);
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

uint8_t CountPairs(volatile player *player_ptr)
{
	//This function is looking for a value in array and returns its index
	uint8_t i, count;
	count = 0;
	for(i = 0;i < VALUES;i++)
  {
		if (player_ptr->ValuesOfDice[i] == 2)
		{
			count ++;
		}
  }
	return count; //zwraca 0 jak nic nie znalazlo, 1 jak ma pare 2 jak ma 2 pary
}

uint8_t Max(volatile player *player_ptr)
{
	uint8_t max, i;
	volatile uint8_t *Tab = player_ptr->ValuesOfDice;
	max = 0 ;
	for(i = 0;i < VALUES;i++)
  {
		if (max <= *(Tab + i))
		{
			max = *(Tab + i);
		}
  }
	return max;
}
// w CountScore przyporzadkowuje Cathegory od 7-1
// kareta = 7, duzy straight  = 6,sredni straight=5, maly straight = 4, trojka =3, dwie pary = 2, jedna para = 1, nic =0
//
void CountScore(volatile player *player_ptr)
{
	uint8_t max, index;
	CountDice(current_player);
	max = Max(player_ptr);
	switch (max)
  {
  	case 4://We're looking for Four Of A Kind
					// 
					player_ptr->Category = 7;
					player_ptr->Score = Value2Index(current_player, max)+1;
  		break;
  	case 3://We're looking for Three Of A Kind
					player_ptr->Category = 3;
					player_ptr->Score = Value2Index(current_player, max)+1;
  		break;
		case 2://We're looking for Two Pairs or Pair
					if( 1 == CountPairs(current_player)){
						player_ptr->Category = 1; // jedna para
						player_ptr->Score = Value2Index(current_player, max)+1;
					}
					else if ( 2 == CountPairs(current_player)){
						player_ptr->Category = 2; // dwie pary
						player_ptr->Score = Value2Index(current_player, max)+1;
						index = player_ptr->Score;
						player_ptr->ValuesOfDice[index] = 0; // czyszcze tablice w tym miejscy gdzie znalazlo i szukam nastepnej
						player_ptr->Score += Value2Index(current_player, max)+1;
						player_ptr->ValuesOfDice[index] = max;
					}
					else
						// something went wrong, error code 
					slcdErr(1);
  		break;
		case 1://We're looking for any of Straights
					if(3 == Value2Index(current_player, 1)){
						player_ptr->Category = 4; // maly straight
						player_ptr->Score = 0;
					}
					else if(5 == Value2Index(current_player, 0) && 0==*(player_ptr->ValuesOfDice)){
						player_ptr->Category = 5; // sredni straight
						player_ptr->Score = 0;
					}
					else if(0==*(player_ptr->ValuesOfDice) && 0==*(player_ptr->ValuesOfDice+1) ){ //brzydko sprawdzam czy zero jest na 0 i 1 miejscu tablicy
						player_ptr->Category = 6; // duzy straight
						player_ptr->Score = 0;
					}
					else {
						player_ptr->Category = 0;
						player_ptr->Score = Value2Index(current_player, max)+1;// najwieksza wykulana liczba
					}						
  		break;
  	default:
						// something went wrong, error code 
					slcdErr(1);
  		break;
  }
	
}
uint8_t WhoWon(volatile player * Players){
		if(Players->Category > (Players+1)->Category)
			return 1;//wygral player 1
		else if (Players->Category == (Players+1)->Category){
				if (Players->Score > (Players+1)->Score)
					return 1;//wygral player 1
				else if (Players->Score < (Players+1)->Score)
					return 2;//wygral player 2
				else 
					return 3;//remis
		}
		else 
			return 2;
				//wygral player 2

	}	

	void DisplayWinner(uint8_t cos){//zbiera co co sie wkonalo w whoWon
		if (2==cos)
			slcdErr(2);
		else if (1==cos)
			slcdErr(1);
		else
			slcdErr(3);
	}
