#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>
#include <vector>

#include "domino.h"
#include "table.h"
#include "random.h"

using namespace std;

/**
 * @brief The Player class
 * 
 */
class Player : Random
{
private:
	vector<shared_ptr<Domino>> hand;
	string m_name;
	bool m_isBlocked;

public:
	Player(string name);
	~Player();
	
	void create();

	/**
	 * @brief Draws one domino
	 * 
	 * @param table
	 */
	void draw(Table* table);

	/**
	 * @brief Draws multiple dominos
	 * 
	 * The player draws the amount of dominos as
	 * specified by 'amount'
	 * 
	 * @param table 
	 * @param amount 
	 */
	void draw(Table* table, int amount);

	/**
	 * @brief The player's standard turn
	 * 
	 * Tries to play a domino from the player's hand.
	 * If unsucessful, draw a domino and repeat the process.
	 * 
	 * @param table 
	 */
	void playTurn(Table* table);

	/**
	 * @brief Takes a random domino from the player's hand
	 * 
	 * @return shared_ptr<Domino> 
	 */
	shared_ptr<Domino> takeRandom();

	/**
	 * @brief Determines if the hand is empty
	 * 
	 * @return true 
	 * @return false 
	 */
	bool handEmpty();

	/**
	 * @brief Determines if the player is blocked
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isBlocked();

	/**
	 * @brief Get the Name object
	 * 
	 * @return string 
	 */
	string getName();

	/**
	 * @brief Prints the player's hand
	 * 
	 */
	void printHand();
};

#endif /* PLAYER_H */
