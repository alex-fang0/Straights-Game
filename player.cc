#include "player.h"

Player::Player(std::string atype)
	:Score{0},
	 Type{atype}
{}

void Player::ResetCards() {
	this->Hand.clear();
	this->Discard.clear();
}

int Player::Scoring() {
	int total = 0;
	for (int i = 0; i < this->Discard.size(); i++) {
                total += this->Discard[i].get()->getScore();
        }
	this->Score += total;
	return total;
}

void Player::DiscardCard(std::shared_ptr<Card> aCard) {
	for (int i = 0; i < this->Hand.size(); i++) {
                if (aCard.get() == this->Hand[i].get()) {
			this->Discard.emplace_back(this->Hand[i]);
			this->Hand.erase(this->Hand.begin()+i);
			break;
		}
        }
}

void Player::Play(std::shared_ptr<Card> aCard) {
	 for (int i = 0; i < this->Hand.size(); i++) {
                if (aCard.get() == this->Hand[i].get()) {
			this->Hand.erase(this->Hand.begin()+i);
                        break;
                }
        }
}

std::shared_ptr<Card> Player::AutoPlay(std::vector<std::shared_ptr<Card>> Plays) {
	this->Play(Plays[0]);
	return Plays[0];
}

std::shared_ptr<Card> Player::AutoDiscard() {
	this->DiscardCard(this->Hand[0]);
	return this->Discard[this->Discard.size()-1];
}


