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
  std::string trial_name = "SiblingParentNeuronTrial";
  float mutation_rate = 0.25;
  float bracket_ratio = 0.10;

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


  // Sibling Neuron Parameter
  if ((it = cl_args.find("sn")) != cl_args.end())
    _root["config"]["siblingNeuron"] = (it->second == "true");
  else
    cl_args["sn"] = "false";

  //Speed Parameter
  if ((it = cl_args.find("speedA")) != cl_args.end())
    _root["config"]["speedA"] = std::stod(it->second);
  else
    cl_args["speedA"] = "12";

  if ((it = cl_args.find("speedB")) != cl_args.end())
    _root["config"]["speedB"] = std::stod(it->second);
  else
    cl_args["speedB"] = "12";

  if ((it = cl_args.find("speedP")) != cl_args.end())
    _root["config"]["speedP"] = std::stod(it->second);
  else
    cl_args["speedP"] = "12";

  //Angle Parameter
  if ((it = cl_args.find("angleA")) != cl_args.end())
    _root["config"]["angleA"] = std::stod(it->second);
  else
    cl_args["angleA"] = "0";

  if ((it = cl_args.find("angleB")) != cl_args.end())
    _root["config"]["angleB"] = std::stod(it->second);
  else
    cl_args["angleB"] = "0";

  if ((it = cl_args.find("angleP")) != cl_args.end())
    _root["config"]["angleP"] = std::stod(it->second);
  else
    cl_args["angleB"] = "0";

  // Creating a log file
  _trial_logger.start_new_file(cl_args["xp_path"], "Trial_" + std::to_string(_trial_id) + ".json");
  _generational_data = Json::Value(Json::arrayValue);

  // JSON style
  _root["config"]["trialName"] = trial_name;
  _root["config"]["randomSeed"] = seed;
  _root["config"]["numberOfGenerations"] = _max_generation_num;
  _root["config"]["numberOfTimesteps"] = _max_step_num;
  _root["config"]["populationSize"] = _population_size;
  _root["config"]["bracketRatio"] = bracket_ratio;
  _root["config"]["mutationRate"] = mutation_rate;

  // Instantiating a trial
  if (trial_name == "SiblingParentNeuronTrial"){
    cl_args["angleA"] = "0";
    cl_args["angleB"] = "0";
    cl_args["angleP"] = "0";
    _trial = new nevil::sibling_parent_trial(cl_args);
  }
  else if (trial_name == "SiblingParentAsymTrial")
  {
    cl_args["sn"] = "false";
    _trial = new nevil::sibling_parent_trial(cl_args);
  }
  else if (trial_name == "SiblingParentDetectionTrial")
  {
    cl_args["sn"] = "false";
    _trial = new nevil::sibling_sibling_trial(cl_args); // Change this
  }
  else
  {
    printf("Trial '%s' is not defined.\nTerminating...\n", trial_name.c_str());
    exit(1);
  }

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
  Json::Value data;
  data["generationNumber"] = _current_generation;
  data["individualList"] = _trial->get_generation_data();
 
  _trial->epoch();

  data["bestIndividual"] = _trial->get_best_individual().json();
  _generational_data.append(data);
}

void nevil::trial_controller::_end()
{
  printf("-Trial %d: finished\n", _trial_id);
  _root["generationalData"] = _generational_data;
  _trial_logger.write(_root);
  _trial_logger.close_file();
}
