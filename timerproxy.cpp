#include "timerproxy.h"


TimerProxy::TimerProxy()
{
    // instantiate QTimer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(emitUpdate()));
    timer -> start(64);

    counter = 16; // for the countdown timer to count approximately 1 sec.
}

TimerProxy::~TimerProxy() {

}

void TimerProxy::emitUpdate() {
    emit updateTime(64);

    counter--;
    if (counter == 0) {
        counter = 16;
        countdown--;
        emit gamesceneUpdateInfo("cntDown");
    }

    if (countdown == 0) {
        emit changeScene();
    }
}
