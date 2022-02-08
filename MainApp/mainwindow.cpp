#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coordinatewidget.h"
#include "valuedetailwidget.h"
#include "alarmwidget.h"
#include "commmanager.h"

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CoordinateWidget *coordinateController = new CoordinateWidget(this);
    ValueDetailWidget *valueDetail = new ValueDetailWidget(this);
    ui->gridLayout->addWidget(coordinateController, 0, 0);
    ui->gridLayout->addWidget(valueDetail, 0, 1);

    connect(COMM_MANAGER, &CommManager::connectedToHost,
            this, [Ui = ui](){Ui->statusbar->showMessage(QStringLiteral("Connected to host"));});
    connect(COMM_MANAGER, &CommManager::disconnectedToHost,
            this, [Ui = ui](){Ui->statusbar->showMessage(QStringLiteral("Disconnected to host"));});
    connect(COMM_MANAGER, &CommManager::cannotEstablishConnection,
            this, [Ui = ui](){Ui->statusbar->showMessage(QStringLiteral("Cannot connect to host"));});
    COMM_MANAGER->initTCPConnection();

    connect(ui->aImportProgram, &QAction::triggered, ui->programWidget, &ProgramWidget::importProgramTriggered);
    connect(ui->aExportProgram, &QAction::triggered, ui->programWidget, &ProgramWidget::exportProgramTriggered);
}

MainWindow::~MainWindow()
{
    delete ui;
}
