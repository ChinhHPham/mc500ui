#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QPainter>

QPixmap beautifyIcon(QPixmap &logo) {
    QPixmap beautifiedImg(logo);
    QRect imgRect = beautifiedImg.rect();
    int borderRadius = imgRect.width() / 5;
    QPainter p(&beautifiedImg);

    p.setRenderHint(QPainter::Antialiasing);
    p.setBrush(QColor("white"));
    p.drawRoundedRect(imgRect, borderRadius, borderRadius);
    p.setPen(Qt::transparent);
    p.drawPixmap(imgRect, logo);
    return beautifiedImg;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap logo(QStringLiteral(":/images/logo.png"));
    qApp->setWindowIcon(QIcon(beautifyIcon(logo)));

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
