#include "timerproxy.h"

TimerProxy::TimerProxy()
{
    // instantiate QTimer
    timer = new QTimer(this);

    // QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateTime(16)));

}

void TimerProxy::updateTime(int msecs) {
    qDebug() << "wow\n";
}
