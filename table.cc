#include "table.h"
#include <iostream>

Table::Table(Deck aDeck, std::vector<Player> aPlayers) 
	:TheDeck{aDeck},
	 Players{aPlayers},
	 turn{0},
	 movesplayed{0}
{}

void Table::Deal() {
	for (int i = 0; i < 4; i++) {
		auto start_itr = std::next(this->TheDeck.Cards.cbegin(), i*13);
		auto end_itr = std::next(this->TheDeck.Cards.cbegin(), i*13 + 13);
		this->Players[i].Hand.resize(13);
		std::copy(start_itr, end_itr, this->Players[i].Hand.begin());
	}
}

void Table::Rage() {
	this->Players[this->turn].Type = "c";
}

void Table::ResetPiles() {
	this->Diamonds.clear();
	this->Clubs.clear();
	this->Hearts.clear();
	this->Spades.clear();
}

int Table::EndGame() {
	this->ResetPiles();
	int currscore;
	int minscore = 9999;
	bool ended = false;
	for (int i = 0; i < 4; i++) {
		currscore = this->Players[i].Scoring();
		std::cout << "Player" << i+1 << "'s discards: ";
		for (auto it = this->Players[i].Discard.begin(); it != this->Players[i].Discard.end(); it++) {
               		std::cout << (*(*it)).getValue() << (*(*it)).getSuit() << " ";
        	}
        	std::cout << std::endl;
		std::cout << "Player" << i+1 << "'s score: " << this->Players[i].Score - currscore << " + " << currscore << " = " << this->Players[i].Score << std::endl;
		if (this->Players[i].Score >= 80) {
			ended = true;
		}
		if (this->Players[i].Score < minscore) {
			minscore = this->Players[i].Score;
		}
		this->Players[i].ResetCards();
	}
	this->movesplayed = 0;
	if (ended) {
		return minscore;
	} else {
		return -1;
	}
}

void Table::PlayCard(std::shared_ptr<Card> aCard) {
	char thesuit = aCard->getSuit();
	int thescore = aCard->getScore();
	if (thesuit == 'D') {
		if (this->Diamonds.size() == 0) {
			this->Diamonds.push_back(aCard);
		} else if (thescore < (*this->Diamonds[0]).getScore()) {
			this->Diamonds.insert(this->Diamonds.begin(), aCard);
		} else {
			this->Diamonds.push_back(aCard);
		}
	} else if (thesuit == 'C') {
                if (this->Clubs.size() == 0) {
                        this->Clubs.push_back(aCard);
                } else if (thescore < (*this->Clubs[0]).getScore()) {
                        this->Clubs.insert(this->Clubs.begin(), aCard);
                } else {
                        this->Clubs.push_back(aCard);
                }
	} else if (thesuit == 'H') {
                if (this->Hearts.size() == 0) {
                        this->Hearts.push_back(aCard);
                } else if (thescore < (*this->Hearts[0]).getScore()) {
                        this->Hearts.insert(this->Hearts.begin(), aCard);
                } else {
                        this->Hearts.push_back(aCard);
                }
	} else {
		if (this->Spades.size() == 0) {
                        this->Spades.push_back(aCard);
                } else if (thescore < (*this->Spades[0]).getScore()) {
                        this->Spades.insert(this->Spades.begin(), aCard);
                } else {
                        this->Spades.push_back(aCard);
                }
	}
}

std::vector<std::shared_ptr<Card>> Table::CheckLegals() {
	char thesuit;
	int thescore;
	std::vector<std::shared_ptr<Card>> Legals;
	
	for (auto it = this->Players[this->turn].Hand.begin(); it != this->Players[this->turn].Hand.end(); it++) {
		thesuit = (*it)->getSuit();
		thescore = (*it)->getScore();
		if (this->Diamonds.empty() && this->Clubs.empty() && this->Hearts.empty() && this->Spades.empty()) {
			if (thesuit == 'S' && thescore == 7) {
				Legals.push_back((*it));
				break;
			}
		} else {
			if (thescore == 7) {
				Legals.push_back((*it));
			} else if (thesuit == 'D') {
				if (this->Diamonds.size() != 0) {
					if (thescore == (*this->Diamonds[0]).getScore() - 1) {
					Legals.insert(Legals.begin(),(*it));
					} else if (thescore == (*this->Diamonds[this->Diamonds.size()-1]).getScore() + 1) {
						Legals.push_back((*it));
					}
				}
			} else if (thesuit == 'C') {
				if (this->Clubs.size() != 0) {
        	                	if (thescore == (*this->Clubs[0]).getScore() - 1) {
                	        	        Legals.insert(Legals.begin(),(*it));
                        		} else if (thescore == (*this->Clubs[this->Clubs.size()-1]).getScore() + 1) {
	                        	        Legals.push_back((*it));
        	                	}
				}
			} else if (thesuit == 'H') {
				if (this->Hearts.size() != 0) {
                        		if (thescore == (*this->Hearts[0]).getScore() - 1) {
	                        	        Legals.insert(Legals.begin(),(*it));
        	                	} else if (thescore == (*this->Hearts[this->Hearts.size()-1]).getScore() + 1) {
                	                	Legals.push_back((*it));
                        		}
				}
  	              } else if (thesuit == 'S') {
			       if (this->Spades.size() != 0) {
			      		if (thescore == (*this->Spades[0]).getScore() - 1) {
                	                	Legals.insert(Legals.begin(),(*it));
                        		} else if (thescore == (*this->Spades[this->Spades.size()-1]).getScore() + 1) {
                                		Legals.push_back((*it));
					}
			       }
		      }
		}
	}
	return Legals;
}

void Table::NextTurn() {
	this->turn += 1;
	if (this->turn == 4) {
		turn = 0;
	}
	this->movesplayed += 1;
}

void Table::PrintDeck() {
	int count = 0;
	for (auto it = this->TheDeck.Cards.begin(); it != this->TheDeck.Cards.end(); it++) {
		std::cout << (*(*it)).getValue() << (*(*it)).getSuit();
		count++;
		if ((count%13 == 0) && (count != 0)) {
			std::cout << std::endl;
		} else {
			std::cout << " ";
		}
	}
}

void Table::PrintTableAndHand() {
	std::cout << "Cards on the table:" << std::endl;
	std::cout << "Clubs: ";
	for (auto it = this->Clubs.begin(); it != this->Clubs.end(); it++) {
		std::cout << (*(*it)).getValue() << (*(*it)).getSuit() << " ";
	}
	std::cout << std::endl;
	std::cout << "Diamonds: ";
        for (auto it = this->Diamonds.begin(); it != this->Diamonds.end(); it++) {
                std::cout << (*(*it)).getValue() << (*(*it)).getSuit() << " ";
        }
	std::cout << std::endl;
	std::cout << "Hearts: ";
        for (auto it = this->Hearts.begin(); it != this->Hearts.end(); it++) {
		std::cout << (*(*it)).getValue() << (*(*it)).getSuit() << " ";
        }
	std::cout << std::endl;
	std::cout << "Spades: ";
        for (auto it = this->Spades.begin(); it != this->Spades.end(); it++) {
		std::cout << (*(*it)).getValue() << (*(*it)).getSuit() << " ";
        }
	std::cout << std::endl;
	std::cout << "Your hand: ";
	for (auto it = this->Players[this->turn].Hand.begin(); it != this->Players[this->turn].Hand.end(); it++) {
		std::cout << (*(*it)).getValue() << (*(*it)).getSuit() << " ";
	}
	std::cout << std::endl;
}

void Table::PrintLegals(std::vector<std::shared_ptr<Card>> Legals) {
	std::cout << "Legal plays: ";
	for (auto it = Legals.begin(); it != Legals.end(); it++) {
		std::cout << (*(*it)).getValue() << (*(*it)).getSuit() << " ";
	}
	std::cout << std::endl;
}


