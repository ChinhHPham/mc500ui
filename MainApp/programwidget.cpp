#include "programwidget.h"
#include "ui_programwidget.h"
#include "commmanager.h"
#include <QStyle>
#include <QTextBlock>
#include <QFileDialog>
#include <QDebug>

const QString htmlTextHighLight = QStringLiteral("<span style=\"background-color: #FFFF00\">%1</span>");
const QString kEdit = QStringLiteral("Edit");
const QString kSave = QStringLiteral("Save");
const QString kHold = QStringLiteral("Hold");
const QString kRelease = QStringLiteral("Release");
const QString kStarting = QStringLiteral("Starting");
const QString kStart = QStringLiteral("Start");
const QString kRunning = QStringLiteral("Running");

ProgramWidget::ProgramWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgramWidget),
    m_currentStep(0)
{
    ui->setupUi(this);
    connect(ui->editButton, &QPushButton::clicked, this, &ProgramWidget::editButtonClicked);
    connect(ui->holdButton, &QPushButton::clicked, this, &ProgramWidget::holdButtonClicked);
    connect(ui->startButton, &QPushButton::clicked, this, &ProgramWidget::startButtonClicked);
    connect(COMM_MANAGER, &CommManager::currentStepChanged, this, &ProgramWidget::currentStepChanged);
    connect(COMM_MANAGER, &CommManager::cycleStopped, this, &ProgramWidget::cycleStopped);
}

ProgramWidget::~ProgramWidget()
{
    delete ui;
}

void ProgramWidget::importProgramTriggered()
{
    QFile programFile = QFileDialog::getOpenFileName(this,
                                                     QLatin1String("Open file"),
                                                     QDir::currentPath(),
                                                     QLatin1String("Text files (*.txt)"));
    if (programFile.open(QFile::ReadOnly)) {
        ui->programTextEdit->setPlainText(QLatin1String(programFile.readAll()));
        programFile.close();
        updateProgram();
    }
}

void ProgramWidget::exportProgramTriggered()
{
    QFile programFile = QFileDialog::getSaveFileName(this,
                                                     QLatin1String("Save file"),
                                                     QDir::currentPath(),
                                                     QLatin1String("Text files (*.txt)"));
    if (programFile.open(QFile::WriteOnly)) {
        programFile.write(ui->programTextEdit->document()->toPlainText().toUtf8());
        programFile.close();
    }
}

void ProgramWidget::editButtonClicked()
{
    if (ui->editButton->text() == kEdit) {
        //Start editting
        ui->editButton->setText(kSave);
        setButtonEnabled(ui->startButton, false);
        ui->programTextEdit->setReadOnly(false);
        ui->programTextEdit->setUndoRedoEnabled(true);
    } else {
        //Finish editting
        ui->editButton->setText(kEdit);
        setButtonEnabled(ui->startButton, true);
        ui->programTextEdit->setReadOnly(true);
        ui->programTextEdit->setUndoRedoEnabled(false);
        updateProgram();
    }
}

void ProgramWidget::holdButtonClicked()
{
    if (ui->holdButton->text() == kHold) {
        if (COMM_MANAGER->updateFeedHoldStatus(true)) {
            ui->holdButton->setText(kRelease);
        }
    } else {
        if (COMM_MANAGER->updateFeedHoldStatus(false)) {
            ui->holdButton->setText(kHold);
        }
    }
}

void ProgramWidget::startButtonClicked()
{
    if (COMM_MANAGER->cycleStart()) {
        setButtonEnabled(ui->holdButton, false);
        setButtonEnabled(ui->startButton, false);
        ui->startButton->setText(kStarting);
        setButtonEnabled(ui->editButton, false);
    }
}

void ProgramWidget::currentStepChanged(quint32 currentStep)
{
    if (currentStep != m_currentStep) {
        ui->startButton->setText(kRunning);
        setButtonEnabled(ui->startButton, false);
        setButtonEnabled(ui->holdButton, true);
        setButtonEnabled(ui->editButton, false);

        QTextDocument *textDoc = ui->programTextEdit->document();
        QTextCursor nextBlockCursor(textDoc);
        QTextCursor currentBlockCursor(textDoc);

        if(m_currentStep > 0) {
            currentBlockCursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor, m_currentStep - 1);
            removeTextHighLight(currentBlockCursor);
        }
        nextBlockCursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor, currentStep - 1);
        highLightText(nextBlockCursor);
        m_currentStep = currentStep;
    }
}

void ProgramWidget::cycleStopped()
{
    setButtonEnabled(ui->holdButton, false);
    setButtonEnabled(ui->startButton, true);
    ui->startButton->setText(kStart);
    setButtonEnabled(ui->editButton, true);

    QTextCursor currentBlockCursor(ui->programTextEdit->document());
    currentBlockCursor.movePosition(QTextCursor::NextBlock, QTextCursor::MoveAnchor, m_currentStep - 1);
    removeTextHighLight(currentBlockCursor);
    m_currentStep = 0;
}

void ProgramWidget::setButtonEnabled(QPushButton *button, bool enabled)
{
    button->setEnabled(enabled);
    button->style()->unpolish(button);
    button->style()->polish(button);
}

void ProgramWidget::updateProgram()
{
    if (!COMM_MANAGER->clearProgram()) {
        qDebug() << QStringLiteral("Cannot send command clearProgram");
        return;
    }
    int blockCount = 0;
    QTextBlock currentBlock;
    for (currentBlock = ui->programTextEdit->document()->begin();
         currentBlock.isValid();
         currentBlock = currentBlock.next()) {
        ProgramLine pLine;
        pLine.commandLine = currentBlock.text();
        pLine.step = ++blockCount;
        if (!COMM_MANAGER->addProgramLine(pLine)) {
            qDebug() << QStringLiteral("Program uploading aborted at step %1: %2")
                        .arg(pLine.commandLine)
                        .arg(pLine.step);
            break;
        }
    }
}

void ProgramWidget::highLightText(QTextCursor &cursor)
{
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.insertHtml(htmlTextHighLight.arg(cursor.block().text()));
}

void ProgramWidget::removeTextHighLight(QTextCursor &cursor)
{
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.insertHtml(cursor.block().text());
}
