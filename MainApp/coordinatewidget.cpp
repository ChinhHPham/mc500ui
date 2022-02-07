#include "coordinatewidget.h"
#include "ui_coordinatewidget.h"
#include "commmanager.h"

CoordinateWidget::CoordinateWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CoordinateWidget)
{
    ui->setupUi(this);
    connect(COMM_MANAGER, &CommManager::positionUpdated, this, &CoordinateWidget::positionUpdated);
    connect(ui->resetXButton, &QPushButton::clicked, this, &CoordinateWidget::updateXPos);
    connect(ui->resetYButton, &QPushButton::clicked, this, &CoordinateWidget::updateYPos);
    connect(ui->resetZButton, &QPushButton::clicked, this, &CoordinateWidget::updateZPos);
}

CoordinateWidget::~CoordinateWidget()
{
    delete ui;
}

void CoordinateWidget::positionUpdated(PositionExact pos)
{
    switch (pos.type) {
    case COORDINATE_TYPE::X:
        ui->xValue->setText(QStringLiteral("%1").arg(pos.x));
        break;
    case COORDINATE_TYPE::Y:
        ui->yValue->setText(QStringLiteral("%1").arg(pos.y));
        break;
    case COORDINATE_TYPE::Z:
        ui->zValue->setText(QStringLiteral("%1").arg(pos.z));
        break;
    case COORDINATE_TYPE::ALL:
        ui->xValue->setText(QStringLiteral("%1").arg(pos.x));
        ui->yValue->setText(QStringLiteral("%1").arg(pos.y));
        ui->zValue->setText(QStringLiteral("%1").arg(pos.z));
        break;
    default:
        Q_ASSERT(false);
        break;
    }
}

void CoordinateWidget::updateXPos()
{
    PositionExact newPos;
    newPos.x = ui->xValue->text().toInt();
    newPos.type = COORDINATE_TYPE::X;
    COMM_MANAGER->updatePosition(newPos);
}

void CoordinateWidget::updateYPos()
{
    PositionExact newPos;
    newPos.y = ui->yValue->text().toInt();
    newPos.type = COORDINATE_TYPE::Y;
    COMM_MANAGER->updatePosition(newPos);
}

void CoordinateWidget::updateZPos()
{
    PositionExact newPos;
    newPos.z = ui->zValue->text().toInt();
    newPos.type = COORDINATE_TYPE::Z;
    COMM_MANAGER->updatePosition(newPos);
}
