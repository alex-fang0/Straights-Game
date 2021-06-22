#ifndef _TABLE_H_
#define _TABLE_H_

#include "deck.h"
#include "player.h"

class Table {
        public:
	std::vector<std::shared_ptr<Card>> Diamonds;
	std::vector<std::shared_ptr<Card>> Clubs;
	std::vector<std::shared_ptr<Card>> Hearts;
	std::vector<std::shared_ptr<Card>> Spades;	
	Deck TheDeck;
	std::vector<Player> Players;
	int turn;
	int movesplayed;

	Table(Deck aDeck, std::vector<Player> aPlayers);
	void Deal();
	void Rage();
	void ResetPiles();
	int EndGame();
	void PlayCard(std::shared_ptr<Card> aCard);
	std::vector<std::shared_ptr<Card>> CheckLegals();
	void NextTurn();
	void PrintDeck();
	void PrintTableAndHand();
	void PrintLegals(std::vector<std::shared_ptr<Card>> Legals);
};

#endif
