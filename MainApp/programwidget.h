#ifndef PROGRAMWIDGET_H
#define PROGRAMWIDGET_H

#include <QWidget>

class QPushButton;

namespace Ui {
class ProgramWidget;
}

class ProgramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProgramWidget(QWidget *parent = nullptr);
    ~ProgramWidget();

private slots:
    void on_editButton_clicked();

    void on_holdButton_clicked();

    void on_startButton_clicked();

private:
    Ui::ProgramWidget *ui;
    void setButtonEnabled(QPushButton *button, bool enabled);
};

#endif // PROGRAMWIDGET_H
