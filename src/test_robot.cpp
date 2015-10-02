#include "nevil/test_robot.hpp"

nevil::test_robot::test_robot(double x, double y, double angle ,const std::string &robot_name, const Enki::Color &color, double max_speed)
: robot(x, y, angle, robot_name, color, max_speed)
{
  _neural_network = nevil::basic_feedforward_nn(19, 2);
}

nevil::test_robot::~test_robot() {}

void nevil::test_robot::set_individual(nevil::individual *i)
{
  _individual = dynamic_cast<nevil::test_individual *> (i);
  _neural_network.set_weights(_individual->get_chromosome());
}

bool nevil::test_robot::update(const std::vector<object *> &objects)
{
  // Increase robot's fitness if its under the light
  if (is_at_light())
    _individual->increase_fitness(1);
  // Get the sensor information
  std::vector<double> inputs = _get_sensor_inputs();
  // Add the bias input
  inputs.push_back(1);
  // Evaluate the neural network
  std::vector <double> output = _neural_network.update(inputs);
  // Pass the output of each NN and convert it to motor velocities
  _set_wheels_speed(output[0], output[1]);
  return true;
}