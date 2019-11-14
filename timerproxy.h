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

    static int countdown;
    int counter;

signals:
    // for all animated sprites to register to
    void updateTime(int msecs);

    // update labels
    void gamesceneUpdateInfo(QString name);

    // switch scene
    void changeScene();


private slots:
    // to emit updateTime
    void emitUpdate();


};

#endif // TIMERPROXY_H
