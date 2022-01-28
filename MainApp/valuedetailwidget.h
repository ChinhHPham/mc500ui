#ifndef VALUEDETAILWIDGET_H
#define VALUEDETAILWIDGET_H

#include <QFrame>

namespace Ui {
class ValueDetailWidget;
}

class ValueDetailWidget : public QFrame
{
    Q_OBJECT

public:
    explicit ValueDetailWidget(QWidget *parent = nullptr);
    ~ValueDetailWidget();

private:
    Ui::ValueDetailWidget *ui;
};

#endif // VALUEDETAILWIDGET_H
