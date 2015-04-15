#include "nevil/arena/wall.hpp"

const Enki::Color nevil::wall::COLOR = Enki::Color(0.9, 0.9, 0.9);

nevil::wall::wall()
{
  setColor(COLOR);
}

nevil::wall::wall(int x, int y, double size_x, double size_y, double height , double mass)
{
  pos = Enki::Point(x, y);
  setRectangular(size_x, size_y, height, mass);
  setColor(COLOR);
}

nevil::wall::~wall() {}

void nevil::wall::turn_on() {}
void nevil::wall::turn_off() {}