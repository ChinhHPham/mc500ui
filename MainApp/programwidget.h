#ifndef PROGRAMWIDGET_H
#define PROGRAMWIDGET_H

#include <QWidget>

class QPushButton;
class QTextCursor;

namespace Ui {
class ProgramWidget;
}

class ProgramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProgramWidget(QWidget *parent = nullptr);
    ~ProgramWidget();

public slots:
    void importProgramTriggered();
    void exportProgramTriggered();

private slots:
    void editButtonClicked();
    void holdButtonClicked();
    void startButtonClicked();
    void currentStepChanged(quint32 currentStep);
    void cycleStopped();

private:
    Ui::ProgramWidget *ui;
    quint32 m_currentStep;
    void setButtonEnabled(QPushButton *button, bool enabled);
    void updateProgram();
    void highLightText(QTextCursor &cursor);
    void removeTextHighLight(QTextCursor &cursor);
};

#endif // PROGRAMWIDGET_H
