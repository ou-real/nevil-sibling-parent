#ifndef _NEVIL_TEST_TRIAL_HPP_
#define _NEVIL_TEST_TRIAL_HPP_

#include "nevil/trial.hpp"
#include "nevil/test_arena.hpp"
#include "nevil/test_population.hpp"
#include "nevil/util/logger.hpp"
#include "util/parser.hpp"

namespace nevil
{
  class test_trial : public trial
  {
  public:
    test_trial();
    test_trial(nevil::args &cl_args);
    virtual ~test_trial();
    
    bool reset();
    bool update();
    bool epoch();
    nevil::test_individual get_best_individual() const;
    Enki::World *get_trial_world();


  protected:
    int _population_size;
    int _current_index;
    nevil::test_arena *_trial_arena;
    nevil::test_individual _best_individual;
    nevil::test_population _population;
  };
}

#endif // _NEVIL_SIBLING_TRIAL_HPP_