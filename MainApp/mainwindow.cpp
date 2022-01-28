#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coordinatewidget.h"
#include "valuedetailwidget.h"
#include "alarmwidget.h"
#include <QFile>
#include <QHBoxLayout>
#include <qglobal.h>
#include "tcpsocket.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CoordinateWidget *coordinateController = new CoordinateWidget(this);
    ValueDetailWidget *valueDetail = new ValueDetailWidget(this);
    ui->gridLayout->addWidget(coordinateController, 0, 0);
    ui->gridLayout->addWidget(valueDetail, 0, 1);

//Get host name and port from environment variables and establish connection
#ifdef Q_OS_UNIX
    TCPSocket::instance()->doConnect(QLatin1String(qgetenv("MC_HOSTNAME")), qgetenv("MC_PORT").toInt());
#elif Q_OS_WIN32
    TCPSocket::instance()->doConnect(qEnvironmentVariable("MC_HOSTNAME"), qEnvironmentVariable("MC_PORT").toInt());
#else
    Q_ASSERT(true);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

