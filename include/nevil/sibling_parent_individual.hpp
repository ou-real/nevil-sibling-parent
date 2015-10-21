#ifndef _NAME_SIBLING_PARENT_INDIVIDUAL_HPP_
#define _NAME_SIBLING_PARENT_INDIVIDUAL_HPP_

#include <string>
#include <json/json.h>

#include "individual.hpp"
#include "nevil/util/random.hpp"

namespace nevil
{
  class sibling_parent_individual : public individual
  {
  public:
    //is_sibling_a is true if this represents sibling a, false if this represents sibling b, and ignored if this is a parent.
    sibling_parent_individual();									//default constructor
    sibling_parent_individual(size_t chromo_size, bool is_sibling_a, bool is_parent);			
    sibling_parent_individual(const std::vector<double> &chromosome, bool is_sibling_a, bool is_parent);
    sibling_parent_individual(const sibling_parent_individual &rhs);
    virtual ~sibling_parent_individual();

    sibling_parent_individual* clone(bool is_a, bool is_parent=false) const;				//returns a pointer to a non-mutated child of this robot
    void mutate(float rate);										//possibly mutates a single randomly-selected gene to a random value
    
    const std::string &get_uuid() const;								//returns a unique identifier for this individual, ending in A or B
    const std::string &get_parent_uuid() const;								//returns this individual's parent's unique identifier, ending in either A or B unless it was a parent when set_id(int) was last called
    Json::Value json() const;										//returns a JSON representation of this individual
    bool is_a() const;											//returns true iff this individual is marked as sibling A
    bool is_b() const;											//returns true iff this individual is marked as sibling B
    bool is_parent() const;										//returns true iff this individual is marked as the parent
    bool turned_on_switch() const;
    bool went_light_first() const;
    nevil::sibling_parent_individual &operator=(const nevil::sibling_parent_individual &rhs);		//assignment operator

    void increase_fitness(int fitness);									//increments this individual's fitness by the given amount
    void set_id(int id);										//sets the id of this robot uniquely, appended by A or B if it is not a parent
    void set_turned_on_switch();
    void set_went_light_first();

  protected:
    sibling_parent_individual* clone() const;								//returns a pointer to an individual created with the default constructor

    // Indicates whether this is sibling A or not (parent or sibling B)
    bool _is_sibling_a;
    // Indicates whether this is sibling B or not (parent or sibling A)
    bool _is_sibling_b;
    // Indicates whether this is the parent or not (sibling A or sibling B)
    bool _is_parent;
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

#endif // _NAME_SIBLING_PARENT_INDIVIDUAL_HPP_
