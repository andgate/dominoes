#ifndef DOMINO_H
#define DOMINO_H

#include <string>


using namespace std;


class Domino {
private:
	int m_head;
	int m_tail;

public:
	Domino(int headNum, int tailNum);
	Domino(const Domino &other);

	~Domino();

	/**
	 * @brief Get the Head object
	 * 
	 * @return int 
	 */
	int getHead();

	/**
	 * @brief Get the Tail object
	 * 
	 * @return int 
	 */
	int getTail();

	/**
	 * @brief Rotates the domino
	 * 
	 * Swaps the values in the domino's
	 * head and tail
	 */
	void rotate();
};

#endif /* DOMINO_H */
