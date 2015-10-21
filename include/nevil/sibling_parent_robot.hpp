#ifndef _NEVIL_SIBLING_PARENT_ROBOT_HPP_
#define _NEVIL_SIBLING_PARENT_ROBOT_HPP_


#include "nevil/arena/robot.hpp"
#include "nevil/robot_controller/basic_feedforward_nn.hpp"
#include "nevil/sibling_parent_individual.hpp"

namespace nevil
{
  class sibling_parent_robot : public robot
  {
  public:
    sibling_parent_robot(double x, double y, double angle, bool sibling_nn, double max_speed, const std::string &robot_name, const Enki::Color &color); //sibling_nn is true if using 'unique neurons'
    virtual ~sibling_parent_robot();

    bool update(const std::vector<object *> &objects);
    void set_individual(nevil::individual *i);

  protected:
    bool _sibling_neuron;
    nevil::sibling_parent_individual *_individual;
    nevil::basic_feedforward_nn _neural_network;
  };
}



#endif // _NEVIL_SIBLING_PARENT_ROBOT_HPP_
