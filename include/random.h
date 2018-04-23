#ifndef RANDOM_H
#define RANDOM_H

#include <ctime> 
#include <cstdlib>

#include <random>

using namespace std;

typedef mt19937 RNG;

class Random
{
private:
    RNG m_rng;
    
public:
    Random()
    : m_rng() {}
    
    ~Random() {}
 
protected:
    /**
    * @brief Seeds random number generator with current time.
    */
    virtual void create()
    {
        m_rng.seed(random_device()());
    }
    
    /**
    * @brief Randomly returns a value from min to max
    * 
    * @param min minimal value that can be generated
    * @param max maximum value that can be generated
    * @return some random integer between 0 and max
    */
    int randomInt(int min, int max)
    {
        uniform_int_distribution<RNG::result_type> dist(min, max);
        return dist(m_rng);
    }

};

#endif /* _H */
