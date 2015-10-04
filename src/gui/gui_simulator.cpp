#include "nevil/gui/gui_simulator.hpp"

nevil::gui_simulator::gui_simulator(nevil::args &cl_args)
{
  unsigned seed = rand();

  if (cl_args.find("rs") != cl_args.end())
    seed = std::stoll(cl_args["rs"]);

  _controller = new nevil::trial_controller (1, seed, cl_args);
  _view = new nevil::view(_controller);
  _view->show();
}

nevil::gui_simulator::~gui_simulator()
{
  delete _view;
  delete _controller;
}