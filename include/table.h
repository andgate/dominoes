#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>

#include "domino.h"
#include "player.h"

using namespace std;


class Table
{
private:
	static const int DOMINO_MAX = 6;
	static const int DOMINOS_COUNT = 26;

	vector<shared_ptr<Domino>> 	boneyard;
	list<shared_ptr<Domino>> 	chain;

	Player p1;
	Player p2;

public:
	Table()
		: boneyard(), chain()
		, p1() , p2()
	{}
	
	~Table()
	{}

	void build()
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

		for (auto& dom : boneyard)
			cout << "[" << dom->fst() << "|" << dom->snd() << "]" << endl;
	}

	void deal(Player* p)
	{
		p->take(boneyard.back());
		boneyard.pop_back();
	}
};

#endif /* TABLE_H */