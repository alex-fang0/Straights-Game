#include "deck.h"
#include <algorithm>
#include <random>
#include <iostream>

Deck::Deck(unsigned aseed)
	: seed{aseed}
{
	char suit;
	for(int i = 0; i < 4; i++) {
		if (i == 0) {
			suit = 'C';
		} else if (i == 1) {
			suit = 'D';
		} else if (i == 2) {
			suit = 'H';
		} else {
			suit = 'S';
		}

		Cards.emplace_back(new Card{'A',suit,1});

		for (int j = 2; j <= 9; j++) {
			Cards.emplace_back(new Card{'0'+j, suit, j});
		}

		Cards.emplace_back(new Card{'T',suit,10});
		Cards.emplace_back(new Card{'J',suit,11});
		Cards.emplace_back(new Card{'Q',suit,12});
		Cards.emplace_back(new Card{'K',suit,13});
	}
	for (auto i : this->Cards) {
                //std::cout << i.get()->getValue() << i.get()->getSuit() << std::endl;
        }
}

void Deck::Shuffle() {
	std::default_random_engine rng{seed};
        std::shuffle(this->Cards.begin(), this->Cards.end(), rng );
}
