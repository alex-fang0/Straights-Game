#ifndef _DECK_H_
#define _DECK_H_
#include "card.h"
#include <vector>
#include <memory>

class Deck {
	public:
	std::vector<std::shared_ptr<Card>> Cards;
	unsigned seed;
	void Shuffle();
	Deck(unsigned aseed);
};

#endif
