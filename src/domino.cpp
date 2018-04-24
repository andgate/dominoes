#include "domino.h"


Domino::Domino(int headNum, int tailNum)
	: m_head(headNum)
	, m_tail(tailNum)
{}

Domino::Domino(const Domino &other)
	: m_head(other.m_head)
	, m_tail(other.m_tail)
{}

Domino::~Domino() {}


int Domino::getHead()
{
	return m_head;
}

int Domino::getTail()
{
	return m_tail;
}

void Domino::rotate()
{
	int tmp = m_head;
	m_head = m_tail;
	m_tail = tmp;
}
