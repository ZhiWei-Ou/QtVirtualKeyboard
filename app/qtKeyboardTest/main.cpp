#include <QApplication>
#include <QWidget>
#include <QDateTime>
#include <QtCore/qglobal.h>
#include <cstdio>
#include <QDebug>
#include <QLineEdit>

static void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

QSize GlobGetScreenSize(bool &ok) {
    ok = true;
    return QSize(1024, 600);
}

/**
 * @file main.cpp
 * @function main
 *
 */
int main(int argc, char **argv) {
    // Qt Application
    // log format && filter
    qInstallMessageHandler(myMessageHandler);
    qputenv("QT_LOGGING_RULES",QByteArray("qtkeyboard.*=true\nother.*=true"));

    // Keyboard Plugin Environment
    qputenv("QT_IM_MODULE",QByteArray("QtKeyboard"));
    // qputenv("QT_IM_MODULE",QByteArray("qtvirtualkeyboard"));

    QApplication app(argc, argv);

    QWidget w;
    w.setObjectName("HelloWidget");
    w.setFocusPolicy(Qt::ClickFocus);
    w.resize(800, 480);

    QLineEdit lineEdit(&w);
    lineEdit.setGeometry(10, 10, 200, 50);

    w.show();

    return app.exec();
}

QtMsgType GlobQLogLevel = QtDebugMsg;

void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
#define COLOR_DEBUG "\033[36m"
#define COLOR_INFO "\033[32m"
#define COLOR_WARN "\033[33m"

#define COLOR_GRAY "\033[90m"
#define COLOR_RESET "\033[0m"

    QByteArray localMsg = msg.toLocal8Bit();
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");

    switch (type) {
    case QtDebugMsg:
        fprintf(stdout, "%s%s%s %sDebug%s: %s\n",
                COLOR_GRAY, timestamp.toLocal8Bit().constData(), COLOR_RESET,
                COLOR_DEBUG, COLOR_RESET,
                localMsg.constData());
        break;
    case QtInfoMsg:
        fprintf(stdout, "%s%s%s %sInfo%s: %s\n",
                COLOR_GRAY, timestamp.toLocal8Bit().constData(), COLOR_RESET,
                COLOR_INFO, COLOR_RESET,
                localMsg.constData());
        break;
    case QtWarningMsg:
        fprintf(stdout, "%s%s%s %sWarning%s: %s\n",
                COLOR_GRAY, timestamp.toLocal8Bit().constData(), COLOR_RESET,
                COLOR_WARN, COLOR_RESET,
                localMsg.constData());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "-- Critical: %s\n", localMsg.constData());
        break;
    case QtFatalMsg:
        fprintf(stderr, "-- Fatal: %s\n", localMsg.constData());
        abort();
    }
}

