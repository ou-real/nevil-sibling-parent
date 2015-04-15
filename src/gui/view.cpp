#include "nevil/gui/view.hpp"

nevil::view::view(Enki::World *world, QWidget *parent)
  : Enki::ViewerWidget(world, parent)
{
  pos.setX(-world->w * 1.1);
  pos.setY(-world->h * 0.5);
  altitude = world->h * 0.6;
  pitch = M_PI/5;
  yaw = -M_PI;

  _frame_number = 0;
  _skip_frame = 0;
  startTimer(0);
}

nevil::view::~view() {}

void nevil::view::timerEvent(QTimerEvent *event)
{
    updateGL();
}

void nevil::view::update()
{
  if(_frame_number == _skip_frame)
  {
    updateGL();
    _frame_number = -1;
  }
  ++_frame_number;
}

void nevil::view::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Plus)
  {
    if(_skip_frame + 1 <= 30)
      ++_skip_frame;
    _frame_number = 0;
    std::cout << "-Speeding simulation: " << _skip_frame << " skipped frames" << std::endl;
  }
  else if(event->key() == Qt::Key_Minus)
  {
    if(_skip_frame - 1 >= 0)
      --_skip_frame;
    _frame_number = 0;
    std::cout << "-Slowing simulation: "<< _skip_frame <<" skipped frames "<< std::endl;
  }
}

void nevil::view::sceneCompletedHook()
{
  glColor3d(0,0,0);
  renderText(10, height()-50, tr("Rotate camera by moving mouse while pressing ctrl/cmd+left mouse button"));
  renderText(10, height()-30, tr("Move camera on x/y by moving mouse while pressing ctrl/cmd+shift+left mouse button"));
  renderText(10, height()-10, tr("Move camera on z by moving mouse while pressing ctrl/cmd+shift+right mouse button"));
}