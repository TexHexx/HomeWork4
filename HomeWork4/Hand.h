#pragma once
#include "Card.h"
#include <vector>

class Hand
{
private:
	std::vector<Card*> _cards;
public:
	Hand() {
		_cards.reserve(52);
	};

	void Add(Card& card) {
		_cards.push_back(&card);
	};

	void Clear() {
		_cards.clear();
	};

	int GetValue() {
		bool hasAce = false;
		int result = 0;
		for (auto card : _cards) {
			int cardValue = card->GetValue();
			if (cardValue == 1)
				hasAce = true;
			result += card->GetValue();
		};
		if (((result + 10) <= 21) && hasAce)
			result += 10;
		return result;
	};
};

\