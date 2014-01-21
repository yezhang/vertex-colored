#include "mainwindow.h"
#include <QtGui/QApplication>
#include <QtCore/QTextCodec>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/appicon/colorgraph.png"));
    // 以下部分解决中文乱码
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    // 以上部分解决中文乱码

    MainWindow w;
    w.show();


    return a.exec();
}
