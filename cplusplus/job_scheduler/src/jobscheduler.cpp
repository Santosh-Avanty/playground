/****************************************************************************
**
** GNU General Public License Usage
** Author : Santosh Kumar
**
****************************************************************************/

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>

#include "jobscheduler.h"
#include "task.h"

#define LENGTHONE 6
#define LENGTHTWO 14

using namespace std;

JobScheduler::JobScheduler(const int argc, char* argv[], QObject *parent) : QObject(parent)
{
    m_TaskName = argv[1];

    for (int index = 2; index < argc; ++index) {

        qDebug() << "Reading file " << (QDir::homePath().append("/tasks/").append(argv[index]));
       if(!populateDataFromFiles(QDir::homePath().append("/tasks/").append(argv[index]))) {
           exitApplication();
       }
    }

    qDebug() << "---------Data populated------Executing task now";
    tryExecuteTask(m_TaskName);
}

JobScheduler::~JobScheduler()
{
    // Destroy map and task objects.
    m_TasksMap.clear();
}

bool JobScheduler::populateDataFromFiles(const QString& fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
         qCritical() << "Error in reading file";
         return false;
    } else {

        QString name;
        QString dependecies;

        // Read the config files line by line and extract name and dependencies.
        while (!file.atEnd()) {
            QString line = file.readLine().trimmed();
            if (line.contains("name:")) {
                name = line.remove(0, LENGTHONE);
            } else if (line.contains("dependencies:")) {
                dependecies = line.remove(0, LENGTHTWO);
            }
        }

        // Create task object and connect signals
        Task* currentTask = new Task(name, dependecies);
        // Propogare completed event to job-scheduler
        connect(currentTask, &Task::taskCompleted, this, &JobScheduler::taskCompleted);
        // Serve the request from task objects on dependencies.
        connect(currentTask, &Task::requestTask, this, &JobScheduler::tryExecuteTask);
        // Propogate completed event to other tasks.
        connect(this, &JobScheduler::taskCompleted, currentTask, &Task::updateTask);

        m_TasksMap.insert(name, currentTask);
    }

    return true;
}

void JobScheduler::tryExecuteTask(const QString& name)
{
    // Execute the task if it is found otherwise exit withe error.
    if (m_TasksMap.contains(name)) {
         m_TasksMap[name]->executeTask();
    } else {
        exitWithError();
    }
}

void JobScheduler::exitApplication()
{
    QCoreApplication::exit(0);
}

void JobScheduler::exitWithError()
{
    qCritical() << "Error!, Please check the log";
    QCoreApplication::exit(1);
}
