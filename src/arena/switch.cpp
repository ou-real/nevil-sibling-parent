#include "nevil/arena/switch.hpp"

const Enki::Color nevil::switch_object::ON_COLOR = Enki::Color(0.4, 1.0, 1.0);
const Enki::Color nevil::switch_object::OFF_COLOR = Enki::Color(0.4, 0.0, 1.0);

nevil::switch_object::switch_object() {}

nevil::switch_object::switch_object(int x, int y, double size_x, double size_y,
  double height, double mass, double dry_friction_coefficient)
{
  pos = Enki::Point(x, y);
  setRectangular(size_x, size_y, height, mass);
  dryFrictionCoefficient = dry_friction_coefficient;
  turn_off();
}

nevil::switch_object::~switch_object() {}

void nevil::switch_object::turn_on()
{
  setColor(ON_COLOR);
  _is_on = true;
}
void nevil::switch_object::turn_off()
{
  setColor(OFF_COLOR);
  _is_on = false;
}