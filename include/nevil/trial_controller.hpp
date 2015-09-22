#ifndef _NEVIL_TRIAL_CONTROLLER_HPP_
#define _NEVIL_TRIAL_CONTROLLER_HPP_

#include <iostream>
#include <string>
#include <time.h>
#include <enki/Types.h>

#include "sibling_trial.hpp"
#include "util/logger.hpp"
#include "util/parser.hpp"

namespace nevil
{
  class trial_controller
  {
  public:
    trial_controller();
    trial_controller(int id, unsigned seed, args&);
    ~trial_controller();

    bool run();
    Enki::World *get_trial_world();

  protected:
    void _simulate();
    void _evaluate();
    void _end();

    nevil::sibling_trial *_trial;
    nevil::logger _trial_logger;
    int _trial_id;

    //simulation variables
    int _max_step_num;
    int _population_size;
    int _max_generation_num;
    int _current_generation;
    int _current_individual;
    int _current_step;
  };
}

#endif // _NEVIL_TRIAL_CONTROLLER_HPP_