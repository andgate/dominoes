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

	/**
	 * @brief Creates the dominoes
	 * 
	 * Generates every domino possible and adds
	 * them to the boneyard. Then randomizes the
	 * order of the boneyard
	 */
	void setup()
	{
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


	/**
	 * @brief Adds a domino into the player's hand
	 * 		
	 * 	If there are dominoes left in the boneyard, it will
	 * 	move one from it into the player's hand
	 * 
	 * @return shared_ptr<Domino> 
	 */
	shared_ptr<Domino> draw()
	{
		if (boneyard.empty()) return nullptr;
		shared_ptr<Domino> dom(boneyard.back());
		boneyard.pop_back();
		return dom;
	}

	/**
	 * @brief Determines if the boneyard is empty
	 * 
	 * @return true 
	 * @return false 
	 */
	bool boneyardEmpty()
	{
		return boneyard.empty();
	}

	/**
	 * @brief Get the Chain Head object
	 * 
	 * @return int 
	 */
	int getChainHead()
	{
		return chain.front()->getHead();
	}

	/**
	 * @brief Adds the domino to the head of the chain
	 * 
	 * @param dom 
	 */
	void addChainHead(shared_ptr<Domino> dom)
	{
		chain.push_front(dom);
	}

	/**
	 * @brief Get the Chain Tail object
	 * 
	 * @return int 
	 */
	int getChainTail()
	{
		return chain.back()->getTail();
	}

	/**
	 * @brief Adds the domino to the tail of the chain
	 * 
	 * @param dom 
	 */
	void addChainTail(shared_ptr<Domino> dom)
	{
		chain.push_back(dom);
	}

	/**
	 * @brief Tries to play a domino to the chain
	 * 
	 * Takes the current domino and checks the to see if it can
	 * be played on the chain in its current rotation. If it can't
	 * then flip it and check again.
	 * 
	 * @param dom 
	 * @return true 
	 * @return false 
	 */
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

	/**
	 * @brief Prints the current boneyard
	 * 
	 */
	void printBoneyard()
	{
		for (auto& dom : boneyard)
			cout << "[" << dom->getHead() << "|" << dom->getTail() << "] ";
		cout << endl;
	}

	/**
	 * @brief Prints the current domino chain
	 * 
	 */
	void printChain()
	{
		for (auto& dom : chain)
			cout << "[" << dom->getHead() << "|" << dom->getTail() << "] ";
		cout << endl;
	}
};

#endif /* TABLE_H */
