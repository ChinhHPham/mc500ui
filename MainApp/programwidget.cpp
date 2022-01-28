#include "programwidget.h"
#include "ui_programwidget.h"
#include <QStyle>

ProgramWidget::ProgramWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramWidget)
{
    ui->setupUi(this);
}

ProgramWidget::~ProgramWidget()
{
    delete ui;
}

void ProgramWidget::on_editButton_clicked()
{
    if (ui->editButton->text() == QStringLiteral("Edit")) {
        ui->editButton->setText(QStringLiteral("Save"));
        setButtonEnabled(ui->startButton, false);
    } else {
        ui->editButton->setText(QStringLiteral("Edit"));
        setButtonEnabled(ui->startButton, true);
    }
}

void ProgramWidget::on_holdButton_clicked()
{
    ui->holdButton->text() == QStringLiteral("Hold") ?
        ui->holdButton->setText(QStringLiteral("Release")) :
        ui->holdButton->setText(QStringLiteral("Hold"));
}

void ProgramWidget::on_startButton_clicked()
{
    setButtonEnabled(ui->holdButton, true);
    setButtonEnabled(ui->startButton, false);
    ui->startButton->setText(QStringLiteral("Running"));
    setButtonEnabled(ui->editButton, false);
}

void ProgramWidget::setButtonEnabled(QPushButton *button, bool enabled)
{
    button->setEnabled(enabled);
    button->style()->unpolish(button);
    button->style()->polish(button);
}
