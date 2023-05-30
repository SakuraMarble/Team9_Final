#include "signinwindow.h"
#include <QApplication>

#include <QAbstractButton>
#include <QMessageBox>
#include <QDateTime>
#include <QMutex>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#ifndef but
#define but 3373;

#endif

static QMutex mutex;
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    //Q_UNUSED(context)
    QDateTime datetime = QDateTime::currentDateTime();
    QString LogDate = datetime.toString("yyyy-MM-dd hh:mm:ss.zzz");//"yyyy-MM-dd hh:mm:ss ddd"
    QString txt(LogDate);

    switch (type)
    {
    case QtDebugMsg://调试信息提示
    {
        txt += QString(" [Debug] ");
        break;
    }
    case QtInfoMsg://信息输出
    {
        txt += QString(" [Info] ");
        break;
    }
    case QtWarningMsg://一般的warning提示
    {
        txt += QString(" [Warning] ");
        break;
    }
    case QtCriticalMsg://严重错误提示
    {
        txt += QString(" [Critical] ");
        break;
    }
    case QtFatalMsg://致命错误提示
    {
        txt += QString(" [Fatal] ");
        break;
    }
    default:
    {
        txt += QString(" [Trace] ");
        break;
    }
    }

    txt.append( QString(" %1").arg(context.file) );
    txt.append( QString("<%1>: ").arg(context.line) );
    txt.append(msg);

    mutex.lock();
    QString documents_path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString folder_path = documents_path + "/Nogo Running Logs";
    // create folder if it does not exist
    QDir().mkpath(folder_path);
    QFile file(folder_path + "/" + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh") + "-log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << txt << "\r\n";
    file.flush();
    file.close();
    mutex.unlock();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(customMessageHandler);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    SignInWindow w;
    w.show();

    return a.exec();
}
