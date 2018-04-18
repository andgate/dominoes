#ifndef API_H
#define API_H

#include "player.h"
#include "table.h"
#include "coin.h"

class API {
private:
	Table table;
	Player p1;
	Player p2;

	int currentTurn = 0;

public:
	API()
		: table(), p1(), p2()
	{}

	int run()
	{
		table.setup();
		table.printBoneyard();

		deal();
		pickFirstTurn();
		initialTurn();

		while(!p1.handEmpty() && !p2.handEmpty())
		{
			turn();
		}

		return 0;
	}

	void pickFirstTurn()
	{
		cout << "Flipping a coin to decide who goes first...";
		
		if(flipCoin()) {
			cout << "Player1 goes first!" << endl;
			currentTurn = 0;
		} else {
			cout << "Player2 goes first!" << endl;
			currentTurn = 1;
		}
	}

	void deal()
	{
		p1.draw(&table, 10);
		cout << "Player1 drawing.." << endl;
		p1.printHand();

		p2.draw(&table, 10);
		cout << "Player2 drawing.." << endl;
		p2.printHand();
	}


	void initialTurn()
	{
		Player* currPlayer = nextPlayer();
		shared_ptr<Domino> dom(currPlayer->takeRandom());
		table.addChainTail(dom);
	}

	void turn()
	{
		Player* currPlayer = nextPlayer();
		currPlayer->playTurn(&table);

		cout << "Current chain: ";
		table.printChain();

		cout << "Current boneyard: ";
		table.printBoneyard();
	}

	Player* nextPlayer()
	{
		if (currentTurn) {
			cout << "Player1's turn..." << endl;
			currentTurn = 0;
			return &p1;
		} else {
			cout << "Player2's turn..." << endl;
			currentTurn = 1;
			return &p2;
		}
	}
};

#endif /* API_H */