#include "coordinatewidget.h"
#include "ui_coordinatewidget.h"
#include "commmanager.h"

CoordinateWidget::CoordinateWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CoordinateWidget)
{
    ui->setupUi(this);
    //connect(MessageHandler::instance(), &MessageHandler::positionUpdated, this, &CoordinateWidget::positionUpdated);
}

CoordinateWidget::~CoordinateWidget()
{
    delete ui;
}

void CoordinateWidget::positionUpdated(PositionExact pos)
{
    switch (pos.type) {
    case COORDINATE_TYPE::X:
        ui->XValue->setText(QStringLiteral("%1").arg(pos.x));
        break;
    case COORDINATE_TYPE::Y:
        ui->YValue->setText(QStringLiteral("%1").arg(pos.y));
        break;
    case COORDINATE_TYPE::Z:
        ui->ZValue->setText(QStringLiteral("%1").arg(pos.z));
        break;
    case COORDINATE_TYPE::ALL:
        ui->XValue->setText(QStringLiteral("%1").arg(pos.x));
        ui->YValue->setText(QStringLiteral("%1").arg(pos.y));
        ui->ZValue->setText(QStringLiteral("%1").arg(pos.z));
        break;
    default:
        Q_ASSERT(false);
        break;
    }
}
