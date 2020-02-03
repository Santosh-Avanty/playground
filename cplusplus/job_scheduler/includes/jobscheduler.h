/****************************************************************************
**
** GNU General Public License Usage
** Author : Santosh Kumar
**
****************************************************************************/

#ifndef JOBSCHEDULER_H
#define JOBSCHEDULER_H

#include <QObject>
#include <QMap>
#include <QStack>

// Forward declaration
class Task;

class JobScheduler : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief JobScheduler
     * \param argc
     * \param argv
     * \param parent
     */
    explicit JobScheduler(const int argc, char* argv[], QObject *parent = nullptr);
    ~JobScheduler();

signals:
    /*!
     * \brief updateTasks
     * \param name
     */
    void updateTasks(const QString& name);


private:
    bool populateDataFromFiles(const QString& fileName);
    void exitApplication();
    void exitWithError();
    void tryExecuteTask(const QString& name, const QString& waitingName = "");

    QString m_TaskName;
    QMap<QString, Task*> m_TasksMap;
    QStack<QString> m_WaitingStack;

};

#endif // JOBSCHEDULER_H
