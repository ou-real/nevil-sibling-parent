#ifndef _NEVIL_UTIL_RANDOM_HPP_
#define _NEVIL_UTIL_RANDOM_HPP_

#include <stdlib.h>
#include <assert.h>
#include <iostream>

namespace nevil
{
  namespace random
  {
    int random_int(int lower_bound, int upper_bound);
  }
}

#endif // _NEVIL_UTIL_RANDOM_HPP_