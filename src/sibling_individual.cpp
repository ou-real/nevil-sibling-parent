#include "nevil/sibling_individual.hpp"

nevil::sibling_individual::sibling_individual() {}

nevil::sibling_individual::sibling_individual(size_t chromo_size, bool is_sibling_a)
  : _is_sibling_a(is_sibling_a)
  , _parent_uuid("NONE")
  , _light_first(false)
  , _turned_on_switch(false)
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
  , _light_first(false)
  , _turned_on_switch(false)
{
  _fitness = 0;
  _chromosome = chromosome;
}

nevil::sibling_individual::sibling_individual(const sibling_individual &rhs)
  : _is_sibling_a(rhs._is_sibling_a)
  , _uuid(rhs._uuid)
  , _parent_uuid(rhs._parent_uuid)
  , _light_first(rhs._light_first)
  , _turned_on_switch(rhs._turned_on_switch)
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

bool nevil::sibling_individual::turned_on_swich() const
{
  return _turned_on_switch;
}

bool nevil::sibling_individual::went_light_first() const
{
  return _light_first;
}

Json::Value nevil::sibling_individual::json() const
{
  Json::Value data;
  data["parentUUID"] = _parent_uuid;
  data["UUID"] = _uuid;
  data["switch"] = _turned_on_switch;
  data["lightFirst"] = _light_first;
  data["fitness"] = _fitness;
  return data;
}

void nevil::sibling_individual::set_id(int id)
{
  _uuid = std::to_string(id) + (_is_sibling_a ? "A" : "B");
}

void nevil::sibling_individual::set_turned_on_swich()
{
  _turned_on_switch = true;
}

void nevil::sibling_individual::set_went_light_first()
{
  _light_first = true;
}

void nevil::sibling_individual::increase_fitness(int fitness)
{
  _fitness += fitness;
}

nevil::sibling_individual* nevil::sibling_individual::clone(bool is_a) const
{
  nevil::sibling_individual* new_individual = new sibling_individual(_chromosome, is_a);
  new_individual->_parent_uuid = _uuid;
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
  _light_first = rhs._light_first;
  _turned_on_switch = rhs._turned_on_switch;
  _fitness = rhs._fitness;
  _chromosome = rhs._chromosome;
  return (*this);
}