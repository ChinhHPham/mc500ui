#ifndef COORDINATEWIDGET_H
#define COORDINATEWIDGET_H

#include <QFrame>

#include "dataclasses.h"

namespace Ui {
class CoordinateWidget;
}

class CoordinateWidget : public QFrame
{
    Q_OBJECT

public:
    explicit CoordinateWidget(QWidget *parent = nullptr);
    ~CoordinateWidget();

private slots:
    void positionUpdated(PositionExact pos);

private:
    Ui::CoordinateWidget *ui;
};

#endif // COORDINATEWIDGET_H
