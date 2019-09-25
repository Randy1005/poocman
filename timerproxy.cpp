#include "timerproxy.h"

TimerProxy::TimerProxy()
{
    // instantiate QTimer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(emitUpdate()));
    timer -> start(64);
}

TimerProxy::~TimerProxy() {

}

void TimerProxy::emitUpdate() {
    emit updateTime(64);
}
