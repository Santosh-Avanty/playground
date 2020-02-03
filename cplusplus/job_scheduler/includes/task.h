/****************************************************************************
**
** GNU General Public License Usage
** Author : Santosh Kumar
**
****************************************************************************/

#ifndef TASK_H
#define TASK_H

#include <QObject>

class Task : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief Task
     * \param name
     * \param dependencies
     * \param parent
     */
    explicit Task(const QString& name, const QString& dependencies, QObject *parent = nullptr);

    /*!
     * \brief isCompleted
     * \return
     */
    bool isCompleted();

    /*!
     * \brief setIsCompleted
     * \param isCompleted
     */
    void setIsCompleted(const bool isCompleted);

    /*!
     * \brief executeTask
     */
    void executeTask();

    /*!
     * \brief updateTask
     * \param name
     */
    void updateTask(const QString& name);

signals:
    void taskCompleted(const QString& name);
    void requestTask(const QString& name);

private:
    QString m_Name;
    QStringList m_Dependencies;
    bool m_isCompleted;
    bool m_isWaiting;

};

#endif // TASK_H
