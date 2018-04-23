#ifndef DOMINO_H
#define DOMINO_H

#include <string>
#include <sstream>


using namespace std;


class Domino {
private:
	int m_head;
	int m_tail;

public:
	Domino(int headNum, int tailNum)
		: m_head(headNum)
		, m_tail(tailNum)
	{}

	Domino(const Domino &other)
		: m_head(other.m_head)
		, m_tail(other.m_tail)
	{}

	~Domino() {}

	/**
	 * @brief Get the Head object
	 * 
	 * @return int 
	 */
	int getHead() { return m_head; }

	/**
	 * @brief Get the Tail object
	 * 
	 * @return int 
	 */
	int getTail() { return m_tail; }

	/**
	 * @brief Rotates the domino
	 * 
	 * Swaps the values in the domino's
	 * head and tail
	 */
	void rotate() {
		int tmp = m_head;
		m_head = m_tail;
		m_tail = tmp;
	}
};

#endif /* DOMINO_H */
