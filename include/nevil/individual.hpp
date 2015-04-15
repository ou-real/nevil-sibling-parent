#ifndef _NAME_INDIVIDUAL_HPP_
#define _NAME_INDIVIDUAL_HPP_

#include <vector>

namespace nevil
{
  class individual
  {
  public:
    virtual void increase_fitness(int fitness) = 0;

    virtual individual* clone() const = 0;
    virtual void mutate(float rate) = 0;

    int get_fitness() const { return _fitness; };
    const std::vector<double> &get_chromosome() const { return _chromosome; };
    bool operator> (const individual &rhs) { return _fitness > rhs._fitness; }
    bool operator< (const individual &rhs) { return _fitness < rhs._fitness; }

  protected:
    int _fitness;
    std::vector<double> _chromosome;
  };
}
#endif // _INDIVIDUAL_HPP_