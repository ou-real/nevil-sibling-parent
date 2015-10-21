#ifndef _NEVIL_SIBLING_PARENT_TRIAL_HPP_
#define _NEVIL_SIBLING_PARENT_TRIAL_HPP_

#include <json/json.h>

#include "nevil/trial.hpp"
#include "nevil/sibling_parent_population.hpp"
#include "nevil/sibling_parent_arena.hpp"
#include "nevil/util/logger.hpp"
#include "util/parser.hpp"


namespace nevil
{
  class sibling_parent_trial : public trial
  {
  public:
    sibling_parent_trial();
    sibling_parent_trial(nevil::args &cl_args);
    virtual ~sibling_parent_trial();
    
    bool reset();
    bool update();
    bool epoch();
    nevil::sibling_parent_individual get_best_individual() const;
    Json::Value get_generation_data();
    Enki::World *get_trial_world();


  protected:
    int _population_size;
    int _current_index;

    nevil::sibling_parent_individual _best_individual;
    nevil::sibling_parent_arena *_trial_arena;
    nevil::sibling_parent_population _population;
  };
}

#endif // _NEVIL_SIBLING_PARENT_TRIAL_HPP_
