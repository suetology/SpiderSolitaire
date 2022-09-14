#pragma once

#include <vector>

#define CARD_COUNT 104
#define OPENED_CARDS 10
#define HIDDEN_CARDS 44
#define CARDS_IN_DECK 50

class Card;

class Deck
{
public:
	static std::vector<Card*> cards;
	static std::vector<Card*> cardsInDeck;

	static void Shuffle();
};

std::vector<Card*> Deck::cards;
std::vector<Card*> Deck::cardsInDeck;

void Deck::Shuffle()
{
	/*for (int i = 0; i < 10; i++)
	{
		rand();
	}*/

	std::vector<Card*> shuffled;
	
	shuffled.reserve(CARDS_IN_DECK);

	while (shuffled.size() < CARDS_IN_DECK)
	{
		int i = rand() % cards.size();
		shuffled.push_back(cards[i]);
		cards.erase(cards.begin() + i);
	}
	cardsInDeck = shuffled;

	shuffled.clear();
	shuffled.reserve(OPENED_CARDS + HIDDEN_CARDS);

	while (shuffled.size() < OPENED_CARDS + HIDDEN_CARDS)
	{
		int i = rand() % cards.size();
		shuffled.push_back(cards[i]);
		cards.erase(cards.begin() + i);
	}
	cards = shuffled;
}