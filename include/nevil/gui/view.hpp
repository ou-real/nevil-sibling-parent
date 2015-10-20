#ifndef _NAME_GUI_VIEW_HPP_
#define _NAME_GUI_VIEW_HPP_

#include <iostream>
#include <QKeyEvent>
#include <QtGui>
#include <enki/viewer/Viewer.h>
#include "nevil/trial_controller.hpp"


namespace nevil
{
  class view : public Enki::ViewerWidget
  {
  public:
    view(nevil::trial_controller*, QWidget *parent = 0);
    ~view();

    virtual void timerEvent(QTimerEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void sceneCompletedHook();

  protected:
    nevil::trial_controller *_controller;
    bool _pause_gui;
    int _frame_number;
    int _skip_frame;
  };
}

#endif // _NAME_GUI_VIEW_HPP_