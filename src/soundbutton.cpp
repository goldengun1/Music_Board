#include "soundbutton.h"

SoundButton::SoundButton(QWidget *parent):
    QPushButton(parent)
{
}

void SoundButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
        emit rightClicked(this);
}
