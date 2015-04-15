#ifndef _NEVIL_ARENA_SWITCH_HPP_
#define _NEVIL_ARENA_SWITCH_HPP_

#include "nevil/arena/object.hpp"

namespace nevil
{
  class switch_object : public object
  {
  public:
    switch_object();
    switch_object(int x, int y, double size_x, double size_y, double height,
      double mass, double dry_friction_coefficient);
    virtual ~switch_object();
    void turn_on();
    void turn_off();

    static const Enki::Color ON_COLOR;
    static const Enki::Color OFF_COLOR;
  };
}

#endif // _NEVIL_ARENA_SWITCH_HPP_