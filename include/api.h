#ifndef API_H
#define API_H

#include <vector>
#include <sstream>

#include "random.h"
#include "player.h"
#include "table.h"

using namespace std;

class API : Random
{
public:
	API();
	~API();

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
	int run();

private:
	private:
	static const int PLAYER_COUNT = 2;
	static const int INITIAL_HAND_SIZE = 10;

	Table table;
	
	vector<Player> players;

	int currPlayerIndex = 0;
	int turnCount = 0;

	
	void create();
	
	void createPlayers(int playerCount);

	void createPlayer(string playerName);
    

	/**
	 * @brief Randomly decides which player goes first
	 * 
	 */
	void pickFirstTurn();

	/**
	 * @brief Gives each player 10 dominoes
	 * 
	 */
	void deal();

	/**
	 * @brief The very first turn
	 * 
	 * 	Plays a random domino from the player's hand as the first domino
	 *  in the chain
	 */
	void initialTurn();

	/**
	 * @brief A standard turn
	 * 
	 * Takes a random domino from the player's hand and plays it
	 * 
	 * @return true 
	 * @return false 
	 */
	bool playTurn();

	/**
	 * @brief Changes whose turn it is
	 * 
	 * @return Player* 
	 */
	Player* nextPlayer();

	/**
	 * @brief Get the Current Player object
	 * 
	 * @return Player* 
	 */
	Player* getCurrentPlayer();

	/**
	 * @brief Checks if the players are blocked
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isBlocked();

	/**
	 * @brief Prints all player's hands
	 * 
	 */
	void printPlayersHands();
};

#endif /* API_H */
