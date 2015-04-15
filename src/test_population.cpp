#include "nevil/test_population.hpp"

nevil::test_population::test_population() {}

nevil::test_population::test_population(size_t pop_size, float bracket_ratio, float mutation_rate)
  : _population_size(pop_size)
  , _bracket_size(size_t(bracket_ratio * pop_size))
  , _mutation_rate(mutation_rate)
{
  _individual_list = std::vector<nevil::test_individual *>(_population_size);
  for (int i = 0; i < _population_size; ++i)
    _individual_list[i] = new nevil::test_individual(38);
}

nevil::test_population::~test_population()
{
  for (auto i : _individual_list)
    delete i;
}

size_t nevil::test_population::size() const
{
  return _individual_list.size();
}

nevil::test_individual nevil::test_population::next_generation()
{
  //sort part
  std::sort(_individual_list.begin(), _individual_list.end(), [](nevil::test_individual *a, nevil::test_individual *b) {
    return (*b) < (*a);
  });

  nevil::test_individual best_individual(*_individual_list[0]);

  // tournament part
  auto selected_individuals = nevil::evolution::tournament_selection(_individual_list, _population_size, _bracket_size);

  for (int i = 0; i < _population_size; ++i)
  {
    delete _individual_list[i];
    _individual_list[i] = selected_individuals[i]->clone();
    _individual_list[i]->mutate(_mutation_rate);
    delete selected_individuals[i];
  }
  return best_individual;
}


nevil::test_population &nevil::test_population::operator=(const nevil::test_population &rhs)
{
  for (auto i : _individual_list)
    delete i;
  _population_size = rhs._population_size;
  _bracket_size = rhs._bracket_size;
  _mutation_rate = rhs._mutation_rate;
  _individual_list = std::vector<nevil::test_individual *> (rhs.size());
  for (int i = 0; i < _individual_list.size(); ++i)
    _individual_list[i] = new nevil::test_individual(*rhs._individual_list[i]);

  return (*this);
}


nevil::test_individual* nevil::test_population::operator[](int i)
{
  return _individual_list[i];
}
