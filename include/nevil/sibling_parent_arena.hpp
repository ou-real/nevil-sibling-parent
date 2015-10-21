#ifndef _NEVIL_SIBLING_PARENT_ARENA_HPP_
#define _NEVIL_SIBLING_PARENT_ARENA_HPP_

#include "nevil/arena/arena.hpp"
#include "nevil/arena/light.hpp"
#include "nevil/arena/switch.hpp"
#include "nevil/arena/wall.hpp"

#include "nevil/sibling_parent_individual.hpp"
#include "nevil/sibling_parent_robot.hpp"


namespace nevil
{
  class sibling_parent_arena : public arena
  {
  public:
    sibling_parent_arena(int size_x, int size_y, bool sibling_neuron, double speed_A, double speed_B, double speed_P, double angle_A, double angle_B , double angle_P, const Enki::Color &arena_color = Enki::Color(0.9, 0.9, 0.9));
    virtual ~sibling_parent_arena();

    void set_individuals(sibling_parent_individual *sibling_a, sibling_parent_individual *sibling_b, sibling_parent_individual *parent);
    bool update();

  protected:
    bool _sibling_neuron;
  };
}
#endif // _NEVIL_SIBLING_PARENT_ARENA_HPP_
