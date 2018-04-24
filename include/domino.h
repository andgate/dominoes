#ifndef DOMINO_H
#define DOMINO_H

#include <string>

using namespace std;

/**
 * @brief Domino class which represents a piece.
 *
 *  A domino has a head (left-most value) and a 
 *  tail (right-most value). In addition,
 *  a domino may be rotated, which flips
 *  the head and tail around.
 */
class Domino
{
public:
	/**
	 * @brief Constructor for Domino
	 *
	 * @param headNum Value assigned to domino's head.
	 * @param tailNum Value assigned to domino's tail.
	 */
	Domino(int headNum, int tailNum);

	/**
	 * @brief Copy Constructor for Domino
	 *
	 * @param other Domino to copy.
	 */
	Domino(const Domino &other);

	/**
	 * @brief Default Destructor of Domino
	 */
	~Domino();

	/**
	 * @brief Get the head of the domino.
	 * 
	 * @return Value at the head of the domino. 
	 */
	int getHead();

	/**
	 * @brief Get the tail of the domino.
	 * 
	 * @return Value at the tail of the domino. 
	 */
	int getTail();

	/**
	 * @brief Rotates the domino.
	 * 
	 * Rotation is accomplished by
	 * swapping the domino's head and tail.
	 */
	void rotate();

	/**
	 * @brief Get string representation of a domino.
	 * 
	 *  For example, a domino with head=1 and a tail=2
	 *  will be represented as [1|2].
	 *
	 * @return String representation of domino.
	 */
	string toString();

private:
	int m_head; // Head of domino (or left-most value).
	int m_tail; // Tail of domino (or right-most value).
};

#endif /* DOMINO_H */
