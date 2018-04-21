#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <utility>
#include <vector>

#include "domino.h"
#include "table.h"

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


	void draw(Table* table)
	{
		shared_ptr<Domino> dom = table->draw();
		hand.push_back(dom);
	}


	void draw(Table* table, int amount)
	{
		for(int i = 0; i < amount; ++i)
		{
			draw(table);
		}
	}


	void playTurn(Table* table)
	{
		for(size_t i = 0; i < hand.size(); ++i)
		{
			shared_ptr<Domino> dom(hand[i]); 
			if(table->playPiece(dom))
			{
				hand.erase(hand.begin()+i);
				return;
			}
		}

		// Otherwise, draw until a piece is playable
		while(true)
		{
			shared_ptr<Domino> dom = table->draw();
			if(dom == nullptr) return;

			if (table->playPiece(dom))
				return;
			else
				hand.push_back(dom);
		}
	}

	shared_ptr<Domino> takeRandom()
	{
		std::srand(std::time(nullptr));
		int domIndex = std::rand() % (hand.size() - 1);
		
		shared_ptr<Domino> dom(hand.at(domIndex));
		hand.erase(hand.begin() + domIndex);
		
		return dom;
	}


	bool handEmpty()
	{
		return hand.empty();
	}

	void printHand()
	{
		for (auto& dom : hand)
			cout << "[" << dom->getTail() << "|" << dom->getHead() << "] ";
		cout << endl;
	}
};

#endif /* PLAYER_H */