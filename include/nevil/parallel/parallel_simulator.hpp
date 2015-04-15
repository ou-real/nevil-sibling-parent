#ifndef _NEVIL_PARALLEL_PARALLEL_HPP_
#define _NEVIL_PARALLEL_PARALLEL_HPP_

#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <algorithm>
#include <math.h>
#include <ctime>

#include "nevil/util/parser.hpp"
#include "nevil/util/system.hpp"
#include "nevil/trial_controller.hpp"

namespace nevil
{
  namespace parallel
  {
    struct thread_data
    {
      args *cl_args;
      size_t start_id;
      size_t end_id;
      unsigned random_seed;
    };

    void simulator(args &cl_args);
    void *_run_trial(void *data);
  }
}

#endif //_NEVIL_PARALLEL_PARALLEL_HPP_