#include "nevil/sibling_individual.hpp"

nevil::sibling_individual::sibling_individual() {}

nevil::sibling_individual::sibling_individual(size_t chromo_size, bool is_sibling_a)
  : _is_sibling_a(is_sibling_a)
  , _parent_uuid("NONE")
  , _gained_fitness(false)
  , _turned_on_light(false)
{
  _fitness = 0;
  // Assign values to every gene in the chromosome
  _chromosome = std::vector<double>(chromo_size);
  for (int i = 0; i < chromo_size; ++i)
    _chromosome[i] = nevil::random::random_int(-15, 15);
}

nevil::sibling_individual::sibling_individual(const std::vector<double> &chromosome, bool is_sibling_a)
  : _is_sibling_a(is_sibling_a)
  , _parent_uuid("NONE")
  , _gained_fitness(false)
  , _turned_on_light(false)
{
  _fitness = 0;
  _chromosome = chromosome;
}

nevil::sibling_individual::sibling_individual(const sibling_individual &rhs)
  : _is_sibling_a(rhs._is_sibling_a)
  , _uuid(rhs._uuid)
  , _parent_uuid(rhs._parent_uuid)
  , _gained_fitness(rhs._gained_fitness)
  , _turned_on_light(rhs._turned_on_light)
{
  _fitness = rhs._fitness;
  _chromosome = rhs._chromosome;
}

nevil::sibling_individual::~sibling_individual() {}

const std::string &nevil::sibling_individual::get_uuid() const
{
  return _uuid;
}

const std::string &nevil::sibling_individual::get_parent_uuid() const
{
  return _parent_uuid;
}

bool nevil::sibling_individual::is_a() const
{
  return _is_sibling_a;
}

std::string nevil::sibling_individual::str() const
{
  return _parent_uuid + ":" + _uuid + ":S=" + (_turned_on_light ? "1" : "0") + ":L=" + (_gained_fitness ? "1" : "0") + ":" +std::to_string(_fitness);
}

Json::Value nevil::sibling_individual::json() const
{
  Json::Value data;
  data["parentUUID"] = _parent_uuid;
  data["UUID"] = _uuid;
  data["switch"] = _turned_on_light;
  data["light"] = _gained_fitness;
  data["fitness"] = _fitness;
  return data;
}

void nevil::sibling_individual::set_id(int id)
{
  _uuid = std::to_string(id) + (_is_sibling_a ? "A" : "B");
}

void nevil::sibling_individual::set_turn_on_light(bool b)
{
  _turned_on_light = b;
}

void nevil::sibling_individual::increase_fitness(int fitness)
{
  _fitness += fitness;
  _gained_fitness = true;
}

nevil::sibling_individual* nevil::sibling_individual::clone(bool is_a) const
{
  nevil::sibling_individual* new_individual = new sibling_individual(_chromosome, is_a);
  new_individual->_parent_uuid =_uuid;
  return new_individual;
}

nevil::sibling_individual* nevil::sibling_individual::clone() const 
{
  return new sibling_individual();
}

void nevil::sibling_individual::mutate(float rate)
{
  assert (0 <= rate && rate <= 1 && "Mutation rate must be between 0 and 1");
  int gene_index = rand() % (_chromosome.size());
  double r  = ((double) rand() / (RAND_MAX));
  if (r <= rate)
    _chromosome[gene_index] = nevil::random::random_int(-15,15);
}

nevil::sibling_individual &nevil::sibling_individual::operator=(const nevil::sibling_individual &rhs)
{
  _is_sibling_a = rhs._is_sibling_a;
  _uuid = rhs._uuid;
  _parent_uuid = rhs._parent_uuid;
  _gained_fitness = rhs._gained_fitness;
  _turned_on_light = rhs._turned_on_light;
  _fitness = rhs._fitness;
  _chromosome = rhs._chromosome;
  return (*this);
}