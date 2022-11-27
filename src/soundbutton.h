#ifndef SOUNDBUTTON_H
#define SOUNDBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class SoundButton : public QPushButton
{
    Q_OBJECT
public:
    SoundButton(QWidget *parent = 0);
    uint32_t id;

private slots:
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void rightClicked(SoundButton *button);

public slots:

};

#endif // SOUNDBUTTON_H
