#ifndef _CARD_H_
#define _CARD_H_
#include <string>

class Card {
	char Value;
	char Suit;
	int Score;
	public:
	Card(char avalue, char asuit, int ascore);
	char getSuit();
	char getValue();
	int getScore();
};

#endif
