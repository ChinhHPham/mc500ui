#include "valuedetailwidget.h"
#include "ui_valuedetailwidget.h"

ValueDetailWidget::ValueDetailWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ValueDetailWidget)
{
    ui->setupUi(this);
}

ValueDetailWidget::~ValueDetailWidget()
{
    delete ui;
}
