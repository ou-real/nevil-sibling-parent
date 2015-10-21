#include "nevil/sibling_parent_population.hpp"

int nevil::sibling_parent_population::_individual_counter = 0;

nevil::sibling_parent_population::sibling_parent_population() {}

nevil::sibling_parent_population::sibling_parent_population(size_t pop_size, bool sibling_neurons, float bracket_ratio, float mutation_rate)
  : _population_size(pop_size)
  , _bracket_size(int(bracket_ratio * pop_size))
  , _mutation_rate(mutation_rate)
{
  _individual_list = std::vector<nevil::sibling_parent_individual *>(3 * _population_size);
  int genome_size = 38 + 6*sibling_neurons; //sibling_neurons will cast to either 0 or 1. 2*(1 for isA, 1 for isB, 1 for isParent) are the sibling neurons
  for (int i = 0; i < _population_size; ++i)
  {
	//create parent
    _individual_list[i + 2*_population_size] = new nevil::sibling_parent_individual(genome_size, false, true);
    _individual_list[i + 2*_population_size]->set_id(_individual_counter);
	//create sibling A
    _individual_list[i] = _individual_list[i + 2*_population_size]->clone(true);
    _individual_list[i]->set_id(_individual_counter);
	//create sibling B
    _individual_list[i + _population_size] = _individual_list[i + 2*_population_size]->clone(false);
    _individual_list[i + _population_size]->mutate(_mutation_rate);
    _individual_list[i + _population_size]->set_id(_individual_counter);
	
    ++_individual_counter;
  }
}

nevil::sibling_parent_population::~sibling_parent_population()
{
  for (auto i : _individual_list)
    delete i;
}

size_t nevil::sibling_parent_population::size() const
{
  return _individual_list.size();
}

nevil::sibling_parent_individual nevil::sibling_parent_population::next_generation()
{
  // tournament part
  //We need to save this bit!! @fixme
  auto selected_individuals = nevil::evolution::tournament_selection(_individual_list.begin(), _individual_list.end(), _population_size, _bracket_size);
  nevil::sibling_parent_individual* max_individual = _individual_list[0];
  std::vector<nevil::sibling_parent_individual *> new_individuals(3 * _population_size);

	//automatically ignores the parents, conveniently
  for (int i = 0; i < _population_size; ++i)
  {
    // Finding the best individual
    if ((*_individual_list[i]) > (*max_individual))
      max_individual = _individual_list[i];

    new_individuals[i] = _individual_list[selected_individuals[i]]->clone(true, false);
    new_individuals[i]->set_id(_individual_counter);
    new_individuals[i]->mutate(_mutation_rate);


    // Finding the best individual
    if ((*_individual_list[i + _population_size]) > (*max_individual))
      max_individual = _individual_list[i + _population_size];

    new_individuals[i + _population_size] = _individual_list[selected_individuals[i]]->clone(false, false);
    new_individuals[i + _population_size]->set_id(_individual_counter);
    new_individuals[i + _population_size]->mutate(_mutation_rate);

    //create the parents
    new_individuals[i + 2*_population_size] = _individual_list[selected_individuals[i]]->clone(false, true);
    new_individuals[i + 2*_population_size]->set_id(_individual_counter);

    ++_individual_counter;
  }

  nevil::sibling_parent_individual best_individual(*max_individual);
  for (auto i : _individual_list)
    delete i;

  _individual_list = new_individuals;

  return best_individual;
}


nevil::sibling_parent_population &nevil::sibling_parent_population::operator=(const nevil::sibling_parent_population &rhs)
{
  for (auto i : _individual_list)
    delete i;
  _population_size = rhs._population_size;
  _mutation_rate = rhs._mutation_rate;
  _bracket_size = rhs._bracket_size;
  _individual_list = std::vector<nevil::sibling_parent_individual *> (rhs.size());
  for (int i = 0; i < _individual_list.size(); ++i)
    _individual_list[i] = new nevil::sibling_parent_individual(*rhs._individual_list[i]);

  return (*this);
}


nevil::sibling_parent_individual* nevil::sibling_parent_population::operator[](int i)
{
  return _individual_list[i];
}
