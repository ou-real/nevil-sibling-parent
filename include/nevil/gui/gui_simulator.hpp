#ifndef _NAME_GUI_SIMULATOR_HPP_
#define _NAME_GUI_SIMULATOR_HPP_

#include "nevil/util/parser.hpp"
#include "nevil/gui/view.hpp"
#include "nevil/trial_controller.hpp"

namespace nevil
{
  class gui_simulator
  {
  public:
    gui_simulator(nevil::args &cl_args);
    ~gui_simulator();

  private:
    nevil::trial_controller *_controller;
    nevil::view *_view;
  };
}

#endif //_NAME_GUI_SIMULATOR_HPP_