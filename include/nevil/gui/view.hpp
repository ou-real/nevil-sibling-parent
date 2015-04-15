#ifndef _NAME_GUI_VIEW_HPP_
#define _NAME_GUI_VIEW_HPP_

#include <iostream>
#include <QKeyEvent>
#include <QtGui>
#include <enki/viewer/Viewer.h>

namespace nevil
{
  class view : public Enki::ViewerWidget
  {
  public:
    view(Enki::World*, QWidget *parent = 0);
    ~view();

    void update();
    virtual void timerEvent(QTimerEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void sceneCompletedHook();

  protected:
    int _frame_number;
    int _skip_frame;
  };
}

#endif // _NAME_GUI_VIEW_HPP_