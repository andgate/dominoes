#include <iostream>

#include "table.h"

Table::Table()
	: boneyard()
	, chain()
{}

Table::~Table()
{}


void Table::create()
{
	Random::create();
	
	boneyard.clear();
	boneyard.reserve(DOMINOS_COUNT);
	for (int i = 0; i <= DOMINO_MAX; ++i) {
		for (int j = i; j <= DOMINO_MAX; ++j) {
			shared_ptr<Domino> dom_ptr(new Domino(i, j));
			boneyard.push_back(dom_ptr);
		}
	}

	shuffleBoneyard();
}


void Table::shuffleBoneyard()
{
	int n = boneyard.size() - 1;
	shared_ptr<Domino> tmp = nullptr;
	for (unsigned i = 0; i < boneyard.size(); ++i)
	{
		unsigned j = randomInt(0, n);
		tmp = boneyard[i];
		boneyard[i] = boneyard[j];
		boneyard[j] = tmp;
	}
}


shared_ptr<Domino> Table::draw()
{
	if (boneyard.empty()) return nullptr;
	shared_ptr<Domino> dom(boneyard.back());
	boneyard.pop_back();
	return dom;
}


bool Table::boneyardEmpty()
{
	return boneyard.empty();
}


int Table::getChainHead()
{
	return chain.front()->getHead();
}


void Table::addChainHead(shared_ptr<Domino> dom)
{
	chain.push_front(dom);
}


int Table::getChainTail()
{
	return chain.back()->getTail();
}


void Table::addChainTail(shared_ptr<Domino> dom)
{
	chain.push_back(dom);
}


bool Table::playPiece(shared_ptr<Domino> dom)
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


void Table::printBoneyard()
{
	for (auto& dom : boneyard)
		cout << "[" << dom->getHead() << "|" << dom->getTail() << "] ";
	cout << endl;
}


void Table::printChain()
{
	for (auto& dom : chain)
		cout << "[" << dom->getHead() << "|" << dom->getTail() << "] ";
	cout << endl;
}