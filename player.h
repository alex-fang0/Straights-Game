#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "card.h"
#include <vector>
#include <memory>
#include <string>

class Player {
	public:
	std::vector<std::shared_ptr<Card>> Hand;
	std::vector<std::shared_ptr<Card>> Discard;
	int Score;
	std::string Type;
	
	Player(std::string atype);
	void ResetCards();
	int Scoring();
	void DiscardCard(std::shared_ptr<Card> aCard);
	void Play(std::shared_ptr<Card> aCard);
	std::shared_ptr<Card> AutoPlay(std::vector<std::shared_ptr<Card>> Plays);
	std::shared_ptr<Card> AutoDiscard();
};

#endif
