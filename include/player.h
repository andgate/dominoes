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
 *  The player class interacts with a table
 *  by drawing or playing domino pieces.
 */
class Player
{
public:
	/**
	 * @brief Constructor for Player.
	 *
	 * @param name Name to give the player.
	 */
	Player(string name);

	/**
	 * @brief Default Destructor for Player.
	 */
	~Player();

	/**
	 * @brief Draws a domino from a table's boneyard
	 *        to this player's hand.
	 * 
	 * @param table Table to draw from.
	 */
	void draw(Table* table);

	/**
	 * @brief Draws multiple dominos.
	 * 
	 * The player draws the amount of dominos as
	 * specified by 'amount'.
	 * 
	 * @param table Table to draw from.
	 * @param amount Amount of dominos to draw.
	 */
	void draw(Table* table, int amount);

	/**
	 * @brief The player's standard turn.
	 * 
	 * Tries to play a domino from the player's hand.
	 * If unsucessful, draw a domino and repeat the process.
	 * When the chain is empty, player just will play first
	 * domino on hand.
	 * 
	 * @param table Table to play on.
	 */
	void playTurn(Table* table);

	/**
	 * @brief Determines if the player's hand is empty.
	 * 
	 * @return True when empty, false otherwise.
	 */
	bool handEmpty();

	/**
	 * @brief Determines if the player is blocked.
	 *
	 *  A player is considered blocked when they
	 *  were unable to play a domino on their last turn.
	 * 
	 * @return True when blocked, false otherwise.
	 */
	bool isBlocked();

	/**
	 * @brief Get the name of the player
	 * 
	 * @return String containing the name of the player.
	 */
	string getName();

	/**
	 * @brief Prints the player's hand.
	 * 
	 */
	void printHand();


private:
	vector<shared_ptr<Domino>> hand;
	string m_name;
	bool m_isBlocked;
};

#endif /* PLAYER_H */
