#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

#include "domino.h"

using namespace std;

class Player
{
private:
	vector<shared_ptr<Domino>> hand;

public:
	Player()
		: hand()
	{}

	~Player() {}

	void take(shared_ptr<Domino> domino)
	{
		hand.push_back(domino);
	}

	shared_ptr<Domino> playDomino()
	{
		shared_ptr<Domino> dom(hand.back());
		hand.pop_back();
		return dom;
	}

};

#endif /* PLAYER_H */