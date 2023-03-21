#ifndef COUNTWIDGET_H
#define COUNTWIDGET_H

#include <QWidget>
#include <mainwindow.h>

class CountWidget : public QWidget
{
public:
    CountWidget(QWidget *parent = nullptr) : QWidget(parent) {};
    QLabel *countlabel;
private:
    QTimer *timer;
    int count;
    void timer_init();
    void timelimit_exceeded();
    void timer_update();
private slots:
    void TimerCount();
};

#endif // COUNTWIDGET_H
