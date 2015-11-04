#ifndef _NEVIL_SIBLING_PARENT_POPULATION_HPP_
#define _NEVIL_SIBLING_PARENT_POPULATION_HPP_

#include <vector>
#include <algorithm>

#include "nevil/sibling_parent_individual.hpp"
#include "nevil/util/evolution.hpp"

namespace nevil
{
  class sibling_parent_population
  {
  public:
    sibling_parent_population();
    sibling_parent_population(size_t pop_size, bool sibling_neurons, float bracket_ratio ,float mutation_rate);
    virtual ~sibling_parent_population();

    size_t size() const;
    nevil::sibling_parent_individual next_generation();

    sibling_parent_population &operator=(const sibling_parent_population &rhs);
    sibling_parent_individual *operator[](int i);

  protected:
    // Number of individuals created so far
    int _individual_counter;
    size_t _bracket_size;
    float _mutation_rate;
    size_t _population_size;
    std::vector <nevil::sibling_parent_individual *> _individual_list; //Each 1/3-length sub-array represents _population_size sibling A's, sibling B's, and parents

  };
}

#endif // _NEVIL_SIBLING_PARENT_POPULATION_HPP_
