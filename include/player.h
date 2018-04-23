#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <utility>
#include <vector>
#include <string>

#include "domino.h"
#include "table.h"

using namespace std;

/**
 * @brief The Player class
 * 
 */
class Player
{
private:
	vector<shared_ptr<Domino>> hand;
	string m_name;
	bool m_isBlocked;

public:
	Player(string name)
		: hand(), m_name(name), m_isBlocked(false)
	{}

	~Player() {}

	/**
	 * @brief Draws one domino
	 * 
	 * @param table 
	 */
	void draw(Table* table)
	{
		shared_ptr<Domino> dom = table->draw();
		hand.push_back(dom);
	}

	/**
	 * @brief Draws multiple dominos
	 * 
	 * The player draws the amount of dominos as
	 * specified by 'amount'
	 * 
	 * @param table 
	 * @param amount 
	 */
	void draw(Table* table, int amount)
	{
		for(int i = 0; i < amount; ++i)
		{
			draw(table);
		}
	}

	/**
	 * @brief The player's standard turn
	 * 
	 * Tries to play a domino from the player's hand.
	 * If unsucessful, draw a domino and repeat the process.
	 * 
	 * @param table 
	 */
	void playTurn(Table* table)
	{
		m_isBlocked = false;

		for(size_t i = 0; i < hand.size(); ++i)
		{
			shared_ptr<Domino> dom(hand[i]); 
			if(table->playPiece(dom))
			{
				hand.erase(hand.begin()+i);
				return;
			}
		}

		// Otherwise, draw until a piece is playable
		while(true)
		{
			shared_ptr<Domino> dom = table->draw();
			if(dom == nullptr)
			{
				m_isBlocked = true;
				return;
			}

			if (table->playPiece(dom))
				return;
			else
				hand.push_back(dom);
		}
	}

	/**
	 * @brief Takes a random domino from the player's hand
	 * 
	 * @return shared_ptr<Domino> 
	 */
	shared_ptr<Domino> takeRandom()
	{
		std::srand(std::time(nullptr));
		int domIndex = std::rand() % (hand.size() - 1);
		
		shared_ptr<Domino> dom(hand.at(domIndex));
		hand.erase(hand.begin() + domIndex);
		
		return dom;
	}

	/**
	 * @brief Determines if the hand is empty
	 * 
	 * @return true 
	 * @return false 
	 */
	bool handEmpty()
	{
		return hand.empty();
	}

	/**
	 * @brief Determines if the player is blocked
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isBlocked()
	{
		return m_isBlocked;
	}

	/**
	 * @brief Get the Name object
	 * 
	 * @return string 
	 */
	string getName()
	{
		return m_name;
	}

	/**
	 * @brief Prints the player's hand
	 * 
	 */
	void printHand()
	{
		for (auto& dom : hand)
			cout << "[" << dom->getTail() << "|" << dom->getHead() << "] ";
		cout << endl;
	}
};

#endif /* PLAYER_H */
