#include "nevil/sibling_parent_robot.hpp"

nevil::sibling_parent_robot::sibling_parent_robot(double x, double y, double angle, bool sibling_nn, double max_speed, const std::string &robot_name, const Enki::Color &color)
: robot(x, y, angle, robot_name, color, max_speed)
, _sibling_neuron(sibling_nn)
{
  _neural_network = nevil::basic_feedforward_nn(_sibling_neuron ? 22 : 19, 2);
}

nevil::sibling_parent_robot::~sibling_parent_robot()
{}

void nevil::sibling_parent_robot::set_individual(nevil::individual *i)
{
  _individual = dynamic_cast<sibling_parent_individual *> (i);
  _neural_network.set_weights(_individual->get_chromosome());
}

bool nevil::sibling_parent_robot::update(const std::vector<object *> &objects)
{
  // Get the sensor information
  std::vector<double> inputs = _get_sensor_inputs();

  if (is_at_switch())
    _individual->set_turned_on_switch();

  if (is_at_light())
  {
    // If the individual has not turned on the switch
    if (!_individual->turned_on_switch())
      _individual->set_went_light_first();

    _individual->increase_fitness(1);
  }

  // If it is a sibling A
  if (_individual->is_a())
  {
    // Add the sibling A inputs, if using 'unique neurons'
    if(_sibling_neuron)
    {
      // std::cout << "Robot A " << std::endl;
      inputs.push_back(1);
      inputs.push_back(0);
      inputs.push_back(0);
    }
  }
  // If it is a sibling B
  else if(_individual->is_b())
  {
    // Add the sibling B inputs, if using 'unique neurons'
    if(_sibling_neuron)
    {
      inputs.push_back(0);
      inputs.push_back(1);
      inputs.push_back(0);
    }
  }
  // If it is a parent
  else {
    // Add the parent inputs, if using 'unique neurons'
    if(_sibling_neuron)
    {
      inputs.push_back(0);
      inputs.push_back(0);
      inputs.push_back(1);
    }
  }
  // Add the bias input
  inputs.push_back(1);
  // Evaluate the neural network
  std::vector <double> output = _neural_network.update(inputs);
  // Pass the output of each NN and convert it to motor velocities
  _set_wheels_speed(output[0], output[1]);
  return true;
}
