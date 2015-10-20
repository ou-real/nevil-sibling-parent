#ifndef _NEVIL_ARENA_ARENA_HPP_
#define _NEVIL_ARENA_ARENA_HPP_

#include "nevil/arena/object.hpp"
#include "nevil/arena/robot.hpp"

namespace nevil
{
  class arena
  {
  public:
    arena();
    arena(int size_x, int size_y, const Enki::Color &arena_color);
    virtual ~arena(); 

    void tick();
    virtual bool update() = 0;
    virtual void reset();

    Enki::World* get_world();

  protected:
    void _add_object(nevil::object *o);
    void _add_robot(nevil::robot *r);

    Enki::World *_trial_world;
    std::vector<robot*> _robot_vector;
    std::vector<object*> _object_vector;
  };
}
#endif // _NEVIL_ARENA_ARENA_HPP_