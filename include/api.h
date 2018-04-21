#ifndef API_H
#define API_H

#include <vector>

#include "player.h"
#include "table.h"
#include "coin.h"

using namespace std;

class API {
private:
	Table table;
	
	vector<Player> players;

	int currPlayerIndex = 0;
	int turnCount = 0;

public:
	API()
		: table()
		, players()
	{}

	int run()
	{
		table.setup();
		table.printBoneyard();

		players.push_back(Player("Player1"));
		players.push_back(Player("Player2"));

		deal();
		pickFirstTurn();
		initialTurn();

		while(!isBlocked())
		{
			if(playTurn()) return 0;
		}

		cout << "Players are blocked. Game over!" << endl;

		return 0;
	}

	void pickFirstTurn()
	{
		cout << "Flipping a coin to decide who goes first...";
		
		srand(time(nullptr));
		currPlayerIndex = abs(rand()) % players.size();

		Player* currPlayer = getCurrentPlayer();
		cout << currPlayer->getName() << " goes first!" << endl;

	}

	void deal()
	{
		for(size_t i = 0; i < players.size(); ++i)
		{
			Player* player = &players[i];
			player->draw(&table, 10);
			cout << player->getName() << " is drew 10 dominoes." << endl;
			player->printHand();
		}
	}


	void initialTurn()
	{
		Player* currPlayer = getCurrentPlayer();

		cout << currPlayer->getName() << "'s turn..." << endl;
		shared_ptr<Domino> dom(currPlayer->takeRandom());
		table.addChainTail(dom);

		nextPlayer();
	}

	bool playTurn()
	{
		Player* player = getCurrentPlayer();
		player->playTurn(&table);

		cout << player->getName() << "'s turn..." << endl;

		cout << "Current chain: ";
		table.printChain();

		cout << "Current boneyard: ";
		table.printBoneyard();

		printPlayersHands();

		if(player->handEmpty())
		{
			cout << player->getName() << " is the winner!" << endl;
			return true;
		}

		++turnCount;
		nextPlayer();
		return false;
	}

	Player* nextPlayer()
	{
		currPlayerIndex = (currPlayerIndex+1) % players.size();
		Player* currentPlayer = getCurrentPlayer();
		return currentPlayer;
	}

	Player* getCurrentPlayer()
	{
		return &players[currPlayerIndex];
	}

	bool isBlocked()
	{
		bool blocked = false;
		for(size_t i = 0; i < players.size(); ++i)
		{
			blocked |= players[i].isBlocked();
		}

		return blocked;
	}

	void printPlayersHands()
	{
		for(size_t i = 0; i < players.size(); ++i)
		{
			cout << players[i].getName() << "'s Hand: ";
			players[i].printHand();
		}
	}
};

#endif /* API_H */