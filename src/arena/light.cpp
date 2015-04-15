#include "nevil/arena/light.hpp"

const Enki::Color nevil::light::ON_COLOR = Enki::Color(1.0, 1.0, 0.0);
const Enki::Color nevil::light::OFF_COLOR = Enki::Color(0.5, 0.5, 0.0);

nevil::light::light() {}

nevil::light::light(int x, int y, double size_x, double size_y,
  double height , double mass, double dry_friction_coefficient)
{
  pos = Enki::Point(x, y);
  setRectangular(size_x, size_y, height, mass);
  dryFrictionCoefficient = dry_friction_coefficient;
  turn_off();
}

nevil::light::~light() {}

void nevil::light::turn_on()
{
  setColor(ON_COLOR);
  _is_on = true;
}

void nevil::light::turn_off()
{
  setColor(OFF_COLOR);
  _is_on = false;
}