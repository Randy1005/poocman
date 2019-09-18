#include "timerproxy.h"

TimerProxy::TimerProxy()
{
    // instantiate QTimer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(emitUpdate()));
    timer -> start(16);

}

TimerProxy::~TimerProxy() {

}

void TimerProxy::emitUpdate() {
    emit updateTime(16);
}
