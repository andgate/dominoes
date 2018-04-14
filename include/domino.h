#ifndef DOMINO_H
#define DOMINO_H

#include <string>
#include <sstream>

class Domino {
private:
	const int m_fst;
	const int m_snd;

public:
	Domino(int first, int second)
		: m_fst(first), m_snd(second)
	{}

	Domino(const Domino &other)
		: m_fst(other.m_fst), m_snd(other.m_snd)
	{}

	~Domino() {}

	int fst() { return m_fst; }
	int snd() { return m_snd; }

	std::string toString() {
		std::ostringstream stringStream;
		stringStream << m_fst << ":" << m_snd;
		return stringStream.str();
	}
};

#endif /* DOMINO_H */