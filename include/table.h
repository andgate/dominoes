#ifndef TABLE_H
#define TABLE_H

#include <list>
#include <vector>
#include <memory>

#include "domino.h"
#include "random.h"

using namespace std;

class Table : Random
{

private:
	static const int DOMINO_MAX = 6;
	static const int DOMINOS_COUNT = 26;

	vector<shared_ptr<Domino>> 	boneyard;
	list<shared_ptr<Domino>> 	chain;


public:
	Table();
	~Table();


	/**
	 * @brief Initializes random number generator,
     *        creates and shuffles dominoes.
	 * 
	 *  Populates the boneyard with the 26 dominos
	 *  needed for a game, and shuffles the boneyard.
	 */
	void create();

	/**
	 * @brief Shuffle the current boneyard
	 * 
	 *  Shuffles the current boneyard in linear time.
	 *  Does so by iterating through the dominoes,
	 *  and randomly swapping each domino with another.
	 */
	void shuffleBoneyard();

	/**
	 * @brief Draws a domino from the boneyard.
	 * 		
	 * 	If there are dominoes left in the boneyard, draw() will
	 * 	remove a domino from the boneyard, and return that domino.
	 *  Otherwise, a nullptr will be given.
	 * 
	 * @return Pointer to the domino drawn from the boneyard,
     *         or nullptr when there are none to draw.
	 */
	shared_ptr<Domino> draw();

	/**
	 * @brief Determines if the boneyard is empty
	 * 
	 * @return True when empty, false otherwise.
	 */
	bool boneyardEmpty();

	/**
	 * @brief Get the value at the head of the domino chain.
	 * 
	 * @return value at the head of the domino chain.
	 */
	int getChainHead();

	/**
	 * @brief Adds a domino to the head of the chain.
	 * 
	 * @param dom Domino to add to the head of the chain.
	 */
	void addChainHead(shared_ptr<Domino> dom);

	/**
	 * @brief Get the value at the tail of the chain.
	 * 
	 * @return value at the tail of the domino chain. 
	 */
	int getChainTail();

	/**
	 * @brief Adds a domino to the tail of the chain.
	 * 
	 * @param dom Domino to add to the head of the chain.
	 */
	void addChainTail(shared_ptr<Domino> dom);

	/**
	 * @brief Tries to play a domino.
	 * 
	 * Takes a domino and checks the to see if it can
	 * be played on the chain. If the head or tail of the domino
	 * matches the head or tail of the chain, then the domino
	 * will be added to the chain.
	 * 
	 * @param dom Domino to play
	 * @return True when domino is played successfully, otherwise false.
	 */
	bool playPiece(shared_ptr<Domino> dom);

	/**
	 * @brief Prints the current boneyard
	 * 
	 */
	void printBoneyard();

	/**
	 * @brief Prints the current domino chain
	 * 
	 */
	void printChain();
};

#endif /* TABLE_H */
