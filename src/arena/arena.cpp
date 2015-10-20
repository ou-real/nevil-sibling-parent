#include "nevil/arena/arena.hpp"

nevil::arena::arena() {}

nevil::arena::arena(int world_size_x, int world_size_y, const Enki::Color &arena_color)
{
  _trial_world = new Enki::World(world_size_x, world_size_y, arena_color);
}

nevil::arena::~arena()
{
  delete _trial_world;
}

void nevil::arena::tick()
{
  // step of 50 ms
  _trial_world->step(1.0/30,1);
}

void nevil::arena::reset()
{
  for (auto r : _robot_vector)
    r->reset_position();

  for (auto o : _object_vector)
    o->turn_off();
}

Enki::World *nevil::arena::get_world()
{
  return _trial_world;
}

void nevil::arena::_add_robot(nevil::robot *r)
{
  _robot_vector.push_back(r);
  _trial_world->addObject(r);
}

void nevil::arena::_add_object(nevil::object *o)
{
  _object_vector.push_back(o);
  _trial_world->addObject(o);
}