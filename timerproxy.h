#ifndef TIMERPROXY_H
#define TIMERPROXY_H

#include <QObject>
#include <QDebug>
#include <QTimer>

class TimerProxy : public QObject
{
    Q_OBJECT

public:
    TimerProxy();
    ~TimerProxy();
    QTimer *timer;

signals:
    // for all animated sprites to register to
    void updateTime(int msecs);

private slots:
    // to emit updateTime
    void emitUpdate();


};

#endif // TIMERPROXY_H
