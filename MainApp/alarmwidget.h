#ifndef ALARMWIDGET_H
#define ALARMWIDGET_H

#include <QWidget>

namespace Ui {
class AlarmWidget;
}

class AlarmWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlarmWidget(QWidget *parent = nullptr);
    ~AlarmWidget();    

private:
    Ui::AlarmWidget *ui;
};

#endif // ALARMWIDGET_H
