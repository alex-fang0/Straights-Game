#include "table.h"
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

int main( int argc, char * argv[] ) {
	unsigned aseed = std::chrono::system_clock::now().time_since_epoch().count();
	if ( argc > 1 ) {
                try {
                        aseed = std::stoi( std::string{ argv[1] } );
                } catch( std::invalid_argument & e ) {
                        std::cerr << e.what() << std::endl;
                        return 1;
                } catch( std::out_of_range & e ) {
                        std::cerr << e.what() << std::endl;
                        return -1;
                }
        }
	Deck TheDeck(aseed);
	
	bool gamedone = false;
	bool newgame = true;
	bool played = false;
	bool repeat = false;
	
	std::vector<Player> Players;
	
	std::string s;	
	for (int i = 1; i <= 4; i++) {
		std::cout << "Is Player " << i << " a human (h) or a computer (c)?" << std::endl;
		std::getline(std::cin, s);
		Players.emplace_back(s);
	}
	Table TheGame(TheDeck,Players);
	std::vector<std::shared_ptr<Card>> TheLegals;
	while (!gamedone) {
		if (newgame) {
			TheGame.TheDeck.Shuffle();
			TheGame.Deal();
			for (int i = 0; i < 4; i++) {
				TheGame.turn = i;
				TheLegals = TheGame.CheckLegals();
				if (TheLegals.empty() == false) {
					break;
				}
			}
			std::cout << "A new round begins. It's Player" << TheGame.turn+1 << "'s turn to play." <<std::endl;	
			newgame = false;
		}
		if (repeat == false) {
			TheLegals = TheGame.CheckLegals();
			TheGame.PrintTableAndHand();
			TheGame.PrintLegals(TheLegals);
		}
		repeat = false;
		if (TheGame.Players[TheGame.turn].Type == "h") {	
			std::getline(std::cin, s);	
			std::istringstream iss{s};
			std::string cmd;
			iss >> cmd;
		
			if (cmd == "play") {
				std::string cardplay;
				iss >> cardplay;
				played = false;
				for (auto it = TheLegals.begin(); it != TheLegals.end(); it++) {
					if ((*it)->getValue() == cardplay[0] && (*it)->getSuit() == cardplay[1]) {
						TheGame.Players[TheGame.turn].Play((*it));
						TheGame.PlayCard((*it));
						played = true;
						std::cout << "Player" << TheGame.turn+1 << " plays " << cardplay << "." << std::endl;
						TheGame.NextTurn();
						break;
					}
				}
				if (played == false) {
					repeat = true;
					std::cout << "This is not a legal play." << std::endl;
				}
			} else if (cmd == "discard") {
				std::string cardplay;
                                iss >> cardplay;
				if (TheLegals.empty()) {
					for (auto it = TheGame.Players[TheGame.turn].Hand.begin(); it != TheGame.Players[TheGame.turn].Hand.end(); it++) {
                                	        if ((*it)->getValue() == cardplay[0] && (*it)->getSuit() == cardplay[1]) {
                                                	TheGame.Players[TheGame.turn].DiscardCard((*it));
							std::cout << "Player" << TheGame.turn+1 << " discards " << cardplay << "." << std::endl;
                                                	TheGame.NextTurn();
                                                	break;
                                        	}
					}
                                } else {
					repeat = true;
					std::cout << "You have a legal play. You may not discard." << std::endl;
				}
			} else if (cmd == "deck") {
				TheGame.PrintDeck();
			} else if (cmd == "ragequit") {
				TheGame.Rage();
				std::cout << "Player " << TheGame.turn << " ragequits. A computer will now take over." << std::endl;
			} else if (cmd == "quit") {
				break;
			} else {
				repeat = true;
				std::cout << "Invalid Command " << cmd << std::endl;
			}
		} else {
			if (TheLegals.empty()) {
				auto TheDiscard = TheGame.Players[TheGame.turn].AutoDiscard();
				std::cout << "Player" << TheGame.turn+1 << " discards " << TheDiscard->getValue() << TheDiscard->getSuit() << "."  << std::endl;	
				TheGame.NextTurn();
			} else {
				auto ThePlay = TheGame.Players[TheGame.turn].AutoPlay(TheLegals);
                                TheGame.PlayCard(ThePlay);
				std::cout << "Player" << TheGame.turn+1 << " plays " << ThePlay->getValue() << ThePlay->getSuit() << "."  << std::endl;
                                TheGame.NextTurn();
			}
		}
		std::cout << std::endl;
		
		if (TheGame.movesplayed == 52) {
			int winnerscore = TheGame.EndGame();
			newgame = true;
			if (winnerscore != -1) {
				for (int i = 0; i < 4; i++) {
					if (TheGame.Players[i].Score == winnerscore) {
						std::cout << "Player" << i+1 << " wins!" << std::endl;
					}
				}
				gamedone = true;
			}
		}



	}
	return 0;
}
