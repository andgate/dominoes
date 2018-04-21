#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>
#include <utility>

#include "domino.h"

using namespace std;

class Table
{
private:
	static const int DOMINO_MAX = 6;
	static const int DOMINOS_COUNT = 26;

	vector<shared_ptr<Domino>> 	boneyard;
	list<shared_ptr<Domino>> 	chain;

public:
	Table()
		: boneyard()
		, chain()
	{}
	
	~Table()
	{}

	void setup()
	{
		// Generate dominos
		boneyard.clear();
		boneyard.reserve(DOMINOS_COUNT);
		for (int i = 0; i <= DOMINO_MAX; ++i) {
			for (int j = i; j <= DOMINO_MAX; ++j) {
				shared_ptr<Domino> dom_ptr(new Domino(i, j));
				boneyard.push_back(dom_ptr);
			}
    	}

		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    	shuffle(boneyard.begin(), boneyard.end(), default_random_engine(seed));
	}

	shared_ptr<Domino> draw()
	{
		if (boneyard.empty()) return nullptr;
		shared_ptr<Domino> dom(boneyard.back());
		boneyard.pop_back();
		return dom;
	}

	bool boneyardEmpty()
	{
		return boneyard.empty();
	}

	int getChainHead()
	{
		return chain.front()->getHead();
	}

	void addChainHead(shared_ptr<Domino> dom)
	{
		chain.push_front(dom);
	}

	int getChainTail()
	{
		return chain.back()->getTail();
	}

	void addChainTail(shared_ptr<Domino> dom)
	{
		chain.push_back(dom);
	}


	bool playPiece(shared_ptr<Domino> dom)
	{
		if(chain.empty())
		{
			chain.push_back(dom);
			return true;
		}

		int head = getChainHead();
		int tail = getChainTail();

		if (dom->getHead() == tail)
		{
			addChainTail(dom);
			return true;
		} else if (dom->getTail() == head) {
			addChainHead(dom);
			return true;
		}

		dom->rotate();

		if (dom->getHead() == tail) {
			addChainTail(dom);
			return true;
		} else if (dom->getTail() == head) {
			addChainHead(dom);
			return true;
		}

		return false;
	}


	void printBoneyard()
	{
		for (auto& dom : boneyard)
			cout << "[" << dom->getHead() << "|" << dom->getTail() << "] ";
		cout << endl;
	}


	void printChain()
	{
		for (auto& dom : chain)
			cout << "[" << dom->getHead() << "|" << dom->getTail() << "] ";
		cout << endl;
	}
};

#endif /* TABLE_H */