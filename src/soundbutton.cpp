#include "soundbutton.h"

SoundButton::SoundButton(QWidget *parent):
    QPushButton(parent)
{
}

void SoundButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
        emit rightClicked(this);
}
