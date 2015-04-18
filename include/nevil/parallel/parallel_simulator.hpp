#ifndef _NEVIL_PARALLEL_PARALLEL_HPP_
#define _NEVIL_PARALLEL_PARALLEL_HPP_

#include <stdlib.h>
#include <string>
#include <algorithm>
#include <thread>

#include "nevil/util/parser.hpp"
#include "nevil/util/system.hpp"
#include "nevil/trial_controller.hpp"

namespace nevil
{
  namespace parallel
  {
    void simulator(args &cl_args);
    void _run_trial(nevil::args cl_args, size_t start_id, size_t end_id, unsigned random_seed);
  }
}

#endif //_NEVIL_PARALLEL_PARALLEL_HPP_