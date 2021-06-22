#include "card.h"

Card::Card(char avalue, char asuit, int ascore)
	: Value{avalue},
	  Suit{asuit},
	  Score{ascore}
{}

char Card::getSuit() {
	return this->Suit;
}

char Card::getValue() {
        return this->Value;
}

int Card::getScore() {
	return this->Score;
}
