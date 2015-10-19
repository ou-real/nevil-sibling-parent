#ifndef _NAME_SIBLING_INDIVIDUAL_HPP_
#define _NAME_SIBLING_INDIVIDUAL_HPP_

#include <string>
#include <json/json.h>

#include "individual.hpp"
#include "nevil/util/random.hpp"

namespace nevil
{
  class sibling_individual : public individual
  {
  public:
    sibling_individual();
    sibling_individual(size_t chromo_size, bool is_sibling_a);
    sibling_individual(const std::vector<double> &chromosome, bool is_sibling_a);
    sibling_individual(const sibling_individual &rhs);
    virtual ~sibling_individual();

    sibling_individual* clone(bool is_a) const;
    void mutate(float rate);
    
    const std::string &get_uuid() const;
    const std::string &get_parent_uuid() const;
    Json::Value json() const;
    bool is_a() const;
    bool turned_on_swich() const;
    bool went_light_first() const;
    nevil::sibling_individual &operator=(const nevil::sibling_individual &rhs);

    void increase_fitness(int fitness);
    void set_id(int id);
    void set_turned_on_swich();
    void set_went_light_first();

  protected:
    sibling_individual* clone() const;

    // Indicates whether this is sibling A or not (sibling B)
    bool _is_sibling_a;
    // Indicates whether this individual activated the switch in a given trial
    bool _turned_on_switch;
    // Indicates whether this individual went to light first.
    bool _light_first;
    // Unique identifier for each sibling followed by A or B.
    std::string _uuid;
    // Parent's uuid.
    std::string _parent_uuid;

  };
}

#endif // _NAME_SIBLING_INDIVIDUAL_HPP_