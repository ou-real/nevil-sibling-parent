#include "nevil/test_trial.hpp"

nevil::test_trial::test_trial() {}

nevil::test_trial::test_trial(nevil::args &cl_args)
{
  const int WORLD_SIZE_X = 40;
  const int WORLD_SIZE_Y = 50;

  _population_size = std::stoi(cl_args["ps"]);
  bool sibling_neuron = (cl_args["sn"] == "true");
  float bracket_ratio = std::stof(cl_args["br"]);
  float mutation_rate = std::stof(cl_args["mr"]);

  _trial_arena = new nevil::test_arena(WORLD_SIZE_X, WORLD_SIZE_Y);
  _population = nevil::test_population(_population_size, bracket_ratio, mutation_rate);
  _current_index = 0;
}

nevil::test_trial::~test_trial() 
{
  delete _trial_arena;
}

Enki::World *nevil::test_trial::get_trial_world()
{
  return _trial_arena->get_world();
}

bool nevil::test_trial::update()
{
  _trial_arena->tick();
  _trial_arena->update();
  return true;
}

bool nevil::test_trial::reset()
{
  _trial_arena->reset();
  _trial_arena->set_individuals(_population[_current_index]);
  ++_current_index;
  return true;
}

bool nevil::test_trial::epoch()
{
  _best_individual = _population.next_generation();
  _current_index = 0;
  return true;
}

nevil::test_individual nevil::test_trial::get_best_individual() const
{
  return _best_individual;
}
