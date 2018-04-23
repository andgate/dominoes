#ifndef COIN_H
#define COIN_H

#include <cstdlib>

/**
 * @brief Randomly returns true or false
 * 
 * @return true 
 * @return false 
 */
bool flipCoin()
{
	std::srand(std::time(nullptr));
	return std::rand() % 10000 < 5000;
}

#endif /* COIN_H */
