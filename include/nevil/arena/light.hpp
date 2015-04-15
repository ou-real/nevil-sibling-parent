#ifndef _NEVIL_ARENA_LIGHT_HPP_
#define _NEVIL_ARENA_LIGHT_HPP_

#include "nevil/arena/object.hpp"

namespace nevil
{
  class light : public object
  {
  public:
    light();
    light(int x, int y, double size_x, double size_y, double height,
     double mass, double dry_friction_coefficient);
    virtual ~light();
    void turn_on();
    void turn_off();

    static const Enki::Color ON_COLOR;
    static const Enki::Color OFF_COLOR;
  };
}

#endif // _NEVIL_ARENA_LIGHT_HPP_