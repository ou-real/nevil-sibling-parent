#ifndef _NEVIL_UTIL_SERIALIZATION_HPP
#define _NEVIL_UTIL_SERIALIZATION_HPP

#include <iostream>
#include <enki/PhysicalEngine.h>

namespace
{
  void serialize(std::ostream &out, double rhs)
  {
    out.write(reinterpret_cast<const char *>(&rhs), sizeof rhs);
  }

  void serialize(std::ostream &out, const Enki::Color &rhs)
  {
    for(auto d : rhs.components)
      serialize(out, d);
  }

  void serialize(std::ostream &out, const Enki::Vector &rhs)
  {
    serialize(out, rhs.x);
    serialize(out, rhs.y);
  }

  void deserialize(std::istream &in, double &rhs)
  {
    in.read(reinterpret_cast<char *>(&rhs), sizeof rhs);
  }

  void deserialize(std::istream &in, Enki::Color &rhs)
  {
    for (auto &d : rhs.components)
      deserialize(in, d);
  }

  void deserialize(std::istream &in, Enki::Vector &rhs)
  {
    deserialize(in, rhs.x);
    deserialize(in, rhs.y);
  }
}

#endif // _NEVIL_UTIL_SERIALIZATION_HPP