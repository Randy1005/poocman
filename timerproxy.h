#ifndef TIMERPROXY_H
#define TIMERPROXY_H

#include <QObject>
#include <QDebug>
#include <QTimer>

class TimerProxy : QObject
{
public:
    TimerProxy();

private:
    QTimer *timer;

signals:
    // for all animated sprites to register to
    void updateTime(int msecs);


};

#endif // TIMERPROXY_H
