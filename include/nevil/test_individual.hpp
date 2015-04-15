#ifndef _NAME_TEST_INDIVIDUAL_HPP_
#define _NAME_TEST_INDIVIDUAL_HPP_

#include "individual.hpp"
#include "nevil/util/random.hpp"
#include <string>

namespace nevil
{
  class test_individual : public individual
  {
  public:
    test_individual();
    test_individual(size_t chromo_size);
    test_individual(const std::vector<double> &chromosome);
    test_individual(const test_individual &rhs);
    virtual ~test_individual();

    void increase_fitness(int fitness);
    test_individual* clone() const;
    void mutate(float rate);
    
    nevil::test_individual &operator=(const nevil::test_individual &rhs);
  };
}

#endif // _NAME_TEST_INDIVIDUAL_HPP_