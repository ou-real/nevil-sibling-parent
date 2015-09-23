#include "nevil/trial_controller.hpp"

nevil::trial_controller::trial_controller() {}

nevil::trial_controller::trial_controller(int id, unsigned seed, nevil::args &cl_args)
  : _trial_id(id)
{
  srand(seed);

  //Default Values
  _population_size = 80;
  _max_generation_num = 200;
  _max_step_num = 1000;
  std::string trial_name = "TestTrial";
  float mutation_rate = 0.25;
  float bracket_ratio = 0.1;

  // Reading the command line arguments
  nevil::args::const_iterator it;

  if ((it = cl_args.find("xn")) != cl_args.end())
    trial_name = it->second;

  if ((it = cl_args.find("mg")) != cl_args.end())
    _max_generation_num = stoi(it->second);

  if ((it = cl_args.find("ms")) != cl_args.end())
    _max_step_num = stoi(it->second);

  if ((it = cl_args.find("ps")) != cl_args.end())
    _population_size = stoi(it->second);
  else
    cl_args["ps"] = std::to_string(_population_size);

  if ((it = cl_args.find("br")) != cl_args.end())
  {
    bracket_ratio = stof(it->second);
    if (bracket_ratio < 0 || bracket_ratio > 1)
    {
      printf("Bracket ratio must be between 0 and 1. '%.2f' was given.\nTerminating ...", bracket_ratio);
      exit(-1); 
    }
  }
  else
    cl_args["br"] = std::to_string(bracket_ratio);

  if ((it = cl_args.find("mr")) != cl_args.end())
  {
    mutation_rate = stof(it->second);
    if (mutation_rate < 0 || mutation_rate > 1)
    {
      printf("Mutation rate must be between 0 and 1. '%.2f' was given.\nTerminating ...", mutation_rate);
      exit(-1); 
    }
  }
  else
    cl_args["mr"] = std::to_string(mutation_rate);

  // Creating a log file
  // Logging into a text file example
  _trial_logger.start_new_file(cl_args["xp_path"], "Trial_" + std::to_string(_trial_id) + ".txt");
  // Logging json example
  _trial_json_logger.start_new_file(cl_args["xp_path"], "Trial_" + std::to_string(_trial_id) + ".json");
  _generational_data = Json::Value(Json::arrayValue);

  // Output arguments to file
  // Text style
  _trial_logger << "==Controller Config==" << std::endl;
  _trial_logger << "-Random seed: " << seed << std::endl;
  _trial_logger << "-Number of generations: " << _max_generation_num << std::endl;
  _trial_logger << "-Number of timesteps: " << _max_step_num << std::endl;
  _trial_logger << "==Trial config==" << std::endl;
  _trial_logger << "-Name: " << trial_name << std::endl;
  _trial_logger << "-Population size: " << _population_size << std::endl;
  _trial_logger << "-Bracket Ratio: " << bracket_ratio << std::endl;
  _trial_logger << "-Mutation Rate: " << mutation_rate << std::endl;
  _trial_logger << "==Starting Trial==" << std::endl;

  // JSON style
  _root["config"]["controller"]["randomSeed"] = seed;
  _root["config"]["controller"]["numberOfGenerations"] = _max_generation_num;
  _root["config"]["controller"]["numberOfTimesteps"] = _max_step_num;
  _root["config"]["trial"]["populationSize"] = trial_name;
  _root["config"]["trial"]["bracketRatio"] = bracket_ratio;
  _root["config"]["trial"]["mutationRate"] = mutation_rate;

  // Instantiating a controller
  // If you have more than one controller you can use the controller name to instantiate the right one
  _trial = new nevil::test_trial(cl_args);

  _current_generation = 0;
  _current_individual = 0;
  _current_step = 0;
  printf("-Trial %d: starting\n", _trial_id);
  printf("-Trial %d: running generation %d\n", _trial_id, _current_generation);
}

nevil::trial_controller::~trial_controller() 
{
  delete _trial;
}

Enki::World *nevil::trial_controller::get_trial_world()
{
  return _trial->get_trial_world();
}

bool nevil::trial_controller::run()
{
  if (_current_generation < _max_generation_num)
  {
    if (_current_individual < _population_size)
    {
      if (_current_step == 0 && _current_individual != _population_size)
        _trial->reset();

      if (_current_step < _max_step_num)
      {
        _trial->update();
        ++_current_step;
      }
      else
      {
        ++_current_individual;
        _current_step = 0;
      }
    }
    else
    {
      _evaluate();
      ++_current_generation;
      _current_individual = 0;
      _current_step = 0;
      printf("-Trial %d: running generation %d\n", _trial_id, _current_generation);
    }
    return true;
  }

  _end();
  return false;
}


void nevil::trial_controller::_evaluate()
{
  _trial->epoch();
  // Text logging
  _trial_logger << _current_generation << "\t" << _trial->get_best_individual().get_fitness() << std::endl;

  //JSON logging
  Json::Value data;
  data["generationNumber"] = _current_generation;
  data["maxFitness"] = _trial->get_best_individual().get_fitness();
  _generational_data.append(data);
}

void nevil::trial_controller::_end()
{
  printf("-Trial %d: finished\n", _trial_id);
  //Text logging
  _trial_logger << "==Trial Ended==" << std::endl;
  _trial_logger << "Best chromosome " << _trial->get_best_individual().get_chromosome() << std::endl;
  _trial_logger.close_file();

  //JSON logging
  Json::Value best_chromosome (Json::arrayValue);
  auto best_chromosome_vec = _trial->get_best_individual().get_chromosome();
  for (int i = 0; i < best_chromosome_vec.size(); ++i)
    best_chromosome.append(best_chromosome_vec[i]);

  _root["generationalData"] = _generational_data;
  _root["bestChromosome"] = best_chromosome;
  _trial_json_logger.write(_root);
  _trial_json_logger.close_file();
}