#ifndef __RANDOMNUMBERGENERATOR
#define __RANDOMNUMBERGENERATOR

#include <random>
#include <chrono>

class RandomNumberGenerator
{
  public:
  
  RandomNumberGenerator()
  {
    unsigned seed = generateRandomSeed();
    this->generator = std::default_random_engine(seed);
    this->distribution = std::uniform_int_distribution<unsigned>();
  }
  
  ~RandomNumberGenerator()
  {
    if (p_instance != nullptr)
    {
      delete p_instance;
    }
  }
  
  static RandomNumberGenerator * instance()
  {
    if (p_instance == 0)
    {
      p_instance = new RandomNumberGenerator;
    }
    
    return p_instance;
  }
  
  unsigned get(unsigned mod)
  {
    if (mod == 0)
    {
      return 0;
    }
    else
    {
      return distribution(generator) % mod;
    }
  }
  
  private:
  
  static RandomNumberGenerator * p_instance;
  
  std::default_random_engine generator;
  std::uniform_int_distribution<unsigned> distribution;
  
  unsigned generateRandomSeed()
  {
    return (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
  }
};

RandomNumberGenerator * RandomNumberGenerator::p_instance = 0;

#endif