#ifndef API_H
#define API_H

#include <vector>

#include "random.h"
#include "player.h"
#include "table.h"

using namespace std;

class API : Random
{
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

	/**
	 * @brief Runs through a game of Dominoes
	 * 
	 * Sets up the table, boneyard, and players. Deals the 
	 * dominoes to the players and selects who has the first
	 * turn. Chosen player plays the first domino, then the
	 * game continues until neither player can play.
	 * 
	 * @return int 
	 */
	int run()
	{
        create();
        
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
	
	void create()
    {
        Random::create();
        
        table.create();
		table.printBoneyard();

        createPlayers();
    }
	
	void createPlayers()
    {
        Player p1 = Player("Player1");
        Player p2 = Player("Player2");
        
        p1.create();
        p2.create();
        
		players.push_back(p1);
		players.push_back(p2);
    }
    

	/**
	 * @brief Randomly decides which player goes first
	 * 
	 */
	void pickFirstTurn()
	{
		cout << "Flipping a coin to decide who goes first...";
		currPlayerIndex = randomInt(0, players.size()-1);

		Player* currPlayer = getCurrentPlayer();
		cout << currPlayer->getName() << " goes first!" << endl;

	}

	/**
	 * @brief Gives each player 10 dominoes
	 * 
	 */
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

	/**
	 * @brief The very first turn
	 * 
	 * 	Plays a random domino from the player's hand as the first domino
	 *  in the chain
	 */
	void initialTurn()
	{
		Player* currPlayer = getCurrentPlayer();

		cout << currPlayer->getName() << "'s turn..." << endl;
		shared_ptr<Domino> dom(currPlayer->takeRandom());
		table.addChainTail(dom);

		nextPlayer();
	}

	/**
	 * @brief A standard turn
	 * 
	 * Takes a random domino from the player's hand and plays it
	 * 
	 * @return true 
	 * @return false 
	 */
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

	/**
	 * @brief Changes whose turn it is
	 * 
	 * @return Player* 
	 */
	Player* nextPlayer()
	{
		currPlayerIndex = (currPlayerIndex+1) % players.size();
		Player* currentPlayer = getCurrentPlayer();
		return currentPlayer;
	}

	/**
	 * @brief Get the Current Player object
	 * 
	 * @return Player* 
	 */
	Player* getCurrentPlayer()
	{
		return &players[currPlayerIndex];
	}

	/**
	 * @brief Checks if the players are blocked
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isBlocked()
	{
		bool blocked = true;
		for(size_t i = 0; i < players.size(); ++i)
		{
			blocked &= players[i].isBlocked();
		}

		return blocked;
	}

	/**
	 * @brief Prints all player's hands
	 * 
	 */
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
