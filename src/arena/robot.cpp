#include "nevil/arena/robot.hpp"

nevil::robot::robot()
  : Enki::EPuck(EPuck::CAPABILITY_CAMERA) {}

nevil::robot::robot(double x, double y, double angle, const std::string &robot_name, const Enki::Color &color)
  : Enki::EPuck(EPuck::CAPABILITY_CAMERA)
  , _initial_angle(angle)
  , _initial_position(Enki::Point(x, y))
  , _robot_name(robot_name)
{
  setColor(color);
  reset_position();
}

nevil::robot::~robot() {}

void nevil::robot::reset_position()
{
  this->leftSpeed = 0;
  this->rightSpeed = 0;
  this->pos = _initial_position;
  this->angle = _initial_angle;
}

/*
Color sets for switch and light
0.5 | 0.5 | 0.0 light turned off
1.0 | 1.0 | 0.0 light turned On

0.4 | 0.0 | 1.0 switch turned off
0.4 | 0.5 | 1.0 switch turned On  
*/
const std::vector<double> nevil::robot::_get_sensor_inputs()
{
  //reset the counters
  std::vector<double> sensor_counter(SENSOR_NUM, 0);

  // Each color has 6 groups of pixels
  for (size_t i = 0; i < 6; ++i)
  {
    // One group is 10 pixels
    for (size_t j = 0; j < 10; ++j)
    {
      // switch
      if (camera.image[i * 10 + j].r() == 0.4)
        ++sensor_counter[i];
      // light off
      if (camera.image[i * 10 + j].r() == 0.5)
        ++sensor_counter[i + 6];
      // light on
      if (camera.image[i * 10 + j].r() == 1.0)
        ++sensor_counter[i + 12];
    }
  }

  // adjust the sensor information
  for (size_t i = 0; i < SENSOR_NUM; ++i) 
  {
    if (sensor_counter[i] > 7)
      sensor_counter[i] = 1;
    else
      sensor_counter[i] = 0;
  }

  return sensor_counter;
}

void nevil::robot::_set_wheels_speed(const std::vector<double> &outputs)
{
  this->leftSpeed = (int)outputs[0];
  this->rightSpeed = (int)outputs[1];
}

bool nevil::robot::is_at_switch() const
{
  for (int i = 0; i < 60; ++i)
    if (camera.image[i].r() != 0.4)
      return false;

  return true;
}

bool nevil::robot::is_at_light() const
{
  for (int i = 0; i < 60; ++i)
    if (camera.image[i].r() != 1.0)
      return false;

  return true;
}
