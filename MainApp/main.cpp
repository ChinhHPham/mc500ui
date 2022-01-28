#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Load CSS style from file
    QFile file(QStringLiteral(":/cssStyle/styles.qss"));
    Q_ASSERT(file.exists());
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return a.exec();
}
