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
		int head = table->getChainHead();
		int tail = table->getChainTail();

		for(size_t i = 0; i < hand.size(); ++i)
		{
			shared_ptr<Domino> dom(hand[i]); 
			int domHead = dom->getHead();
			int domTail = dom->getTail();

			if (domHead == head) {
				table->addChainHead(dom);
				hand.erase(hand.begin() + i);
				return;
			} else if (domTail == tail) {
				table->addChainTail(dom);
				hand.erase(hand.begin() + i);
				return;
			}

			dom->rotate();

			if (domHead == head) {
				table->addChainHead(dom);
				hand.erase(hand.begin() + i);
				return;
			} else if (domTail == tail) {
				table->addChainTail(dom);
				hand.erase(hand.begin() + i);
				return;
			}
		}

		// Otherwise, draw and exit
		draw(table);
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