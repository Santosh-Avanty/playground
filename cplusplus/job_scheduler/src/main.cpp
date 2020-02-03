#include <QCoreApplication>
#include <QDebug>
#include <jobscheduler.h>

using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc <= 2) {
        qCritical() << "Input format is invalid, Either task or task files ate missing, please check!";
        return  0;
    }

    JobScheduler schedular( argc, argv);

    return a.exec();
}
