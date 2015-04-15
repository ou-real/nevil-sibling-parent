#ifndef _NEVIL_ARENA_WALL_HPP_
#define _NEVIL_ARENA_WALL_HPP_

#include "nevil/arena/object.hpp"

namespace nevil
{
  class wall : public object
  {
  public:
    wall();
    wall(int x, int y, double size_x, double size_y, double height, double mass = -1);
    virtual ~wall();
    void turn_on();
    void turn_off();

    static const Enki::Color COLOR;
  };
}

#endif // _NEVIL_ARENA_WALL_HPP_