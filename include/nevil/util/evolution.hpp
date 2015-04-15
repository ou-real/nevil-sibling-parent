#ifndef _NEVIL_UTIL_EVOLUTION_HPP_
#define _NEVIL_UTIL_EVOLUTION_HPP_

#include <vector>
#include <iostream>

namespace nevil
{
  namespace evolution
  {
    template<typename T>
    inline std::vector<T*> tournament_selection(const std::vector<T*> &population, int new_size, size_t pool_size)
    {
      int pop_size = population.size();
      assert (pool_size <= pop_size && "ERROR: the bracket size is bigger than population size.\nTerminating...");

      int winner;
      std::vector<int> bracket(pool_size);
      std::vector<T*> new_population(new_size);

      // Create the population
      for (int i = 0; i < new_size; ++i) 
      {
        bracket.clear();
        winner = pop_size - 1;

        // Creates the bracket
        for (int j = 0; j < pool_size; ++j) 
        {
          bracket[j] = rand() % pop_size;

          // Ensures that the same individual is not put in the bracket more than once
          for (int k = 0; k < j; ++k)
          {
            if (bracket[j] == bracket[k]) 
            {
              bracket[j] = rand() % pop_size;
              k = 0;
            }
            // Individuals with lower sorted indices will have higher fitness
            if (bracket[j] < winner)
              winner = bracket[j];
          }
        }
        new_population[i] = new T(*population[winner]);
      }
      return new_population;
    }
  }
}

#endif // _NEVIL_UTIL_EVOLUTION_HPP_