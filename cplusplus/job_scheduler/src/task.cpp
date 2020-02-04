/****************************************************************************
**
** GNU General Public License Usage
** Author : Santosh Kumar
**
****************************************************************************/

#include <QString>
#include <QDebug>

#include "task.h"

/*!
 * \brief Task::Task
 * \param name
 * \param dependencies
 * \param parent
 */
Task::Task(const QString& name, const QString& dependencies, QObject *parent) : QThread(parent)
{
    m_isCompleted = false;
    m_Name = name;
    m_Dependencies = dependencies.split(',', QString::SkipEmptyParts);
}

/*!
 * \brief Task::isCompleted
 * \return
 */
bool Task::isCompleted()
{
    return m_isCompleted;
}

/*!
 * \brief Task::setIsCompleted
 * \param isCompleted
 */
void Task::setIsCompleted(const bool isCompleted)
{
    m_Dependencies.clear();
    m_isCompleted = isCompleted;
    emit taskCompleted(m_Name);
}

/*!
 * \brief Task::executeTask
 */
void Task::run()
{
    executeTask();
    exec();
}

void Task::executeTask()
{
    if (m_Dependencies.isEmpty()) {
        qDebug() << "echo I am task " << m_Name << " completed.";
        setIsCompleted(true);
    } else {
        emit requestTask(m_Dependencies[0], m_Name);
    }
}

/*!
 * \brief Task::updateTask
 * \param name
 */
void Task::updateTask(const QString& name)
{
    if (m_Dependencies.contains(name)) {
        m_Dependencies.removeOne(name);
    }
}
