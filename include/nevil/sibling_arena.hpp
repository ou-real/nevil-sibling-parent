#ifndef _NEVIL_SIBLING_ARENA_HPP_
#define _NEVIL_SIBLING_ARENA_HPP_

#include "nevil/arena/arena.hpp"
#include "nevil/arena/light.hpp"
#include "nevil/arena/switch.hpp"
#include "nevil/arena/wall.hpp"

#include "nevil/sibling_individual.hpp"
#include "nevil/sibling_robot.hpp"

namespace nevil
{
  class sibling_arena : public arena
  {
  public:
    sibling_arena(int size_x, int size_y, bool sibling_neuron, double speed_A, double speed_B, double angle_A, double angle_B , const Enki::Color &arena_color = Enki::Color(0.9, 0.9, 0.9));
    virtual ~sibling_arena();

    void set_individuals(sibling_individual *sibling_a, sibling_individual *sibling_b);
    bool update();

  protected:
    bool _sibling_neuron;
  };
}
#endif // _NEVIL_SIBLING_ARENA_HPP_
