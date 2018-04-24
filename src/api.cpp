#include <iostream>
#include <stdlib.h>

#include "api.h"
#include "player.h"
#include "table.h"


API::API()
	: table()
	, players()
{}

API::~API() {}

int API::run()
{
	create();
	deal(INITIAL_HAND_SIZE);
	pickFirstTurn();

	while(!isBlocked())
	{
		if(playTurn()) return EXIT_SUCCESS;
	}

	cout << "Players are blocked. Game over!" << endl;

	return EXIT_SUCCESS;
}

void API::create()
{
	Random::create();
	table.create();
	createPlayers(PLAYER_COUNT);
}

void API::createPlayers(int playerCount)
{
	for(int playerIndex = 0; playerIndex < playerCount; ++playerIndex)
	{
		stringstream playerName;
		playerName << "Player" << (playerIndex+1);
		createPlayer(playerName.str());
	}
}

void API::createPlayer(string playerName)
{
	Player player = Player(playerName);
	players.push_back(player);
}


void API::pickFirstTurn()
{
	cout << "Flipping a coin to decide who goes first...";
	currPlayerIndex = randomInt(0, players.size()-1);

	Player* currPlayer = getCurrentPlayer();
	cout << currPlayer->getName() << " goes first!" << endl;

}


void API::deal(int amount)
{
	for(size_t i = 0; i < players.size(); ++i)
	{
		Player* player = &players[i];
		player->draw(&table, amount);
		
		cout << player->getName() << " is drew 10 dominoes." << endl;
		player->printHand();
	}
}


bool API::playTurn()
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


Player* API::nextPlayer()
{
	currPlayerIndex = (currPlayerIndex+1) % players.size();
	Player* currentPlayer = getCurrentPlayer();
	return currentPlayer;
}


Player* API::getCurrentPlayer()
{
	return &players[currPlayerIndex];
}


bool API::isBlocked()
{
	bool blocked = true;
	for(size_t i = 0; i < players.size(); ++i)
	{
		blocked &= players[i].isBlocked();
	}

	return blocked;
}


void API::printPlayersHands()
{
	for(size_t i = 0; i < players.size(); ++i)
	{
		cout << players[i].getName() << "'s Hand: ";
		players[i].printHand();
	}
}