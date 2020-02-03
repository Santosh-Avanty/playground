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
     * \brief taskCompleted
     * \param name
     */
    void taskCompleted(const QString& name);

private:
    bool populateDataFromFiles(const QString& fileName);
    void exitApplication();
    void exitWithError();
    void tryExecuteTask(const QString& name);

    QString m_TaskName;
    QMap<QString, Task*> m_TasksMap;

};

#endif // JOBSCHEDULER_H
