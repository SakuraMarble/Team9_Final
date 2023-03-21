#ifndef COUNTWIDGET_H
#define COUNTWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLabel>

class CountWidget : public QWidget
{
public:
    CountWidget(QWidget *parent = nullptr) : QWidget(parent) {};
    QLabel *countlabel;
    QTimer *timer;
    int count;
    // 设置布局

    void timer_init();
    void timelimit_exceeded();
    void timer_update();
private slots:
    void TimerCount();
};

#endif // COUNTWIDGET_H
