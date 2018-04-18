#ifndef COIN_H
#define COIN_H

#include <cstdlib>


bool flipCoin()
{
	std::srand(std::time(nullptr));
	return std::rand() % 10000 < 5000;
}

#endif /* COIN_H */