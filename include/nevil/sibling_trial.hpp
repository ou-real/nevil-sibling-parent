#ifndef _NEVIL_SIBLING_TRIAL_HPP_
#define _NEVIL_SIBLING_TRIAL_HPP_


#include "nevil/trial.hpp"

#include "nevil/sibling_population.hpp"
#include "nevil/sibling_arena.hpp"
#include "nevil/util/logger.hpp"
#include "util/parser.hpp"


namespace nevil
{
  class sibling_trial : public trial
  {
  public:
    sibling_trial();
    sibling_trial(nevil::args &cl_args);
    virtual ~sibling_trial();
    
    bool reset();
    bool update();
    bool epoch();
    nevil::sibling_individual get_best_individual() const;
    std::string get_generation_data();
    Enki::World *get_trial_world();


  protected:
    int _population_size;
    int _current_index;

    nevil::sibling_individual _best_individual;
    nevil::sibling_arena *_trial_arena;
    nevil::sibling_population _population;
  };
}

#endif // _NEVIL_SIBLING_TRIAL_HPP_