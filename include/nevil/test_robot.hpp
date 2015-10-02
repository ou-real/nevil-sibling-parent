#ifndef _NEVIL_TEST_ROBOT_HPP_
#define _NEVIL_TEST_ROBOT_HPP_


#include "nevil/arena/robot.hpp"
#include "nevil/robot_controller/basic_feedforward_nn.hpp"
#include "nevil/test_individual.hpp"

namespace nevil
{
  class test_robot : public robot
  {
  public:
    test_robot(double x, double y, double angle ,const std::string &robot_name, const Enki::Color &color, double max_speed);
    virtual ~test_robot();

    bool update(const std::vector<object *> &objects);
    void set_individual(nevil::individual *i);

  protected:
    nevil::test_individual *_individual;
    nevil::basic_feedforward_nn _neural_network;
  };
}



#endif // _NEVIL_TEST_ROBOT_HPP_