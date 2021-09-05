#pragma once
enum class cardSuits {
	heart,
	spade,
	cross,
	diamond
};
enum class cardValues {
	_A = 1,
	_2 = 2,
	_3 = 3,
	_4 = 4,
	_5 = 5,
	_6 = 6,
	_7 = 7,
	_8 = 8,
	_9 = 9,
	_10 = 10,
	_J = 10,
	_Q = 10,
	_K = 10
};

class Card
{
private:
	cardSuits _suit;
	cardValues _value;
	bool _position;
public:
	Card(cardSuits suit, cardValues value, bool position = false) : _suit(suit), _value(value), _position(position) {};

	void Flip() {
		_position = !_position;
	};

	int GetValue() {
		return static_cast<int>(_value);
	};
};


