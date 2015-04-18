#ifndef _NEVIL_SIBLING_ROBOT_HPP_
#define _NEVIL_SIBLING_ROBOT_HPP_


#include "nevil/arena/robot.hpp"
#include "nevil/robot_controller/basic_feedforward_nn.hpp"
#include "nevil/sibling_individual.hpp"

namespace nevil
{
  class sibling_robot : public robot
  {
  public:
    sibling_robot(double x, double y, double angle, bool _sibling_nn ,const std::string &robot_name, const Enki::Color &color);
    virtual ~sibling_robot();

    bool update(const std::vector<object *> &objects);
    void set_individual(nevil::individual *i);

  protected:
    bool _sibling_neuron;
    nevil::sibling_individual *_individual;
    nevil::basic_feedforward_nn _neural_network;
  };
}



#endif // _NEVIL_SIBLING_ROBOT_HPP_