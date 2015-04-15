#ifndef _NEVIL_UTIL_SERIALIZATION_HPP
#define _NEVIL_UTIL_SERIALIZATION_HPP

#include <iostream>
#include <enki/PhysicalEngine.h>

void serialize(std::ostream &out, double rhs);
void serialize(std::ostream &out, const Enki::Color &rhs);
void serialize(std::ostream &out, const Enki::Vector &rhs);

void deserialize(std::istream &in, double &rhs);
void deserialize(std::istream &in, Enki::Color &rhs);
void deserialize(std::istream &in, Enki::Vector &rhs);

#endif // _NEVIL_UTIL_SERIALIZATION_HPP