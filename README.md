# Straights-Game
Simple Card Game Coded using C
To Play: Run straights.exe


Rules of the Game:
>
Legal Plays
>
Immediately following the deal, the player with the 7 of spades goes first. This player must play the 7 of spades in the centre
of the table. After the 7 of spades, the players take turns to play cards on the table. At this point, the players must play cards
that constitute legal plays. The following cards are legal:
• A 7 of any suit. This card starts a new pile on the table.
• A card with the same suit and adjacent rank2
as another card that has already been played. It must be played on the pile
of the appropriate suit. (Note that the “pile” is spread across the table, so that play can proceed at either end.)
1A Jack has a rank of 11, while the Queen has a rank of 12. The rank of all other cards is their numeric value e.g. 2 has a rank of 2.
2A card has adjacent rank if its face value is one more or one less than the rank of card under consideration. The King and Ace of a suit are not considered
to be adjacent ranks to each other.

For example, if the 7 of spades is the only card on the table, then the legal plays are: the 7 of diamonds, the 7 of hearts,
the 7 of clubs, the 8 of spades, and the 6 of spades. Once the 8 of spades is played, the next legal plays are: the 9 of spades,
the 6 of spades, the 7 of diamonds, the 7 of hearts, and the 7 of clubs. In this way, you can add cards to either end of the suit
“pile” so long as there are no gaps.
>
Discards
>
When a player has no legal plays, they must then choose a card in their hand, and place it face down in front of them. This is a
discard. Note that if a player has at least one legal play in their hand, then they must make a legal play; they may not discard
in this case.
>
Scoring
>
The round ends when all the cards have either been played or discarded. For each player, their score for the round is the sum
of all the ranks of the players discards. Jacks, Queens, and Kings count as 11, 12, and 13 points, respectively. For example, if
a player discarded an Ace, a Six, and a King, the number of points would be 1 + 6 + 13 = 20.
Each player’s game score is of the sum of their scores in each round. If no player has accumulated 80 or more points at
the end of a round, then the deck is reshuffled and another round begins.

How to Play:
>
Start:
>
At the beginning of the program, prompt the user with the following message:
Is Player<x> a human (h) or a computer (c)?
where <x> is the id number representing the player being initialized. The user then types either h or c to set the desired
player type. Repeat this step for each of the four players.
The game starts after the shuffle and the deal. The four players take turns to play their cards. First, print the following line
(regardless of whether the first player is a human):
A new round begins. It’s Player<x>’s turn to play.
where <x> depends on who has the 7 of spades.

Human Player:
>
Whenever it is a human player’s turn, print the following 8 lines:
Cards on the table:
Clubs:<list of clubs>
Diamonds:<list of diamonds>
Hearts:<list of hearts>
Spades:<list of spades>
Your hand:<cards in your hand>
Legal plays:<legal plays in your hand>
>
Each of list of cards in a specific suit is an ordered sequence of all the ranks in that suit (e.g., 6 7 8 9 T J Q) that have
already been played.
<cards in your hand> and <legal plays in your hand> are lists of cards in the player’s hand, where
each card is in the form <rank><suit> (e.g. 7S). Print the cards in the same order that they appear in the deck. Do not
rearrange the cards. Every list of cards, except for that produced by the deck command, starts with a space character, and a
single space separates each card from the next. There is no space after the final card in the list. If there are no legal plays, then
the list of cards consists of an empty string i.e. print Legal plays:\n.
The program then waits for the user to enter a command.

Commands:
>
There are 5 valid commands for the human player in this game:

play <card> 
Play the specified card. You may assume that the <card> has valid syntax (i.e., <rank><suit>, such as 7C), and that
the specified card is in the players hand. However, it might not be a legal play.
If the play is legal, print:
Player<x> plays <card>.
and proceed to the next player. Otherwise, print:
This is not a legal play.and do not proceed to the next player until a legal play is made.
  
discard <card> 
If the player has no legal plays, discard the specified card from the player’s hand into the player’s discard pile. Again, assume that
the <card> has valid syntax and that the <card> is in the players hand. For test purposes, the value of the card is printed even
though that deviates from the normal straights game play.
Player <x> discards <card>.
Otherwise, print the following error message:
You have a legal play. You may not discard.
>
  
deck 
Print the contents of the deck in order, 13 cards per line. For example:
TS 2D 3S KH 3H 2C 5D TC 8S TD AC KC QH
4D JH 6H JC KD 8C 7D TH 4H 9S 6S 4S KS
7S 7C QD 6C 2H 6D 3C 9C 5H 3D AD 5S 8H
QC 2S 8D JS QS AS JD 4C 7H 9D 5C AH 9H
>

quit 
Terminate the program immediately.
  
ragequit 
Filled with anger, a human player decides to leave! Print the following message:
Player <x> ragequits. A computer will now take over.
Replace the current human player with a computer player, and resume the game.
